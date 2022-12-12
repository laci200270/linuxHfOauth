#ifndef LINUXHAZI_POSTGRESLOGINVALIDATOR_H
#define LINUXHAZI_POSTGRESLOGINVALIDATOR_H

#include "LoginValidator.h"
#include <pqxx/pqxx>

namespace LoginValidation {

    class PostgresLoginValidator : LoginValidation::LoginValidator {
    public:
        PostgresLoginValidator(pqxx::connection &connection);
        bool checkCredentials(std::map<std::string, std::string> (*pFunction)()) override;
    private:
        pqxx::connection &connection;
    };

} // LoginValidation

#endif //LINUXHAZI_POSTGRESLOGINVALIDATOR_H
