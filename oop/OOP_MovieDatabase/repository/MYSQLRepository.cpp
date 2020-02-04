//
// Created by razvan on 21.04.2019.
//

#include "MYSQLRepository.h"


void MYSQLRepository::updateWatchlistFromDatabase() {
    sql::Statement *statement = connection->createStatement();
    sql::ResultSet *resultSet = statement->executeQuery("SELECT * FROM watchlist");

    std::vector <Movie> newWatchlist;
    std::string title, genre, yearString, likesString, trailer;
    int year, likes;
    while (resultSet->next()) {
        title = resultSet->getString(1);
        genre = resultSet->getString(2);
        year = resultSet->getInt(3);
        likes = resultSet->getInt(4);
        trailer = resultSet->getString(5);
        newWatchlist.push_back(Movie{title, genre, year, likes, trailer});
    }
    delete resultSet;
    delete statement;
    Repository::userWatchList = newWatchlist;
}

MYSQLRepository::MYSQLRepository(const std::string& movieFilename): Repository{movieFilename} {
    driver = get_driver_instance();
    connection = driver->connect("tcp://127.0.0.1:3306", "razvan", "razvi");
    connection->setSchema("watchlist");
}

void MYSQLRepository::addMovieToWatchlist(const Movie &movie) {
    updateWatchlistFromDatabase();
    Repository::addMovieToWatchlist(movie);
    addMovieToDatabase(movie);
}

void MYSQLRepository::deleteMovieFromWatchlist(const Movie &movie) {
    updateWatchlistFromDatabase();
    Repository::deleteMovieFromWatchlist(movie);
    deleteMovieFromDatabase(movie);
}

MYSQLRepository::~MYSQLRepository() {
    delete connection;
}

void MYSQLRepository::addMovieToDatabase(const Movie &movie) {
    sql::PreparedStatement *preparedStatement;
    preparedStatement = connection->prepareStatement("INSERT INTO watchlist VALUES (?, ?, ?, ?, ?)");
    preparedStatement->setString(1, movie.getTitle());
    preparedStatement->setString(2, movie.getGenre());
    preparedStatement->setInt(3, movie.getYearOfRelease());
    preparedStatement->setInt(4, movie.getNumberOfLikes());
    preparedStatement->setString(5, movie.getTrailer());
    preparedStatement->execute();

    delete preparedStatement;
}

void MYSQLRepository::deleteMovieFromDatabase(const Movie &movie) {
    sql::PreparedStatement *preparedStatement;
    preparedStatement = connection->prepareStatement("DELETE FROM watchlist WHERE title=? AND genre=? AND yearOfRelease=?");
    preparedStatement->setString(1, movie.getTitle());
    preparedStatement->setString(2, movie.getGenre());
    preparedStatement->setInt(3, movie.getYearOfRelease());
    preparedStatement->execute();

    delete preparedStatement;
}
