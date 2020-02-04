#pragma once
#include "Set.h"

class Set;
typedef int TElem;

class SetIterator {
    friend class Set;
private:
    //Constructor receives a reference of the Set.
    //after creation the iterator will refer to the first element of the Set, or it will be invalid if the Set is empty
    SetIterator(const Set& c);

    //contains a reference of the Set it iterates over
    const Set& c;
    int currentIndex;
    /* representation specific for the iterator*/

public:
    //sets the iterator to the first element of the Set
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
