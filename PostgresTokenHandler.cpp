//
// Created by helaslo on 2022.12.13..
//

#include <pqxx/transaction>
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
        : TokenHandler(jwtSecret, logSinks, "PostgresTokenHandler"), connection(connection) {

}

void PostgresTokenHandler::registerClientSecret(const std::string &clientId, const std::string &clientSecret) {
    auto sql = fmt::format("INSERT INTO \"clients\" (\"clientid\", \"clientsecret\") VALUES ('{0}', '{1}')",
                           connection.esc(clientId),
                           connection.esc(clientSecret));
    pqxx::work work(connection);
    work.exec(sql);
    work.commit();
}

void PostgresTokenHandler::registerRefreshToken(const std::string &userName, const std::string &refreshToken,
                                                const std::string &scopes) {
    auto sql = fmt::format(
            "INSERT INTO \"refreshTokens\" (\"scope\", \"token\", \"userId\") VALUES ('{1}', '{2}', (SELECT \"id\" FROM users WHERE \"username\"='{0}'))",
            connection.esc(userName), connection.esc(refreshToken), connection.esc(scopes));
    pqxx::work work(connection);
    work.exec(sql);
    work.commit();
}

bool PostgresTokenHandler::validateClientSecret(const std::string &clientId, const std::string &clientSecret) {
    using namespace pqxx;
    auto sql = fmt::format("SELECT * from clients WHERE clientid='{}' AND clientsecret='{}' ", connection.esc(clientId),
                           connection.esc(clientSecret));
    nontransaction sqlNonTransactQuery(connection);
    result queryResult(sqlNonTransactQuery.exec(sql));
    return !queryResult.empty();
}
