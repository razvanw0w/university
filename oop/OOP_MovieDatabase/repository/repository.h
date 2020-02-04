#ifndef OOP5_REPOSITORY_H
#define OOP5_REPOSITORY_H

#include "../utils/dynamicarray.h"
#include "../domain/movie.h"
#include <vector>
#include <algorithm>

class Repository {
protected:
    std::vector<Movie> movieList;
    std::vector<Movie> userWatchList;
    std::string movieFileName;
    void loadMoviesFromFile();
    void writeMoviesToFile();

public:
    Repository(const std::string& fileName = "");
    void addMovie(const Movie& movie);
    void deleteMovie(const Movie& movie);
    void updateMovie(const Movie& movie);
    Movie getMovieAtIndex(int index);
    std::vector<Movie> getMoviesByGenre(const std::string& genre);
    int getNumberOfMovies();
    int getNumberOfMoviesInWatchlist();
    Movie getMovieByTitleGenreYear(const std::string& title, const std::string& genre, int year);
    virtual void addMovieToWatchlist(const Movie& movie);
    virtual void deleteMovieFromWatchlist(const Movie& movie);
    Movie getWatchlistMovieAtIndex(int index);
    virtual std::string getExternalFilename();
    virtual ~Repository();
};


#endif //OOP5_REPOSITORY_H
