//
// Created by razvan on 27.05.2019.
//

#include <stdexcept>
#include "SortedSetIterator.h"

SortedSetIterator::SortedSetIterator(const SortedSet &set): set{set}, currentNode{nullptr}, stack{std::stack<BSTNode*>{}} {
    first();
}

void SortedSetIterator::first() {
    currentNode = set.root;
    stack = std::stack<BSTNode*>{};
    while (currentNode != nullptr) {
        stack.push(currentNode);
        currentNode = currentNode->getLeftSon();
    }

    if (stack.empty() == false) {
        currentNode = stack.top();
    }
    else {
        currentNode = nullptr;
    }
}

void SortedSetIterator::next() {
    if (!valid())
        throw std::runtime_error("");

    BSTNode* node = stack.top();
    stack.pop();

    if (node->getRightSon() != nullptr) {
        node = node->getRightSon();
        while (node != nullptr) {
            stack.push(node);
            node = node->getLeftSon();
        }
    }

    if (stack.empty() == false) {
        currentNode = stack.top();
    }
    else {
        currentNode = nullptr;
    }
}

bool SortedSetIterator::valid() const {
    return currentNode != nullptr;
}

TComp SortedSetIterator::getCurrent() const {
    if (!valid())
        throw std::runtime_error("");
    return currentNode->getValue();
}
