//
// Created by razvan on 25.03.2019.
//

#include <fstream>
#include "repository.h"
#include "../exceptions/repositoryException.h"

/**
 * This function adds a movie to the repository movie list
 * @param movie: const Movie& - the movie to be added
 * @except: throws RepositoryException if the movie already exists in the list
 */
void Repository::addMovie(const Movie &movie) {
    if (std::find(movieList.begin(), movieList.end(), movie) != movieList.end())
        throw RepositoryException(std::string("movie already existing"));
    movieList.push_back(movie);
    writeMoviesToFile();
}

/**
 * This function deletes a movie from the repository list
 * @param movie: const Movie& - the movie to be deleted
 * @except: throws RepositoryException if the movie doesn't exist
 */
void Repository::deleteMovie(const Movie &movie) {
    auto it = std::find(movieList.begin(), movieList.end(), movie);
    if (it == movieList.end())
        throw RepositoryException(std::string("movie doesn't exist"));
    movieList.erase(it);
    writeMoviesToFile();
}

/**
 * This function updates a movie form the repository list
 * @param movie: const Movie& - the movie to be updated
 * @except: throws RepositoryException if the movie doesn't exist
 */
void Repository::updateMovie(const Movie &movie) {
    auto it = std::find(movieList.begin(), movieList.end(), movie);
    if (it == movieList.end())
        throw RepositoryException(std::string("nothing to update"));
    *it = movie;
    writeMoviesToFile();
}

/**
 * This function returns a movie at a specified index
 * @param index: int - the desired index
 * @return: Movie - the movie at the index 'index'
 */
Movie Repository::getMovieAtIndex(int index) {
    if (index < 0 || index >= movieList.size()) {
        throw RepositoryException(std::string("bad index"));
    }
    return movieList[index];
}

/**
 * This function returns the number of movies which are stored in the database
 * @return: int - the number of movies in the database
 */
int Repository::getNumberOfMovies() {
    return movieList.size();
}

Repository::Repository(const std::string& fileName): movieList{std::vector<Movie>{}}, userWatchList{std::vector<Movie>{}}, movieFileName{fileName}{
    loadMoviesFromFile();
}

/**
 * This function adds a movie to the watchlist
 * @param movie: const Movie& - the movie to be added
 */
void Repository::addMovieToWatchlist(const Movie &movie) {
    auto it = std::find(userWatchList.begin(), userWatchList.end(), movie);
    if (it != userWatchList.end())
        throw RepositoryException(std::string("movie already in watchlist"));
    userWatchList.push_back(movie);
}

void Repository::deleteMovieFromWatchlist(const Movie &movie) {
    auto it = std::find(userWatchList.begin(), userWatchList.end(), movie);
    if (it == userWatchList.end())
        throw RepositoryException(std::string("movie doesn't exist"));
    userWatchList.erase(it);
}

Movie Repository::getWatchlistMovieAtIndex(int index) {
    if (index < 0 || index >= userWatchList.size()) {
        throw RepositoryException(std::string("bad index"));
    }
    return userWatchList[index];
}

int Repository::getNumberOfMoviesInWatchlist() {
    return userWatchList.size();
}

std::vector<Movie> Repository::getMoviesByGenre(const std::string &genre) {
    std::vector<Movie> moviesOfGenre;
    std::copy_if(movieList.begin(), movieList.end(), std::back_inserter(moviesOfGenre), [&genre](const Movie& movie){return movie.getGenre() == genre;});
    return moviesOfGenre;
}

Movie Repository::getMovieByTitleGenreYear(const std::string &title, const std::string &genre, int year) {
    Movie movie{title, genre, year, 0, ""};
    auto it = std::find(movieList.begin(), movieList.end(), movie);
    if (it == movieList.end())
        throw RepositoryException(std::string("inexisting movie"));
    return getMovieAtIndex(it - movieList.begin());
}

void Repository::loadMoviesFromFile() {
    if (movieFileName == "")
        return;
    Movie movie;
    std::ifstream fin(movieFileName);
    while (fin >> movie) {
        movieList.push_back(movie);
    }
    fin.close();
}

void Repository::writeMoviesToFile() {
    if (movieFileName == "")
        return;
    std::ofstream fout(movieFileName);
    for (const Movie& movie: movieList) {
        fout << movie << '\n';
    }
    fout.close();
}

Repository::~Repository() {
    writeMoviesToFile();
}

std::string Repository::getExternalFilename() {
    return "";
}
