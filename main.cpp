#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <fstream>
#include "OAuthEndpoint.h"
#include "PostgresLoginValidator.h"

int main(int argc, char *argv[]) {
    nlohmann::json config;
    //Set up logging
    spdlog::logger mainLogger("OAuthService");
    auto sinks = mainLogger.sinks();
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[%n][%^%l%$] %v");
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/oauth-{}.txt",
                                                                                     std::chrono::system_clock::now().time_since_epoch() /
                                                                                     std::chrono::milliseconds(1)),
                                                                         true);
    file_sink->set_level(spdlog::level::trace);
    std::vector<spdlog::sink_ptr> sinkList;
    sinkList.push_back(file_sink);
    sinkList.push_back(console_sink);
    mainLogger.sinks().insert(mainLogger.sinks().end(), sinkList.begin(), sinkList.end());
    try {
        auto configFileName = "configFile.json";
        if (argc > 1)
            configFileName = argv[1];
        std::ifstream configFile(configFileName);
        config = nlohmann::json::parse(configFile);
        if (config.is_null()) {
            throw std::runtime_error("Config is null");
        }
    }
    catch (std::exception &e) {
        mainLogger.error("Error while loading config file: {}", e.what());
        config = nlohmann::json::parse("{\"version\":1}");
    }
    mainLogger.info("Hello {}", config.value("name", "default"));
    //Make restarting possible without clean exit
    auto pistacheOptions = Pistache::Http::Endpoint::options();
    pistacheOptions.flags(Pistache::Tcp::Options::ReuseAddr);
    Pistache::Address address;
    if (config.contains("listenAddress") && config.at("listenAddress").is_string())
        address = Pistache::Address(config["listenAddress"]);
    else
        address = Pistache::Address(Pistache::IP::any(), 9800);
    std::shared_ptr<Pistache::Http::Endpoint> endpoint = std::make_shared<Pistache::Http::Endpoint>(address);
    Pistache::Rest::Router router;
    pqxx::connection conn(config.value("postgresAddress", ""));
    auto loginValidator = LoginValidation::PostgresLoginValidator(conn, sinkList);
    auto oAuthEndpointSmartPtr = std::make_shared<OAuthEndpoint>(loginValidator, sinkList);
    {
        using namespace std::placeholders;
        router.addRoute(Pistache::Http::Method::Get, "/authorize",
                        Pistache::Rest::Routes::bind(&OAuthEndpoint::authorizeCallback, oAuthEndpointSmartPtr));
        router.addRoute(Pistache::Http::Method::Post, "/authorize",
                        Pistache::Rest::Routes::bind(&OAuthEndpoint::authorizeCallback, oAuthEndpointSmartPtr));
        router.addRoute(Pistache::Http::Method::Get, "/token",
                        Pistache::Rest::Routes::bind(&OAuthEndpoint::tokenCallback, oAuthEndpointSmartPtr));
    }
    endpoint->init(pistacheOptions);
    endpoint->setHandler(router.handler());
    endpoint->serve();
}