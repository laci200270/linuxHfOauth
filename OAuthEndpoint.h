#ifndef LINUXHAZI_OAUTHENDPOINT_H
#define LINUXHAZI_OAUTHENDPOINT_H

#include "LoginValidator.h"

class OAuthEndpoint {

public:
    OAuthEndpoint(LoginValidation::LoginValidator &loginValidator);
private:
    LoginValidation::LoginValidator &loginValidator;
};


#endif //LINUXHAZI_OAUTHENDPOINT_H
