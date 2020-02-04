//
// Created by razvan on 17.04.2019.
//

#ifndef OOP5_COMPARATORDESCENDINGBYLIKES_H
#define OOP5_COMPARATORDESCENDINGBYLIKES_H

#include "../domain/movie.h"
#include "comparator.h"

class ComparatorDescendingByLikes: public Comparator<Movie> {
public:
    bool compare(const Movie& movie1, const Movie& movie2) const;
};


#endif //OOP5_COMPARATORDESCENDINGBYLIKES_H
