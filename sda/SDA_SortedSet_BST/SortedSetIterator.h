//
// Created by razvan on 27.05.2019.
//

#ifndef SDA7_SORTEDSETITERATOR_H
#define SDA7_SORTEDSETITERATOR_H

#include "SortedSet.h"
#include <stack>
#include "BSTNode.h"

class SortedSet;
typedef int TComp;

class SortedSetIterator {
    friend class SortedSet;

private:
    const SortedSet& set;
    BSTNode* currentNode;
    std::stack <BSTNode*> stack;
    SortedSetIterator(const SortedSet& set);

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


#endif //SDA7_SORTEDSETITERATOR_H
