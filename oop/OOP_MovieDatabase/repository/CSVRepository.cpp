//
// Created by razvan on 16.04.2019.
//

#include <sstream>
#include <fstream>
#include "CSVRepository.h"

/**
 * This function updated a CSV file
 */
void CSVRepository::updateCSVFile() {
    std::ostringstream out;
    out << "Title,Genre,Year of release,Number of likes, Trailer link\n";
    for (const Movie& movie: userWatchList) {
        out << movie.getCSVString() << '\n';
    }
    std::ofstream fout(CSVfileName);
    fout << out.str();
    fout.close();
}

/**
 * CSVRepository constructor
 * @param movieFileName: const std::string& - the large database file name
 * @param CSVfileName: const std::string& - the filename of the csv file
 */
CSVRepository::CSVRepository(const std::string &movieFileName, const std::string &CSVfileName): Repository{movieFileName}, CSVfileName{CSVfileName}
{}

/**
 * This function adds a movie to the watchlist
 * @param movie: const Movie& movie
 */
void CSVRepository::addMovieToWatchlist(const Movie &movie) {
    Repository::addMovieToWatchlist(movie);
    updateCSVFile();
}

/**
 * This function deletes a movie from watchlist
 * @param movie: const Movie& movie
 */
void CSVRepository::deleteMovieFromWatchlist(const Movie &movie) {
    Repository::deleteMovieFromWatchlist(movie);
    updateCSVFile();
}

/**
 * destructor
 */
CSVRepository::~CSVRepository() {
    updateCSVFile();
}

std::string CSVRepository::getExternalFilename() {
    return CSVfileName;
}
