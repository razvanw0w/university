//
// Created by razvan on 01.04.2019.
//

#ifndef SDA1_MATRIXITERATOR_H
#define SDA1_MATRIXITERATOR_H

#include "Matrix.h"

typedef int TElem;

class Matrix;

class MatrixIterator {
    friend class Matrix;
private:
    const Matrix& matrix;
    int currentPosition;
    MatrixIterator(const Matrix& matrix);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent();
};


#endif //SDA1_MATRIXITERATOR_H
