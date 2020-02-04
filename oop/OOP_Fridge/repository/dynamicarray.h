#ifndef OOP3_DYNAMICARRAY_H
#define OOP3_DYNAMICARRAY_H

#include <stdlib.h>

typedef void* GenericType;

typedef struct {
    int size;
    int capacity;
    GenericType* elements;
}DynamicArray;

DynamicArray* createDynamicArray(int capacity);
void destroyDynamicArray(DynamicArray** dynamicArrayPointer);
void resizeElementList(DynamicArray* dynamicArray);
int needsResize(DynamicArray* dynamicArray);
void append(DynamicArray* dynamicArray, GenericType element);
int deleteByIndex(DynamicArray* dynamicArray, int index);
int updateByIndex(DynamicArray* dynamicArray, int index, GenericType element);
GenericType getElementByIndex(DynamicArray* dynamicArray, int index);
DynamicArray* getCopy(DynamicArray* dynamicArray);
int size(DynamicArray* dynamicArray);
void swapElements(DynamicArray* dynamicArray, int index1, int index2);

#endif //OOP3_DYNAMICARRAY_H
