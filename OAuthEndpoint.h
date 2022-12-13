#ifndef LINUXHAZI_OAUTHENDPOINT_H
#define LINUXHAZI_OAUTHENDPOINT_H

#include <pistache/router.h>
#include <spdlog/common.h>
#include "LoginValidator.h"

class OAuthEndpoint {

public:
    OAuthEndpoint(LoginValidation::LoginValidator &loginValidator,
                  std::vector<spdlog::sink_ptr> logSinks = std::vector<spdlog::sink_ptr>());

    void authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

    void tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

private:
    LoginValidation::LoginValidator &loginValidator;
    std::vector<spdlog::sink_ptr> logSinks;
    spdlog::logger logger;

};


#endif //LINUXHAZI_OAUTHENDPOINT_H
