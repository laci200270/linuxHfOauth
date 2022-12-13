#include "OAuthEndpoint.h"
#include "fmt/format.h"

OAuthEndpoint::OAuthEndpoint(LoginValidation::LoginValidator &loginValidator, std::vector<spdlog::sink_ptr> logSinks)
        : loginValidator(loginValidator), logSinks(logSinks), logger(("OAuthEndpoint")) {
    logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
}


void OAuthEndpoint::authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    switch (request.method()) {
        case Pistache::Http::Method::Get:
            if (request.query().has("response_type") && request.query().has("client_id") &&
                request.query().has("redirect_uri") && request.query().has("scope") && request.query().has("state")) {
                auto responseType = *request.query().get("response_type");
                auto client_id = *request.query().get("client_id");
                auto redirect_uri = *request.query().get("redirect_uri");
                auto scope = *request.query().get("scope");
                auto state = *request.query().get("state");

                if (responseType == "code") {
                    if (request.query().has("code_challenge") || request.query().has("code_challenge_method")) {
                        response.send(Pistache::Http::Code::Not_Implemented);
                        break;
                    }
                    std::string locationUri = fmt::format(
                            "/authenticate?response_type={}&client_id={}&redirect_uri={}&scope={}&state={}",
                            responseType, client_id, redirect_uri, scope, state);
                    response.headers().add<Pistache::Http::Header::Location>(locationUri);
                    response.send(Pistache::Http::Code::Temporary_Redirect);
                } else {
                    response.send(Pistache::Http::Code::Not_Implemented);
                    break;
                }
            } else {
                response.send(Pistache::Http::Code::Bad_Request);
                break;
            }
        case Pistache::Http::Method::Post:
            break;
    }
    logger.flush();
}

void OAuthEndpoint::tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

void
OAuthEndpoint::authenticateCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::ContentType>("text/html");
    response.send(Pistache::Http::Code::Ok, fmt::format(R"( <form method="POST" action="/authorize{0}">
                                                                                <label for="uname">Username:</label>
                                                                                <input type="text" id="uname" name="uname"><br><br>
                                                                                <label for="pw">Password:</label>
                                                                                <input type="password" id="pw" name="pw"><br><br>
                                                                                <input type="submit" value="Submit">
                                                                            </form>)", request.query().as_str()));;

}

