//
// Created by razvan on 15.04.2019.
//

#include "movieValidator.h"
#include "../exceptions/validationException.h"

void MovieValidator::validateMovie(const Movie &movie) {
    int likes = movie.getNumberOfLikes();
    int year = movie.getYearOfRelease();
    std::string link = movie.getTrailer();
    std::string error = "";
    if (likes < 0)
        error += "Invalid likes ";
    if (year < 1900 || year > 9999)
        error += "Invalid year ";
    if (link.find("http://") != 0 && link.find("https://") != 0)
        error += "Invalid trailer ";
    if (error != "")
        throw ValidationException(error);
}
