//
// Created by razvan on 15.04.2019.
//

#include "validationException.h"

ValidationException::ValidationException(std::string message): message{message} {
    error = "Validation error: " + message;
}

const char *ValidationException::what() const noexcept {
    return error.c_str();
}
