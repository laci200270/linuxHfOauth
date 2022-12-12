#ifndef LINUXHAZI_OAUTHENDPOINT_H
#define LINUXHAZI_OAUTHENDPOINT_H

#include "LoginValidator.h"

class OAuthEndpoint {

public:
    OAuthEndpoint(LoginValidator &loginValidator);
private:
    LoginValidator &loginValidator;
};


#endif //LINUXHAZI_OAUTHENDPOINT_H
