//
// Created by razvan on 30.03.2019.
//

#include "ListIterator.h"
//#include "IteratedList.h"
#include <stdexcept>

void ListIterator::first() {
    currentNode = list.head;
}

void ListIterator::next() {
    if (!valid()) {
        throw std::runtime_error("error");
    }
    currentNode = currentNode->getNext();
}

bool ListIterator::valid() const {
    return currentNode != nullptr;
}

TElem ListIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error("error");
    }
    return currentNode->getElement();
}

bool ListIterator::operator==(const ListIterator &rhs) const {
    return &list == &rhs.list && currentNode == rhs.currentNode;
}

bool ListIterator::operator!=(const ListIterator &rhs) const {
    return !(rhs == *this);
}

ListIterator::ListIterator(const IteratedList &list) : list(list) {
    if (list.isEmpty())
        currentNode = nullptr;
    else
        currentNode = list.head;
}