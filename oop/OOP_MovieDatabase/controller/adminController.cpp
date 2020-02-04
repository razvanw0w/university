#include "adminController.h"
#include "../utils/movieValidator.h"

/**
 * AdminController constructor
 * @param repository: Repository& - the working repository
 */
AdminController::AdminController(Repository &repository) : repository(repository) {}

/**
 * This function adds a movie into the database as admin
 * @param title: const std::string& - the title of the movie
 * @param genre: const std::string& - the genre of the movie
 * @param yearOfRelease: int - the year of release of the movie
 * @param numberOfLikes: int - the number of likes of the movie
 * @param trailer: const std::string& - the link to the trailer of the movie
 */
void AdminController::adminAddMovie(const std::string &title, const std::string &genre, int yearOfRelease, int numberOfLikes,
                               const std::string &trailer) {
    Movie movie{title, genre, yearOfRelease, numberOfLikes, trailer};
    MovieValidator::validateMovie(movie);
    repository.addMovie(movie);
}

/**
 * This function deletes a movie from the database as admin
 * @param title: const std::string& - the title of the movie
 * @param genre: const std::string& - the genre of the movie
 * @param yearOfRelease: int - the year of release of the movie
 */
void AdminController::adminDeleteMovie(const std::string &title, const std::string &genre, int yearOfRelease) {
    Movie movie{title, genre, yearOfRelease, 0, "https://dummy.link"};
    MovieValidator::validateMovie(movie);
    repository.deleteMovie(movie);
}

/**
 * This function updates a movie from the database as admin
 * @param title: const std::string& - the title of the movie
 * @param genre: const std::string& - the genre of the movie
 * @param yearOfRelease: int - the year of release of the movie
 * @param numberOfLikes: int - the number of likes of the movie
 * @param trailer: const std::string& - the link to the trailer of the movie
 */
void AdminController::adminUpdateMovie(const std::string &title, const std::string &genre, int yearOfRelease,
                                       int numberOfLikes, const std::string &trailer) {
    Movie movie{title, genre, yearOfRelease, numberOfLikes, trailer};
    MovieValidator::validateMovie(movie);
    repository.updateMovie(movie);
}

/**
 * This function returns a list with all the movies in the database
 * @return: list: DynamicArray<Movie> - the list of movies
 */
std::vector<Movie> AdminController::adminGetMovieList() {
    int size = repository.getNumberOfMovies();
    std::vector<Movie> list;
    Movie movie;
    for (int i = 0; i < size; ++i) {
        movie = repository.getMovieAtIndex(i);
        list.push_back(movie);
    }
    return list;
}

void AdminController::sortMoviesByCriteria(std::vector<Movie>& movieList, const Comparator<Movie> &comparator) {
    std::sort(movieList.begin(), movieList.end(), [&comparator](const Movie& movie1, const Movie& movie2){return comparator.compare(movie1, movie2);});
}
