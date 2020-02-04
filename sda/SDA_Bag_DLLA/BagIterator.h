//
// Created by razvan on 13.04.2019.
//

#ifndef SDA4_BAGITERATOR_H
#define SDA4_BAGITERATOR_H


#include "Bag.h"

class Bag;

class BagIterator {
    friend class Bag;
private:
    //Constructor receives a reference of the container.
    //after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
    BagIterator(const Bag& b);
    const Bag& bag;
    int currentNode;
    int currentFrequency;

public:
    //sets the iterator to the first element of the container
    void first();

    //moves the iterator to the next element
    //throws exception if the iterator is not valid
    void next();

    //checks if the iterator is valid
    bool valid() const;

    //returns the value of the current element from the iterator
    // throws exception if the iterator is not valid
    TElem getCurrent() const;
};


#endif //SDA4_BAGITERATOR_H
