#include "PostgresLoginValidator.h"

namespace LoginValidation {

    bool PostgresLoginValidator::checkCredentials(std::map<std::string, std::string> credentialMap) {
        return false;
    }

    PostgresLoginValidator::PostgresLoginValidator(pqxx::connection &connection) : connection(connection) {

    }
} // LoginValidation