//
// Created by razvan on 06.05.2019.
//

#include <stdexcept>
#include "SetIterator.h"

SetIterator::SetIterator(const Set &c): c{c}, currentIndex{0} {
    while (currentIndex < c.hashTableCapacity && c.hashTable[currentIndex] == c.NULL_TELEM) {
        ++currentIndex;
    }
}

void SetIterator::first() {
    currentIndex = 0;
    while (currentIndex < c.hashTableCapacity && c.hashTable[currentIndex] == c.NULL_TELEM) {
        ++currentIndex;
    }
}

void SetIterator::next() {
    if (!valid())
        throw std::runtime_error("");
    ++currentIndex;
    while (currentIndex < c.hashTableCapacity && c.hashTable[currentIndex] == c.NULL_TELEM) {
        ++currentIndex;
    }
}

bool SetIterator::valid() const {
    return currentIndex < c.hashTableCapacity;
}

TElem SetIterator::getCurrent() const {
    if (!valid())
        throw std::runtime_error("");
    return c.hashTable[currentIndex];
}