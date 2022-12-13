#ifndef LINUXHAZI_LOGINVALIDATOR_H
#define LINUXHAZI_LOGINVALIDATOR_H


#include <map>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

namespace LoginValidation {
    class LoginValidator {
    public:

        /***
         * @return  true if credentials are correct, false otherwise
         */
        virtual bool checkCredentials(std::map<std::string, std::string> credentialMap) = 0;

        /***
         * Generic, minimal representation of an user
         */
        class User {
        protected:
            ///The display name of the user
            std::string displayName;
            ///The email adddress of the user
            std::string email;

        public:
            const std::string &getDisplayName() const {
                return displayName;
            }

            const std::string &getEmail() const {
                return email;
            }
        };

    protected:
        ///Internal storage for log sinks
        std::vector<spdlog::sink_ptr> logSinks;
        spdlog::logger logger;

        ///Protected constructor
        LoginValidator(std::vector<spdlog::sink_ptr> logSinks) : logSinks(logSinks), logger("GenericLoginValidator") {
            logger.sinks().insert(logger.sinks().end(), logSinks.begin(), logSinks.end());
        };
    };
}

#endif //LINUXHAZI_LOGINVALIDATOR_H
