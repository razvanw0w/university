//
// Created by razvan on 01.04.2019.
//

#include "DLLANode.h"



TElem DLLANode::getElement() const {
    return element;
}

void DLLANode::setElement(TElem element) {
    DLLANode::element = element;
}

int DLLANode::getPrev() const {
    return prev;
}

void DLLANode::setPrev(int prev) {
    DLLANode::prev = prev;
}

int DLLANode::getNext() const {
    return next;
}

void DLLANode::setNext(int next) {
    DLLANode::next = next;
}

DLLANode::DLLANode(TElem element, int frequency, int prev, int next) : element(element), frequency(frequency),
                                                                       prev(prev), next(next) {}

int DLLANode::getFrequency() const {
    return frequency;
}

void DLLANode::setFrequency(int frequency) {
    DLLANode::frequency = frequency;
}
