#pragma once
#include "SetIterator.h"
#include <climits>

typedef int TElem;

class SetIterator;

class Set {
    friend class SetIterator;
private:
    TElem *hashTable;
    int *nextNode;
    int numberOfElements;
    int hashTableCapacity;
    int firstFreePosition;

    bool needsReadjustment();
    void readjust();
    int hash(TElem elem) const;
    double computeLoadFactor() const;
    void updateFirstFreePosition();

public:
    const double MAXIMUM_LOAD_FACTOR = 0.65;
    const TElem NULL_TELEM = -1e9;
    const int NULL_NEXT = -1;

    //implicit constructor
    Set();

    //adds an element to the  set
    //if the element was added, the operation returns true, otherwise (if the element was already in the set)
    //it returns false
    // complexity: O(n), but on average case it's an amortized Theta(1)
    bool add(TElem e);

    //removes an element from the set
    //if the element was removed, it returns true, otherwise false
    // complexity: O(n)
    bool remove(TElem e);

    //checks if an element is in the  set
    // complexity: O(n), but on average case it's an amortized Theta(1)
    bool search(TElem elem) const;

    //returns the number of elements;
    // complexity: Theta(1)
    int size() const;

    //checks if the set is empty
    // complexity: Theta(1)
    bool isEmpty() const;

    //returns an iterator for the set
    // complexity: Theta(1)
    SetIterator iterator() const;

    void setUnion(const Set& s);

    //destructor
    ~Set();
};
