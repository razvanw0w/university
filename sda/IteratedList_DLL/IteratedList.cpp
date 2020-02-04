//
// Created by razvan on 30.03.2019.
//

#include <stdexcept>
#include "IteratedList.h"

IteratedList::IteratedList(): head{nullptr}, tail{nullptr}, listSize{0} {

}

int IteratedList::size() const {
    return listSize;
}

bool IteratedList::isEmpty() const {
    return listSize == 0;
}

ListIterator IteratedList::first() const {
    ListIterator it{*this};
    return it;
}

TElem IteratedList::getElement(ListIterator pos) const {
    if (!pos.valid())
        throw std::runtime_error("error");
    return pos.getCurrent();
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw std::runtime_error("error");
    TElem oldElement = pos.currentNode->getElement();
    pos.currentNode->setElement(e);
    return oldElement;
}

void IteratedList::addToEnd(TElem e) {
    DLLNode *node = new DLLNode(e);
    if (listSize == 0) {
        head = tail = node;
    }
    else {
        node->setPrev(tail);
        node->setNext(nullptr);
        tail->setNext(node);
        tail = node;
    }
    ++listSize;
}

void IteratedList::addToPosition(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw std::runtime_error("error");
    DLLNode *node = new DLLNode{e};
    if (pos.currentNode == head) {
        node->setNext(head);
        node->setPrev(nullptr);
        head->setPrev(node);
        head = node;
    }
    else if (pos.currentNode == tail) {
        node->setPrev(tail);
        node->setNext(nullptr);
        tail->setNext(node);
        tail = node;
    }
    else {
        TElem oldValue = pos.currentNode->getElement();
        node->setPrev(pos.currentNode);
        node->setNext(pos.currentNode->getNext());
        node->setElement(oldValue);
        pos.currentNode->getNext()->setPrev(node);
        pos.currentNode->setNext(node);
        pos.currentNode->setElement(e);
    }
    ++listSize;
}

TElem IteratedList::remove(ListIterator pos) {
    if (!pos.valid())
        throw std::runtime_error("error");
    TElem oldValue = pos.getCurrent();
    if (pos.currentNode == head) {
        DLLNode *secondElement = head->getNext();
        head->setNext(nullptr);
        head->setPrev(nullptr);
        delete head;
        head = secondElement;
        if (head != nullptr)
            head->setPrev(nullptr);
    }
    else if (pos.currentNode == tail) {
        DLLNode *beforeLastElement = tail->getPrev();
        tail->setNext(nullptr);
        tail->setPrev(nullptr);
        delete tail;
        tail = beforeLastElement;
        if (tail != nullptr)
            tail->setNext(nullptr);
    }
    else {
        DLLNode *next = pos.currentNode->getNext();
        pos.currentNode->setElement(next->getElement());
        pos.currentNode->setNext(next->getNext());
        delete next;
        next = nullptr;
    }
    --listSize;
    return oldValue;
}

ListIterator IteratedList::search(TElem e) const {
    auto it = first();
    while (it.valid()) {
        if (it.getCurrent() == e)
            return it;
        it.next();
    }
    return it;
}

IteratedList::~IteratedList() {
    DLLNode *currentNode;
    while (head != nullptr) {
        currentNode = head;
        head = head->getNext();
        delete currentNode;
    }
}
