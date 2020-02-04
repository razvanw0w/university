//
// Created by razvan on 15.04.2019.
//

#ifndef OOP5_VALIDATIONEXCEPTION_H
#define OOP5_VALIDATIONEXCEPTION_H

#include <exception>
#include <string>

class ValidationException: public std::exception {
private:
    std::string message;
    std::string error;

public:
    ValidationException(std::string message = "");
    const char* what() const noexcept override;
};


#endif //OOP5_ValidationEXCEPTION_H
