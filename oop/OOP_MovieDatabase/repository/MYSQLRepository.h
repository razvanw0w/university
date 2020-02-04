//
// Created by razvan on 21.04.2019.
//

#ifndef OOP5_MYSQLREPOSITORY_H
#define OOP5_MYSQLREPOSITORY_H

#include "repository.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MYSQLRepository: public Repository {
private:
    sql::Driver *driver;
    sql::Connection *connection;

    void updateWatchlistFromDatabase();
    void addMovieToDatabase(const Movie& movie);
    void deleteMovieFromDatabase(const Movie& movie);

public:
    MYSQLRepository(const std::string& movieFilename);
    void addMovieToWatchlist(const Movie& movie) override;
    void deleteMovieFromWatchlist(const Movie& movie) override;
    ~MYSQLRepository();
};


#endif //OOP5_MYSQLREPOSITORY_H
