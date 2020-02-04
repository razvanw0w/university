//
// Created by razvan on 13.04.2019.
//

#include <stdexcept>
#include "BagIterator.h"

BagIterator::BagIterator(const Bag &b): bag{b}
{
    first();
}

void BagIterator::first() {
    if (bag.elementsArraySize > 0) {
        currentNode = bag.head;
        currentFrequency = bag.elements[bag.head].getFrequency();
    }
    else {
        currentNode = -1;
    }
}

void BagIterator::next() {
    if (!valid()) {
        throw std::runtime_error("error");
    }
    --currentFrequency;
    if (currentFrequency == 0) {
        currentNode = bag.elements[currentNode].getNext();
        if (currentNode != -1) {
            currentFrequency = bag.elements[currentNode].getFrequency();
        }
    }
}

bool BagIterator::valid() const {
    return currentNode != -1;
}

TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error("error");
    }
    return bag.elements[currentNode].getElement();
}