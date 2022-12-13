
#ifndef LINUXHAZI_TOKENHANDLER_H
#define LINUXHAZI_TOKENHANDLER_H

#include <spdlog/logger.h>
#include "jwt/jwt.hpp"

class TokenHandler {
protected:
    std::vector<spdlog::sink_ptr> logSinks;
    spdlog::logger logger;
    std::string jwtSecret;

    TokenHandler(const std::string jwtSecret,
                 const std::vector<spdlog::sink_ptr> &logSinks = std::vector<spdlog::sink_ptr>(),
                 const std::string loggerName = "GenericTokenValidator") : jwtSecret(jwtSecret), logSinks(logSinks),
                                                                           logger(loggerName) {
        logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
    };

public:
    virtual bool validateClientSecret(const std::string &clientId, const std::string &clientSecret) = 0;

    virtual void registerClientSecret(const std::string &clientId, const std::string &clientSecret) = 0;

    virtual bool validateRefreshToken(const std::string &userName, const std::string &refreshToken) = 0;

    virtual void
    registerRefreshToken(const std::string &userName, const std::string &refreshToken, const std::string &scopes) = 0;

    bool validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                     const std::string &scope) {
        using namespace jwt::params;
        std::error_code ec;
        auto dec_obj = jwt::decode(accessToken, algorithms({"HS256"}), ec, secret(jwtSecret), verify(true));

        if (ec.value() == 0) {
            if (dec_obj.has_claim("scope")) {
                std::string paramSplitChar = " ", scopes = dec_obj.payload().get_claim_value<std::string>("scope");
                int start, end = -1 * paramSplitChar.size();
                do {
                    start = end + paramSplitChar.size();
                    end = scopes.find(paramSplitChar, start);
                    std::string currLine = scopes.substr(start, end - start);
                    if (currLine == scope) {
                        return true;
                    }
                } while (end != -1);
            }
        }
        return false;
    };
};

#endif //LINUXHAZI_TOKENHANDLER_H
