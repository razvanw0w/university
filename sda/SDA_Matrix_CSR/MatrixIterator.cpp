//
// Created by razvan on 01.04.2019.
//

#include "MatrixIterator.h"

MatrixIterator::MatrixIterator(const Matrix &matrix): matrix{matrix}, currentPosition{0} {

}

void MatrixIterator::first() {
    currentPosition = 0;
}

/**
 * subalgorithm next(matrixIterator):
 *      pre: matrixIterator is a MatrixIterator
 *      post: matrixIterator.currentPosition' = matrixIterator.currentPosition + 1
 *      throws an exception if the iterator is not valid
 *
 *      if (!valid(matrixIterator)) then
 *          throw exception
 *      end-if
 *      matrixIterator.currentPosition <-- matrixIterator.currentPosition + 1
 * end subalgorithm
 *
 * time complexity: Theta(1)
 */
void MatrixIterator::next() {
    if (!valid())
        throw std::runtime_error("error");
    ++currentPosition;
}

bool MatrixIterator::valid() const {
    return 0 <= currentPosition && currentPosition < matrix.elementsValuesSize;
}

TElem MatrixIterator::getCurrent() {
    if (!valid())
        throw std::runtime_error("error");
    if (matrix.elementsValues[currentPosition] != NULL_TELEM)
        return matrix.elementsValues[currentPosition];
    else {
        next();
        return getCurrent();
    }
}