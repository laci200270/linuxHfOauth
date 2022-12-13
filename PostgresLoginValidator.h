#ifndef LINUXHAZI_POSTGRESLOGINVALIDATOR_H
#define LINUXHAZI_POSTGRESLOGINVALIDATOR_H

#include "LoginValidator.h"
#include <pqxx/pqxx>

namespace LoginValidation {

    class PostgresLoginValidator : public LoginValidation::LoginValidator {
    public:

        class PostgresUserInternalRepresentation : User {
        private:
            PostgresUserInternalRepresentation(const std::string &email, const std::string &displayName,
                                               const std::string &username, const std::string &passwordHash,
                                               unsigned int id);

            unsigned id;
            std::string username, passwordHash;
        public:
            const std::string &getEmail() const;

            const std::string &getDisplayName() const;

            const std::string &getUsername() const;

            const bool validatePassword(std::string password);

            PostgresUserInternalRepresentation(unsigned int id, const std::string &email,
                                               const std::string &displayName,
                                               const std::string &username, const std::string &passwordHash);
        };

        std::optional<PostgresLoginValidator::PostgresUserInternalRepresentation>
        getInternalUserRepresentationFromUsername(std::string username);

        PostgresLoginValidator(pqxx::connection &connection,
                               std::vector<spdlog::sink_ptr> logSinks = std::vector<spdlog::sink_ptr>());

        bool checkCredentials(std::map<std::string, std::string> credentialMap) override;

    private:
        pqxx::connection &connection;
    };

} // LoginValidation

#endif //LINUXHAZI_POSTGRESLOGINVALIDATOR_H
