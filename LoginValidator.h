#ifndef LINUXHAZI_LOGINVALIDATOR_H
#define LINUXHAZI_LOGINVALIDATOR_H


#include <map>
#include <string>

class LoginValidator {
public:
    LoginValidator();
    /***
     * @return  true if credentials are correct, false otherwise
     */
    bool checkCredentials(std::map<std::string,std::string>());
};


#endif //LINUXHAZI_LOGINVALIDATOR_H
