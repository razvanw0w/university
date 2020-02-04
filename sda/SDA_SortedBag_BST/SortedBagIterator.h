#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;
typedef int TComp;

class SortedBagIterator {
    friend class SortedBag;

private:
    const SortedBag& sb;
    int currentNode;
    std::stack<int> stack;
    SortedBagIterator(const SortedBag& sb);

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

    TComp getCurrent() const;

};
