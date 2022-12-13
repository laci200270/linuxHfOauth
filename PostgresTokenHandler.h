#ifndef LINUXHAZI_POSTGRESTOKENHANDLER_H
#define LINUXHAZI_POSTGRESTOKENHANDLER_H


#include <pqxx/connection>
#include "TokenHandler.h"

class PostgresTokenHandler : public TokenHandler {
private:
    pqxx::connection &connection;
public:
    bool validateClientSecret(const std::string &clientId, const std::string &clientSecret) override;

    bool validateRefreshToken(const std::string &userName, const std::string &refreshToken) override;


    PostgresTokenHandler(std::string jwtSecret, pqxx::connection &connection,
                         std::vector<spdlog::sink_ptr> logSinks = std::vector<spdlog::sink_ptr>());

    void registerClientSecret(const std::string &clientId, const std::string &clientSecret) override;

    void registerRefreshToken(const std::string &userName, const std::string &refreshToken,
                              const std::string &scopes) override;
};


#endif //LINUXHAZI_POSTGRESTOKENHANDLER_H
