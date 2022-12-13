#include "OAuthEndpoint.h"

OAuthEndpoint::OAuthEndpoint(LoginValidation::LoginValidator &loginValidator) : loginValidator(loginValidator) {
}

void OAuthEndpoint::authorizeCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

void OAuthEndpoint::tokenCallback(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

}

