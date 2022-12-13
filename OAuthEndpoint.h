#ifndef LINUXHAZI_OAUTHENDPOINT_H
#define LINUXHAZI_OAUTHENDPOINT_H

#include <pistache/router.h>
#include "LoginValidator.h"

class OAuthEndpoint {

public:
    OAuthEndpoint(LoginValidation::LoginValidator &loginValidator);

    void authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

    void tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

private:
    LoginValidation::LoginValidator &loginValidator;
};


#endif //LINUXHAZI_OAUTHENDPOINT_H
