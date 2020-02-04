//
// Created by razvan on 27.03.2019.
//

#include "userController.h"
#include "../utils/movieValidator.h"

UserController::UserController(Repository &repository, std::string repositoryType, int currentMovieIndex): repository {repository}, repositoryType{repositoryType}, currentMovieIndex {currentMovieIndex}, currentMoviesByGenre{std::vector<Movie>{}}{

}

void UserController::listMoviesByGenre(const std::string &genre) {
    currentMoviesByGenre = repository.getMoviesByGenre(genre);
    if (currentMoviesByGenre.size() == 0)
        throw std::runtime_error("no movies of specified genre");
    currentMovieIndex = 0;
}

void UserController::addMovieToWatchlist() {
    repository.addMovieToWatchlist(currentMoviesByGenre[currentMovieIndex]);
}

void UserController::goToNextMovieByGenre() {
    currentMovieIndex = (currentMovieIndex + 1) % currentMoviesByGenre.size();
}

void UserController::deleteMovieFromWatchlist(const std::string &title, const std::string &genre, int yearOfRelease,
                                              bool liked) {
    Movie movie = repository.getMovieByTitleGenreYear(title, genre, yearOfRelease);
    MovieValidator::validateMovie(movie);
    int numberOfLikes = movie.getNumberOfLikes();
    if (liked)
        ++numberOfLikes;
    movie.setNumberOfLikes(numberOfLikes);
    repository.updateMovie(movie);
    repository.deleteMovieFromWatchlist(movie);
}

Movie UserController::getWatchlistMovieByIndex(int index) {
    return repository.getWatchlistMovieAtIndex(index);
}

int UserController::getWatchlistLength() {
    return repository.getNumberOfMoviesInWatchlist();
}

Movie UserController::getCurrentMovie() {
    return currentMoviesByGenre[currentMovieIndex];
}

bool UserController::isRepositoryCSV() const {
    return repositoryType == "CSV";
}

bool UserController::isRepositoryHTML() const {
    return repositoryType == "HTML";
}

std::string UserController::getExternalFilename() const {
    return repository.getExternalFilename();
}
