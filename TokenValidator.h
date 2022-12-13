
#ifndef LINUXHAZI_TOKENVALIDATOR_H
#define LINUXHAZI_TOKENVALIDATOR_H

#include <spdlog/logger.h>
#include "jwt/jwt.hpp"

class TokenValidator {
protected:
    std::vector<spdlog::sink_ptr> logSinks;
    spdlog::logger logger;

    TokenValidator(const std::vector<spdlog::sink_ptr> &logSinks = std::vector<spdlog::sink_ptr>(),
                   const std::string loggerName = "GenericTokenValidator") : logSinks(logSinks),
                                                                             logger(loggerName) {
        logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
    };

public:
    virtual bool validateClientSecret(const std::string &clientId, const std::string &clientSecret) = 0;

    virtual bool validateRefreshToken(const std::string &userName, const std::string &refreshToken) = 0;

    virtual bool validateAccessTokenForScope(const std::string &userName, const std::string &accessToken,
                                             const std::string &scope) = 0;
};

#endif //LINUXHAZI_TOKENVALIDATOR_H
