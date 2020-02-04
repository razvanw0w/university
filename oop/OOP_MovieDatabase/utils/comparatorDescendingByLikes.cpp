//
// Created by razvan on 17.04.2019.
//

#include "comparatorDescendingByLikes.h"

bool ComparatorDescendingByLikes::compare(const Movie &movie1, const Movie &movie2) const {
    return movie1.getNumberOfLikes() > movie2.getNumberOfLikes();
}
