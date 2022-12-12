#include "PostgresLoginValidator.h"

namespace LoginValidation {

    bool PostgresLoginValidator::checkCredentials(std::map<std::string, std::string> (*pFunction)()) {

        return false;
    }

    PostgresLoginValidator::PostgresLoginValidator(pqxx::connection &connection):connection(connection) {

    }
} // LoginValidation