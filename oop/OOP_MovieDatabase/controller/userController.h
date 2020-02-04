//
// Created by razvan on 27.03.2019.
//

#ifndef OOP5_USERCONTROLLER_H
#define OOP5_USERCONTROLLER_H


#include "../repository/repository.h"
#include <stdexcept>

class UserController {
private:
    Repository& repository;
    int currentMovieIndex;
    std::vector<Movie> currentMoviesByGenre;
    std::string repositoryType;

public:
    UserController(Repository& repository, std::string repositoryType = "", int currentMovieIndex = 0);
    void listMoviesByGenre(const std::string& genre);
    void addMovieToWatchlist();
    void goToNextMovieByGenre();
    void deleteMovieFromWatchlist(const std::string& title, const std::string& genre, int yearOfRelease, bool liked);
    Movie getWatchlistMovieByIndex(int index);
    Movie getCurrentMovie();
    int getWatchlistLength();
    bool isRepositoryCSV() const;
    bool isRepositoryHTML() const;
    std::string getExternalFilename() const;
};


#endif //OOP5_USERCONTROLLER_H
