//
// Created by razvan on 30.03.2019.
//

#include "DLLNode.h"

DLLNode::DLLNode(TElem element, DLLNode *prev, DLLNode *next) : element(element), prev(prev), next(next) {}

TElem DLLNode::getElement() const {
    return element;
}

void DLLNode::setElement(TElem element) {
    this->element = element;
}

DLLNode *DLLNode::getPrev() const {
    return prev;
}

void DLLNode::setPrev(DLLNode *prev) {
    this->prev = prev;
}

DLLNode *DLLNode::getNext() const {
    return next;
}

void DLLNode::setNext(DLLNode *next) {
    this->next = next;
}

bool DLLNode::operator==(const DLLNode &rhs) const {
    return element == rhs.element &&
           prev == rhs.prev &&
           next == rhs.next;
}

bool DLLNode::operator!=(const DLLNode &rhs) const {
    return !(rhs == *this);
}
