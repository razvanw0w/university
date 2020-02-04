//
// Created by razvan on 23.05.2019.
//

#include "BSTNode.h"

TComp BSTNode::getValue() const {
    return value;
}

void BSTNode::setValue(TComp value) {
    this->value = value;
}

int BSTNode::getLeftSon() const {
    return leftSon;
}

void BSTNode::setLeftSon(int leftSon) {
    this->leftSon = leftSon;
}

int BSTNode::getRightSon() const {
    return rightSon;
}

void BSTNode::setRightSon(int rightSon) {
    this->rightSon = rightSon;
}

BSTNode::BSTNode(TComp value, int leftSon, int rightSon) : value(NULL_TCOMP), leftSon(leftSon), rightSon(rightSon) {}

bool BSTNode::isNull() {
    return value == NULL_TCOMP;
}

bool BSTNode::isLeaf() {
    return leftSon == -1 && rightSon == -1;
}
