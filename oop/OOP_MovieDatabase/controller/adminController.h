#ifndef OOP5_ADMINCONTROLLER_H
#define OOP5_ADMINCONTROLLER_H


#include "../repository/repository.h"
#include "../utils/comparator.h"

class AdminController {
private:
    Repository& repository;

public:
    explicit AdminController(Repository &repository);
    void adminAddMovie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer);
    void adminDeleteMovie(const std::string& title, const std::string& genre, int yearOfRelease);
    void adminUpdateMovie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer);
    std::vector<Movie> adminGetMovieList();
    static void sortMoviesByCriteria(std::vector<Movie>& movieList, const Comparator<Movie>& comparator);
};


#endif //OOP5_ADMINCONTROLLER_H
