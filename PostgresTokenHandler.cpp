//
// Created by helaslo on 2022.12.13..
//

#include "PostgresTokenHandler.h"

bool PostgresTokenHandler::validateClientSecret(const std::string &clientId, const std::string &clientSecret) {
    return false;
}

bool PostgresTokenHandler::validateRefreshToken(const std::string &userName, const std::string &refreshToken) {
    return false;
}

bool PostgresTokenHandler::validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                                       const std::string &scope) {
    return TokenHandler::validateAccessTokenForScope(userName, accessToken, scope);
}

PostgresTokenHandler::PostgresTokenHandler(std::string jwtSecret, pqxx::connection &connection,
                                           std::vector<spdlog::sink_ptr> logSinks)
        : TokenHandler(jwtSecret, logSinks, "PostgresTokenHandler") {

}
