#include <cassert>
#include "Matrix.h"

void Matrix::readjustDynamicArray() {
    elementsValuesCapacity *= 2;
    elementsColumnsCapacity *= 2;

    TElem *newElementsValues = new TElem[elementsValuesCapacity];
    TElem *newColumnsValues = new TElem[elementsColumnsCapacity];

    for (int i = 0; i < elementsValuesSize; ++i) {
        newElementsValues[i] = elementsValues[i];
        newColumnsValues[i] = elementsColumns[i];
    }
    delete[] elementsValues;
    delete[] elementsColumns;
    elementsValues = newElementsValues;
    elementsColumns = newColumnsValues;
}

bool Matrix::needsReadjustment() const {
    return elementsValuesCapacity == elementsValuesSize;
}

Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0)
        throw std::runtime_error("invalid matrix");
    numberOfLines = nrLines;
    numberOfColumns = nrCols;
    elementsValues = new TElem[1];
    elementsValuesCapacity = 1;
    elementsValuesSize = 0;
    nonZeroElementsPartialSum = new int[numberOfLines + 1];
    elementsColumns = new int[1];
    elementsColumnsCapacity = 1;
    elementsColumnsSize = 0;
}

Matrix::~Matrix() {
    delete[] elementsValues;
    delete[] elementsColumns;
    delete[] nonZeroElementsPartialSum;
}

int Matrix::nrLines() const {
    return numberOfLines;
}

int Matrix::nrColumns() const {
    return numberOfColumns;
}

TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= numberOfLines || j < 0 || j >= numberOfColumns)
        throw std::runtime_error("invalid query");
    int lo = nonZeroElementsPartialSum[i];
    int hi = nonZeroElementsPartialSum[i + 1] - 1;
    int mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (elementsColumns[mid] == j)
            return elementsValues[mid];
        if (elementsColumns[mid] < j)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= numberOfLines || j < 0 || j >= numberOfColumns)
        throw std::runtime_error("invalid query");
    bool foundElement = false;
    int lo, hi, mid, bestPosition = -1;
    TElem oldValue = 0;
    lo = nonZeroElementsPartialSum[i];
    hi = nonZeroElementsPartialSum[i + 1] - 1;
    while (lo <= hi && foundElement == false) {
        mid = (lo + hi) / 2;
        if (elementsColumns[mid] == j) {
            foundElement = true;
            oldValue = elementsValues[mid];
            elementsValues[mid] = e;
        }
        else if (elementsColumns[mid] < j) {
            bestPosition = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    if (foundElement == false) {
        if (needsReadjustment())
            readjustDynamicArray();
        if (bestPosition == -1) {
            bestPosition = nonZeroElementsPartialSum[i] - 1;
        }
        ++elementsValuesSize;
        ++elementsColumnsSize;
        for (int k = elementsValuesSize - 1; k > bestPosition + 1; --k) {
            elementsValues[k] = elementsValues[k - 1];
            elementsColumns[k] = elementsColumns[k - 1];
        }
        elementsValues[bestPosition + 1] = e;
        elementsColumns[bestPosition + 1] = j;

        for (int k = i + 1; k <= numberOfLines; ++k)
            ++nonZeroElementsPartialSum[k];
    }
    return oldValue;
}

MatrixIterator Matrix::iterator() const {
    return MatrixIterator{*this};
}
