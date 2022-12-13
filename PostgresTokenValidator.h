#ifndef LINUXHAZI_POSTGRESTOKENVALIDATOR_H
#define LINUXHAZI_POSTGRESTOKENVALIDATOR_H


#include <pqxx/connection>
#include "TokenValidator.h"

class PostgresTokenValidator : public TokenValidator {
public:
    bool validateClientSecret(const std::string &clientId, const std::string &clientSecret) override;

    bool validateRefreshToken(const std::string &userName, const std::string &refreshToken) override;

    bool validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                     const std::string &scope) override;

    PostgresTokenValidator(std::string jwtSecret, pqxx::connection &connection,
                           std::vector<spdlog::sink_ptr> logSinks = std::vector<spdlog::sink_ptr>());
};


#endif //LINUXHAZI_POSTGRESTOKENVALIDATOR_H
