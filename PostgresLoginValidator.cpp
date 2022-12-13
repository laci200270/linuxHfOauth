#include <bcrypt/BCrypt.hpp>
#include <fmt/format.h>
#include "PostgresLoginValidator.h"

namespace LoginValidation {


    bool PostgresLoginValidator::checkCredentials(std::map<std::string, std::string> credentialMap) {
        if (!credentialMap.contains("username") || !credentialMap.contains("password")) {
            return false;
        }
        auto optionalUser = getInternalUserRepresentationFromUsername(credentialMap["username"]);
        if (!optionalUser.has_value())
            return false;
        auto user = *optionalUser;
        return user.validatePassword(credentialMap["password"]);
    }

    std::optional<PostgresLoginValidator::PostgresUserInternalRepresentation>
    PostgresLoginValidator::getInternalUserRepresentationFromUsername(std::string username) {
        using namespace pqxx;
        auto sql = fmt::format("SELECT * from users WHERE username='{}'", connection.esc(username));
        nontransaction sqlNonTransactQuery(connection);
        result queryResult(sqlNonTransactQuery.exec(sql));
        if (queryResult.empty())
            return std::optional<PostgresLoginValidator::PostgresUserInternalRepresentation>();
        auto userRow = *queryResult.begin();
        PostgresUserInternalRepresentation user(userRow["id"].as<int>(), userRow["displayName"].as<std::string>(),
                                                userRow["email"].as<std::string>(), username,
                                                userRow["pwHash"].as<std::string>());
        return user;
    }

    PostgresLoginValidator::PostgresLoginValidator(pqxx::connection &connection, std::vector<spdlog::sink_ptr> logSinks)
            : connection(connection),
              LoginValidation::LoginValidator(logSinks) {
        logger = logger = spdlog::logger("PostgresLoginValidator");
        logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
        logger.info("PostgresLoginValidator successfully started");
    }

    const std::string &PostgresLoginValidator::PostgresUserInternalRepresentation::getUsername() const {
        return username;
    }

    const bool PostgresLoginValidator::PostgresUserInternalRepresentation::validatePassword(std::string password) {
        return BCrypt::validatePassword(password, this->passwordHash);
    }

    PostgresLoginValidator::PostgresUserInternalRepresentation::PostgresUserInternalRepresentation(unsigned int id,
                                                                                                   const std::string &email,
                                                                                                   const std::string &displayName,
                                                                                                   const std::string &username,
                                                                                                   const std::string &passwordHash) {

    }
} // LoginValidation