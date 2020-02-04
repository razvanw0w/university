//
// Created by razvan on 01.04.2019.
//

#include "Bag.h"

Bag::Bag(): head{-1}, tail{-1}, elements{new DLLANode[1]}, elementsArraySize{0}, elementsArrayCapacity{1}, firstFreePosition{0} {

}

Bag::~Bag() {
    delete[] elements;
}

bool Bag::needsReadjustment() const {
    return firstFreePosition == -1;
}

void Bag::readjustArray() {
    DLLANode *newElements = new DLLANode[2 * elementsArrayCapacity];
    for (int i = 0; i < elementsArrayCapacity; ++i) {
        newElements[i] = elements[i];
    }
    for (int i = elementsArrayCapacity; i < elementsArrayCapacity * 2 - 1; ++i) {
        if (i > elementsArrayCapacity) {
            newElements[i].setPrev(i - 1);
        }
        newElements[i].setNext(i + 1);
    }
    newElements[elementsArrayCapacity * 2 - 1].setNext(-1);
    delete[] elements;
    elements = newElements;
    firstFreePosition = elementsArrayCapacity;
    elementsArrayCapacity *= 2;
}

void Bag::add(TElem e) {
    if (needsReadjustment()) {
        readjustArray();
    }
    bool foundElement = false;
    int currentNode = head;
    while (currentNode != -1 && elements[currentNode].getElement() != e) {
        currentNode = elements[currentNode].getNext();
    }
    if (currentNode == -1) {
        ++elementsArraySize;
        if (head == -1) {
            int nextFreePosition = elements[firstFreePosition].getNext();
            head = firstFreePosition;
            tail = firstFreePosition;
            elements[head].setElement(e);
            elements[head].setFrequency(1);
            elements[head].setNext(-1);
            elements[head].setPrev(-1);
            firstFreePosition = nextFreePosition;
        }
        else {
            int nextFreePosition = elements[firstFreePosition].getNext();
            elements[firstFreePosition].setElement(e);
            elements[firstFreePosition].setFrequency(1);
            elements[firstFreePosition].setNext(-1);
            elements[firstFreePosition].setPrev(tail);
            elements[tail].setNext(firstFreePosition);
            tail = firstFreePosition;
            firstFreePosition = nextFreePosition;
        }
    }
    else {
        int frequency = elements[currentNode].getFrequency();
        elements[currentNode].setFrequency(frequency + 1);
    }
}

bool Bag::remove(TElem e) {
    int currentNode = head;

    while (currentNode != -1 && elements[currentNode].getElement() != e) {
        currentNode = elements[currentNode].getNext();
    }
    if (currentNode == -1)
        return false;

    int frequency = elements[currentNode].getFrequency();
    if (frequency > 1) {
        elements[currentNode].setFrequency(frequency - 1);
    }
    else {
        --elementsArraySize;
        int prevNode = elements[currentNode].getPrev();
        int nextNode = elements[currentNode].getNext();
        if (currentNode == tail) {
            tail = prevNode;
            if (tail == -1) {
                head = -1;
            }
        }
        else if (currentNode == head) {
            head = nextNode;
            if (head == -1) {
                tail = -1;
            }
        }
        elements[currentNode].setNext(firstFreePosition);
        firstFreePosition = currentNode;
        if (prevNode != -1) {
            elements[prevNode].setNext(nextNode);
        }
        if (nextNode != -1) {
            elements[nextNode].setPrev(prevNode);
        }
    }
    return true;
}

bool Bag::search(TElem e) const {
    int currentNode = head;
    while (currentNode != -1 && elements[currentNode].getElement() != e) {
        currentNode = elements[currentNode].getNext();
    }
    return currentNode != -1;
}

int Bag::nrOccurrences(TElem e) const {
    int currentNode = head;
    while (currentNode != -1) {
        if (elements[currentNode].getElement() == e) {
            return elements[currentNode].getFrequency();
        }
        currentNode = elements[currentNode].getNext();
    }
    return 0;
}

int Bag::size() const {
    int sz = 0;
    int currentNode = head;
    while (currentNode != -1) {
        sz += elements[currentNode].getFrequency();
        currentNode = elements[currentNode].getNext();
    }
    return sz;
}

BagIterator Bag::iterator() const {
    BagIterator it{*this};
    return it;
}

bool Bag::isEmpty() const {
    return elementsArraySize == 0;
}
