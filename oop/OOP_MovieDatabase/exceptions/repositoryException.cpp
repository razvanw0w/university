//
// Created by razvan on 15.04.2019.
//

#include "repositoryException.h"

RepositoryException::RepositoryException(std::string message): message{message} {
    error = "Repository error: " + message;
}

const char *RepositoryException::what() const noexcept {
    return error.c_str();
}