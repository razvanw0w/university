//
// Created by razvan on 15.04.2019.
//

#ifndef OOP5_REPOSITORYEXCEPTION_H
#define OOP5_REPOSITORYEXCEPTION_H

#include <exception>
#include <string>

class RepositoryException: public std::exception {
private:
    std::string message;
    std::string error;

public:
    RepositoryException(std::string message = "");
    const char* what() const noexcept override;
};


#endif //OOP5_REPOSITORYEXCEPTION_H
