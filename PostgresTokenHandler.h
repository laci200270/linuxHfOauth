#ifndef LINUXHAZI_POSTGRESTOKENHANDLER_H
#define LINUXHAZI_POSTGRESTOKENHANDLER_H


#include <pqxx/connection>
#include "TokenHandler.h"

class PostgresTokenHandler : public TokenHandler {
public:
    bool validateClientSecret(const std::string &clientId, const std::string &clientSecret) override;

    bool validateRefreshToken(const std::string &userName, const std::string &refreshToken) override;

    bool validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                     const std::string &scope) override;

    PostgresTokenHandler(std::string jwtSecret, pqxx::connection &connection,
                         std::vector<spdlog::sink_ptr> logSinks = std::vector<spdlog::sink_ptr>());
};


#endif //LINUXHAZI_POSTGRESTOKENHANDLER_H
