#pragma once
#include <stdexcept>
#include "MatrixIterator.h"

typedef int TElem;

#define NULL_TELEM 0

class MatrixIterator;

class Matrix {
    friend class MatrixIterator;
private:
    /*representation of the matrix*/
    int numberOfLines, numberOfColumns;

    TElem *elementsValues;
    int elementsValuesCapacity;
    int elementsValuesSize;

    int *nonZeroElementsPartialSum;

    int *elementsColumns;
    int elementsColumnsCapacity;
    int elementsColumnsSize;

    void readjustDynamicArray();
    inline bool needsReadjustment() const;
    /*representation of the matrix*/

public:
    //constructor
    //throws exception if nrLines or nrCols is negative or zero
    Matrix(int nrLines, int nrCols);

    //destructor
    ~Matrix();

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    MatrixIterator iterator() const;
};
