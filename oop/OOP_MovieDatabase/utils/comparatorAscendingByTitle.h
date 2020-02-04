//
// Created by razvan on 17.04.2019.
//

#ifndef OOP5_COMPARATORASCENDINGBYTITLE_H
#define OOP5_COMPARATORASCENDINGBYTITLE_H

#include "../domain/movie.h"
#include "comparator.h"

class ComparatorAscendingByTitle: public Comparator<Movie> {
public:
    bool compare(const Movie& movie1, const Movie& movie2) const;
};


#endif //OOP5_COMPARATORASCENDINGBYTITLE_H
