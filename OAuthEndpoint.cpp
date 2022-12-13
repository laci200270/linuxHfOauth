#include "OAuthEndpoint.h"

OAuthEndpoint::OAuthEndpoint(LoginValidation::LoginValidator &loginValidator, std::vector<spdlog::sink_ptr> logSinks)
        : loginValidator(loginValidator), logSinks(logSinks), logger(("OAuthEndpoint")) {
    logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
}


void OAuthEndpoint::authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

void OAuthEndpoint::tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

