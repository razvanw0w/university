//
// Created by razvan on 17.04.2019.
//

#include "comparatorAscendingByTitle.h"

bool ComparatorAscendingByTitle::compare(const Movie &movie1, const Movie &movie2) const {
    return movie1.getTitle() < movie2.getTitle();
}
