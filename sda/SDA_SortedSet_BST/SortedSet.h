//
// Created by razvan on 27.05.2019.
//

#ifndef SDA7_SORTEDSET_H
#define SDA7_SORTEDSET_H
#include "SortedSetIterator.h"
#include "BSTNode.h"

typedef int TComp;
typedef bool(*Relation)(TComp, TComp);

class SortedSetIterator;

class SortedSet {
    friend class SortedSetIterator;

private:
    BSTNode *root;
    int numberOfElements;
    Relation rel;

    BSTNode* getMinimum(BSTNode* startingRoot);
    BSTNode* getMaximum(BSTNode* startingRoot);
    BSTNode* removeRecursively(BSTNode* node, TComp e, bool &removed);

public:
    //constructor
    SortedSet(Relation r);

    //adds an element to the sorted set
    //if the element was added, the operation returns true, otherwise (if the element was already in the set)
    //it returns false
    bool add(TComp e);

    //removes an element from the sorted set
    //if the element was removed, it returns true, otherwise false
    bool remove(TComp e);

    //checks if an element is in the sorted set
    bool search(TComp elem) const;

    //returns the number of elements from the sorted set
    int size() const;

    //checks if the sorted set is empty
    bool isEmpty() const;

    //returns an iterator for the sorted set
    SortedSetIterator iterator() const;

    // destructor
    ~SortedSet();

    void postOrderDeletion(BSTNode *node);
};

#endif //SDA7_SORTEDSET_H
