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
        virtual bool checkCredentials(std::map<std::string, std::string>()) = 0;
    };
}

#endif //LINUXHAZI_LOGINVALIDATOR_H
