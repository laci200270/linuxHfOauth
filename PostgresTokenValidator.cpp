//
// Created by helaslo on 2022.12.13..
//

#include "PostgresTokenValidator.h"

bool PostgresTokenValidator::validateClientSecret(const std::string &clientId, const std::string &clientSecret) {
    return false;
}

bool PostgresTokenValidator::validateRefreshToken(const std::string &userName, const std::string &refreshToken) {
    return false;
}

bool PostgresTokenValidator::validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                                         const std::string &scope) {
    return TokenValidator::validateAccessTokenForScope(userName, accessToken, scope);
}

PostgresTokenValidator::PostgresTokenValidator(std::string jwtSecret, pqxx::connection &connection,
                                               std::vector<spdlog::sink_ptr> logSinks)
        : TokenValidator(jwtSecret, logSinks, "PostgresTokenValidator") {

}
