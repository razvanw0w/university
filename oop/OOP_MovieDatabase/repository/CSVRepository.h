//
// Created by razvan on 16.04.2019.
//

#ifndef OOP5_CSVREPOSITORY_H
#define OOP5_CSVREPOSITORY_H

#include <string>
#include "../domain/movie.h"
#include "repository.h"

class CSVRepository: public Repository {
private:
    std::string CSVfileName;
    void updateCSVFile();

public:
    CSVRepository(const std::string& movieFileName, const std::string& CSVfileName = "");
    void addMovieToWatchlist(const Movie& movie) override;
    void deleteMovieFromWatchlist(const Movie& movie) override;
    std::string getExternalFilename() override;
    ~CSVRepository();
};


#endif //OOP5_CSVREPOSITORY_H
