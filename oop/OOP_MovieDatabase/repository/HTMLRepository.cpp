//
// Created by razvan on 16.04.2019.
//

#include <sstream>
#include <fstream>
#include "HTMLRepository.h"

void HTMLRepository::updateHTMLFile() {
    std::ostringstream out;
    out << "<!DOCTYPE html>\n<html><head><title>Watchlist</title></head><body>\n";
    out << "<table border=\"1\">\n";
    out << "<tr><td>Title</td><td>Genre</td><td>Year of release</td><td>Number of likes</td><td>Link</td></tr>\n";
    for (const Movie& movie: userWatchList) {
        out << movie.getHTMLString() << '\n';
    }
    out << "</table></body></html>";
    std::ofstream fout(HTMLfileName);
    fout << out.str();
    fout.close();
}

HTMLRepository::HTMLRepository(const std::string &movieFileName, const std::string &HTMLfileName): Repository{movieFileName}, HTMLfileName{HTMLfileName}
{}

void HTMLRepository::addMovieToWatchlist(const Movie &movie) {
    Repository::addMovieToWatchlist(movie);
    updateHTMLFile();
}

void HTMLRepository::deleteMovieFromWatchlist(const Movie &movie) {
    Repository::deleteMovieFromWatchlist(movie);
    updateHTMLFile();
}

HTMLRepository::~HTMLRepository() {
    updateHTMLFile();
}

std::string HTMLRepository::getExternalFilename() {
    return HTMLfileName;
}
