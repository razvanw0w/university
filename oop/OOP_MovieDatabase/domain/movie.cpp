//
// Created by razvan on 25.03.2019.
//

#include <sstream>
#include <vector>
#include "movie.h"

/**
 * Movie constructor
 * @param title: const std::string& - the title of the movie
 * @param genre: const std::string& - the genre of the movie
 * @param yearOfRelease: int - the year of release of the movie
 * @param numberOfLikes: int - the number of likes of the movie
 * @param trailer: const std::string& - the link to the trailer of the movie
 */
Movie::Movie(const std::string &title, const std::string &genre, int yearOfRelease, int numberOfLikes,
             const std::string &trailer) : title(title), genre(genre), yearOfRelease(yearOfRelease),
                                           numberOfLikes(numberOfLikes), trailer(trailer) {}

/**
 * Movie title getter
 * @return: const std::string& - the title of the movie
 */
const std::string &Movie::getTitle() const {
    return title;
}

/**
 * Movie title setter
 * @param title: const std::string& - the new title of the movie
 */
void Movie::setTitle(const std::string &title) {
    Movie::title = title;
}

/**
 * Movie genre getter
 * @return: const std::string& - the genre of the movie
 */
const std::string &Movie::getGenre() const {
    return genre;
}

/**
 * Movie genre setter
 * @param genre: const std::string& - the new genre of the movie
 */
void Movie::setGenre(const std::string &genre) {
    Movie::genre = genre;
}

/**
 * Movie year of release getter
 * @return: const std::string& - the year of release of the movie
 */
int Movie::getYearOfRelease() const {
    return yearOfRelease;
}

/**
 * Movie yearOfRelease setter
 * @param yearOfRelease: int - the new yearOfRelease of the movie
 */
void Movie::setYearOfRelease(int yearOfRelease) {
    Movie::yearOfRelease = yearOfRelease;
}

/**
 * Movie number of likes getter
 * @return: const std::string& - the number of likes of the movie
 */
int Movie::getNumberOfLikes() const {
    return numberOfLikes;
}

/**
 * Movie numberOfLikes setter
 * @param numberOfLikes: int - the new numberOfLikes of the movie
 */
void Movie::setNumberOfLikes(int numberOfLikes) {
    Movie::numberOfLikes = numberOfLikes;
}

/**
 * Movie trailer link getter
 * @return: const std::string& - the trailer link of the movie
 */
const std::string &Movie::getTrailer() const {
    return trailer;
}

/**
 * Movie trailer link setter
 * @param trailer: const std::string& - the new trailer link of the movie
 */
void Movie::setTrailer(const std::string &trailer) {
    Movie::trailer = trailer;
}

/**
 * Equality operator
 * @param rhs: const Movie& - the right hand side of the equality
 * @return: true if the movies have the same title, genre and year of release
 *          false otherwise
 */
bool Movie::operator==(const Movie &rhs) const {
    return title == rhs.title &&
           genre == rhs.genre &&
           yearOfRelease == rhs.yearOfRelease;
}

/**
 * Nonequality operator
 * @param rhs: const Movie& - the right hand side of the nonequality
 * @return: false if the movies have the same title, genre and year of release
 *          true otherwise
 */
bool Movie::operator!=(const Movie &rhs) const {
    return !(rhs == *this);
}

/**
 * Copy constructor
 * @param otherMovie: const Movie& - another movie to copy from
 */
Movie::Movie(const Movie &otherMovie): title{otherMovie.title},
                                       genre{otherMovie.genre},
                                       yearOfRelease{otherMovie.yearOfRelease},
                                       numberOfLikes{otherMovie.numberOfLikes},
                                       trailer{otherMovie.trailer}
                                       {}



std::ostream& operator<< (std::ostream& outStream, const Movie& movie) {
    outStream << movie.getCSVString();
    return outStream;
}

std::vector<std::string> Movie::tokenizeString(const std::string &movieString) {
    std::vector <std::string> tokens;
    int startPosition = movieString.find("\""), endPosition;
    std::string token;
    while (startPosition != movieString.size() - 1) {
        endPosition = movieString.find("\"", startPosition + 1);
        if (endPosition == movieString.size() - 1 || movieString[endPosition + 1] == ',') {
            token = movieString.substr(startPosition + 1, endPosition - startPosition - 1);
            if (token[0] == ',') {
                token = token.substr(1);
            }
            tokens.push_back(token);
        }
        startPosition = endPosition;
    }
    return tokens;
}

std::istream& operator>> (std::istream& inStream, Movie& movie) {
    std::string movieString;
    std::getline(inStream, movieString);
    std::vector <std::string> tokens;
    if (movieString == "") {
        return inStream;
    }
    tokens = Movie::tokenizeString(movieString);
    movie.title = tokens[0];
    movie.genre = tokens[1];
    movie.yearOfRelease = std::stoi(tokens[2]);
    movie.numberOfLikes = std::stoi(tokens[3]);
    movie.trailer = tokens[4];
    return inStream;
}

/**
 * This function returns the CSV format string of a movie
 * @return: string - the CSV format string of the movie
 */
std::string Movie::getCSVString() const {
    std::ostringstream stream;
    stream << '"' << title << "\","
           << '"' << genre << "\","
           << '"' << yearOfRelease << "\","
           << '"' << numberOfLikes << "\","
           << '"' << trailer << '"';
    return stream.str();
}

/**
 * This function returns a string formatted for the HTML document
 * @return: string - the HTML format string of the movie
 */
std::string Movie::getHTMLString() const {
    std::ostringstream stream;
    stream << "<tr><td>" << title << "</td>"
           << "<td>" << genre << "</td>"
           << "<td>" << yearOfRelease << "</td>"
           << "<td>" << numberOfLikes << "</td>"
           << "<td><a href=\"" << trailer << "\">Link</a></td>";
    return stream.str();
}