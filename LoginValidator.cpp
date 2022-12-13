
#include <string>
#include "LoginValidator.h"

const std::string &LoginValidation::LoginValidator::User::getDisplayName() const {
    return displayName;
}

const std::string &LoginValidation::LoginValidator::User::getEmail() const {
    return email;
}

LoginValidation::LoginValidator::User::User(const std::string &displayName, const std::string &email) : displayName(
        displayName), email(email) {}
