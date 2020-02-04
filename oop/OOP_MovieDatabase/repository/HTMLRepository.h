//
// Created by razvan on 16.04.2019.
//

#ifndef OOP5_HTMLREPOSITORY_H
#define OOP5_HTMLREPOSITORY_H

#include "repository.h"

class HTMLRepository: public Repository {
private:
    std::string HTMLfileName;
    void updateHTMLFile();

public:
    HTMLRepository(const std::string& movieFileName, const std::string& HTMLfileName = "");
    void addMovieToWatchlist(const Movie& movie) override;
    void deleteMovieFromWatchlist(const Movie& movie) override;
    std::string getExternalFilename() override;
    ~HTMLRepository();
};


#endif //OOP5_HTMLREPOSITORY_H
