#ifndef LINUXHAZI_POSTGRESLOGINVALIDATOR_H
#define LINUXHAZI_POSTGRESLOGINVALIDATOR_H

#include "LoginValidator.h"

namespace LoginValidation {

    class PostgresLoginValidator : LoginValidation::LoginValidator {
        bool checkCredentials(std::map<std::string, std::string> (*pFunction)()) override;
    };

} // LoginValidation

#endif //LINUXHAZI_POSTGRESLOGINVALIDATOR_H
