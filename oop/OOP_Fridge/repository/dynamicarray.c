#include "dynamicarray.h"

/**
 * This function creates a dynamic array with a desired capacity
 * @param capacity: int - the desired capacity
 * @return: DynamicArray* - the newly created dynamic array
 */
DynamicArray* createDynamicArray(int capacity) {
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamicArray->size = 0;
    dynamicArray->capacity = capacity;
    dynamicArray->elements = (GenericType*)malloc(sizeof(GenericType) * capacity);
}

/**
 * This function destroys an existing dynamic array
 * @param dynamicArrayPointer: DynamicArray** - a pointer to our dynamic array
 */
void destroyDynamicArray(DynamicArray** dynamicArrayPointer) {
    free((*dynamicArrayPointer)->elements);
    free(*dynamicArrayPointer);
}

/**
 * This function tells if the dynamic array needs a resize
 * @param dynamicArray: DynamicArray* - a pointer to the desired dynamic array
 * @return: 1 if the dynamic array needs a resize
 *          0 otherwise
 */
int needsResize(DynamicArray* dynamicArray) {
    return dynamicArray->size == dynamicArray->capacity;
}

/**
 * This function resizes the element list (doubles the capacity)
 * @param dynamicArray: DynamicArray* - a pointer to the active dynamic array
 */
void resizeElementList(DynamicArray* dynamicArray) {
    dynamicArray->capacity *= 2;

    GenericType *newElements = (GenericType*)malloc(sizeof(GenericType) * dynamicArray->capacity);
    int i;
    for (i = 0; i < dynamicArray->size; ++i) {
        newElements[i] = dynamicArray->elements[i];
    }
    free(dynamicArray->elements);
    dynamicArray->elements = newElements;
}

/**
 * This function returns the size of the dynamic array
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @return: int - the size of the dynamic array
 */
int size(DynamicArray* dynamicArray) {
    return dynamicArray->size;
}

/**
 * This function adds an element to the dynamic array
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @param element: GenericType - the element to be added
 */
void append(DynamicArray* dynamicArray, GenericType element) {
    if (needsResize(dynamicArray)) {
        resizeElementList(dynamicArray);
    }
    ++dynamicArray->size;
    dynamicArray->elements[dynamicArray->size - 1] = element;
}

/**
 * This function deletes an element from a certain index
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @param index: int - the index of the element which needs to be deleted
 * @return: 1 if the element has been deleted successfully
 *          0 otherwise
 */
int deleteByIndex(DynamicArray* dynamicArray, int index) {
    if (index < 0 || index >= dynamicArray->size) {
        return 0;
    }
    if (dynamicArray->elements > 0) {
        --dynamicArray->size;
        int i;
        for (i = index; i < dynamicArray->size; ++i)
            dynamicArray->elements[i] = dynamicArray->elements[i + 1];
    }
    return 1;
}

/**
 * This function updates an element from a certain index
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @param index: int - the index of the element which needs to be updated
 * @param element: GenericType - the element which the current one will be updated with
 * @return: 1 if the updated has completed successfully
 *          0 otherwise
 */
int updateByIndex(DynamicArray* dynamicArray, int index, GenericType element) {
    if (index < 0 || index >= dynamicArray->size) {
        return 0;
    }
    dynamicArray->elements[index] = element;
}

/**
 * This function gets the element at a certain index
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @param index: int - the index of element which needs to be extracted
 * @return: elements[index] if the index exists
 *          NULL otherwise
 */
GenericType getElementByIndex(DynamicArray* dynamicArray, int index) {
    if (index < 0 || index >= dynamicArray->size) {
        return NULL;
    }
    return dynamicArray->elements[index];
}

/**
 * This function returns a copy of a given dynamic array
 * @param dynamicArray: DynamicArray* - the active dynamic array
 * @return: DynamicArray* - copy of the current dynamic array
 */
DynamicArray* getCopy(DynamicArray* dynamicArray) {
    DynamicArray* copy = createDynamicArray(dynamicArray->capacity);
    copy->size = dynamicArray->size;
    return copy;
}

/**
 * This function swaps two elements on specified indices in a dynamic array
 * @param dynamicArray: DynamicArray* - the given dynamic array
 * @param index1: int - the first index
 * @param index2: int - the second index
 */
void swapElements(DynamicArray* dynamicArray, int index1, int index2) {
    GenericType aux;
    aux = dynamicArray->elements[index1];
    dynamicArray->elements[index1] = dynamicArray->elements[index2];
    dynamicArray->elements[index2] = aux;
}