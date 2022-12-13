#ifndef LINUXHAZI_LOGINVALIDATOR_H
#define LINUXHAZI_LOGINVALIDATOR_H


#include <map>
#include <string>
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
        public:
            ///The display name of the user
            std::string displayName;
            ///The email adddress of the user
            std::string email;
        };
    };
}

#endif //LINUXHAZI_LOGINVALIDATOR_H
