//
// Created by razvan on 23.05.2019.
//

#include <stdexcept>
#include "SortedBagIterator.h"

SortedBagIterator::SortedBagIterator(const SortedBag &sb): sb{sb}, stack{std::stack<int>{}} {
    first();
}

void SortedBagIterator::first() {
    // mergem cat se poate de tare in stanga si bagam intr-o stiva nodurile
    currentNode = sb.root;
    while (currentNode != -1) {
        stack.push(currentNode);
        currentNode = sb.tree[currentNode].getLeftSon();
    }

    if (stack.empty() == false) {
        currentNode = stack.top();
    }
    else {
        currentNode = -1;
    }
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw std::runtime_error{""};
    }

    int node = stack.top(); // luam varful stivei
    stack.pop();

    // daca are un fiu drept, mergem pe fiul drept si apoi doar in stanga pana cand dam de un nod nul
    // pe masura ce parcurgem catre stanga, le adaugam in stiva
    if (sb.tree[node].getRightSon() != -1) {
        node = sb.tree[node].getRightSon();
        while (node != -1) {
            stack.push(node);
            node = sb.tree[node].getLeftSon();
        }
    }

    if (stack.empty() == false) {
        // daca stiva nu e vida, atunci pozitia in vector a nodului curent este varful stivei
        currentNode = stack.top();
    }
    else {
        // altfel, pozitia este -1 ceea ce semnaleaza un nod nul
        currentNode = -1;
    }
}

bool SortedBagIterator::valid() const {
    return currentNode != -1;
}

TComp SortedBagIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error{""};
    }
    return sb.tree[currentNode].getValue();
}