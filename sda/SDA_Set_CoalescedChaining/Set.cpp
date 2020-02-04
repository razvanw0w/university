#include <iostream>
#include "Set.h"

Set::Set(): hashTableCapacity{10}, numberOfElements{0}, firstFreePosition{0} {
    hashTable = new TElem[10];
    nextNode = new TElem[10];
    for (int i = 0; i < hashTableCapacity; ++i) {
        hashTable[i] = NULL_TELEM;
        nextNode[i] = NULL_NEXT;
    }
}

bool Set::add(TElem e) {
    int insertPosition = hash(e);
    if (needsReadjustment()) {
        readjust();
    }
    if (hashTable[insertPosition] == NULL_TELEM) {
        hashTable[insertPosition] = e;
        nextNode[insertPosition] = NULL_NEXT;
        if (firstFreePosition == insertPosition)
            updateFirstFreePosition();
    }
    else {
        int currentNode = insertPosition;
        bool foundElement = false;
        while (nextNode[currentNode] != NULL_NEXT && foundElement == false) {
            if (hashTable[currentNode] == e) {
                foundElement = true;
            }
            currentNode = nextNode[currentNode];
        }
        if (foundElement == true)
            return false;
        if (hashTable[currentNode] == e)
            return false;
        hashTable[firstFreePosition] = e;
        nextNode[firstFreePosition] = NULL_NEXT;
        nextNode[currentNode] = firstFreePosition;
        updateFirstFreePosition();
    }
    ++numberOfElements;
    return true;
}

bool Set::remove(TElem e) {
    int actualNode = hash(e);
    int previousNode = NULL_NEXT;
    int index = 0;

    /*while (index < hashTableCapacity && previousNode == NULL_NEXT) {
        if (nextNode[index] == actualNode) {
            previousNode = index;
        }
        ++index;
    }*/

    while (actualNode != NULL_NEXT && hashTable[actualNode] != e) {
        previousNode = actualNode;
        actualNode = nextNode[actualNode];
    }

    if (actualNode == NULL_NEXT) { // we didn't find the element in the set
        return false;
    }
    else {
        bool doneMoving = false;
        do {
            int currentPos = nextNode[actualNode];
            int previousPos = actualNode;

            while (currentPos != NULL_NEXT && hash(hashTable[currentPos]) != actualNode) {
                previousPos = currentPos;
                currentPos = nextNode[currentPos];
            }

            if (currentPos == NULL_NEXT) {
                doneMoving = true;
            }
            else {
                hashTable[actualNode] = hashTable[currentPos];
                actualNode = currentPos;
                previousNode = previousPos;
            }
        } while (doneMoving == false);

        if (previousNode != NULL_NEXT) {
            nextNode[previousNode] = nextNode[actualNode];
        }
        hashTable[actualNode] = NULL_TELEM;
        nextNode[actualNode] = NULL_NEXT;
        if (actualNode < firstFreePosition) {
            firstFreePosition = actualNode;
        }
    }
    --numberOfElements;
    return true;
}

bool Set::search(TElem elem) const {
    int currentNode = hash(elem);
    while (currentNode != NULL_NEXT) {
        if (hashTable[currentNode] == elem) {
            return true;
        }
        currentNode = nextNode[currentNode];
    }
    return false;
}

int Set::size() const {
    return numberOfElements;
}

bool Set::isEmpty() const {
    return numberOfElements == 0;
}

SetIterator Set::iterator() const {
    return SetIterator{*this};
}

Set::~Set() {
    delete[] hashTable;
    delete[] nextNode;
}

bool Set::needsReadjustment() {
    return computeLoadFactor() >= MAXIMUM_LOAD_FACTOR;
}

void Set::readjust() {
    TElem *oldElements = new TElem[numberOfElements];
    for (int i = 0; i < numberOfElements; ++i) {
        oldElements[i] = NULL_TELEM;
    }
    int currentAppendIndex = 0;
    for (int i = 0; i < hashTableCapacity; ++i) {
        if (hashTable[i] != NULL_TELEM) {
            oldElements[currentAppendIndex++] = hashTable[i];
        }
    }

    hashTableCapacity *= 2;
    TElem *newHashTable = new TElem[hashTableCapacity];
    int *newNextNode = new int[hashTableCapacity];
    for (int i = 0; i < hashTableCapacity; ++i) {
        newHashTable[i] = NULL_TELEM;
        newNextNode[i] = NULL_NEXT;
    }
    delete[] hashTable;
    delete[] nextNode;
    hashTable = newHashTable;
    nextNode = newNextNode;

    firstFreePosition = 0;
    int oldNumberOfElements = numberOfElements;
    numberOfElements = 0;
    for (int i = 0; i < oldNumberOfElements; ++i) {
        add(oldElements[i]);
    }
    delete[] oldElements;
}

int Set::hash(TElem elem) const {
    if (elem < 0)
        elem *= -1;
    return elem % hashTableCapacity;
}

double Set::computeLoadFactor() const {
    return (1.0 * numberOfElements) / (1.0 * hashTableCapacity);
}

void Set::updateFirstFreePosition() {
    ++firstFreePosition;
    while (firstFreePosition < hashTableCapacity && hashTable[firstFreePosition] != NULL_TELEM)
        ++firstFreePosition;
}

/**
 * Complexity: Theta(M)
 * M = number of elements of second set
 *
 * subalgorithm setUnion(s1, s2) is:
 * // pre: s1, s2 are sets
 * // post: s1' <- s1 U s2
 *
 * for i <- 0, s2.hashTableCapacity - 1 execute:
 *      if s2.hashTable[i] =/= NULL_TELEM then
 *          add(s1, s2.hashTable[i])
 *      end-if
 * end-for
 */
void Set::setUnion(const Set &s) {
    for (int i = 0; i < s.hashTableCapacity; ++i) {
        if (s.hashTable[i] != NULL_TELEM) {
            add(s.hashTable[i]);
        }
    }
}
