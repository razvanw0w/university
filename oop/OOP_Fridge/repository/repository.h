#ifndef OOP3_REPOSITORY_H
#define OOP3_REPOSITORY_H

#include "../domain/product.h"
#include "dynamicarray.h"

typedef struct {
    DynamicArray *productArray;
    DynamicArray *historyArray;
    DynamicArray *commandArray;
    int currentHistoryIndex;
    int undoMode;
}Repository;

Repository* createProductRepository(int capacity, int undoMode);
void initProductRepository(Repository* repository);
void destroyProductList(DynamicArray* dynamicArray);
void destroyHistoryList(DynamicArray* dynamicArray);
void destroyCommandList(DynamicArray* dynamicArray);
void destroyRepository(Repository* repository);
void addElement(Repository* repository, Product* product, int mustBeUndone);
int updateElement(Repository* repository, Product* product, int mustBeUndone);
int deleteElement(Repository* repository, Product* product, int mustBeUndone);
int findProductInList(Repository* repository, Product* product);
DynamicArray* getProductListCopy(DynamicArray* dynamicArray);
DynamicArray* getElementList(Repository* repository);
DynamicArray* getElementListByCriteria(Repository* repository, char* givenString, int (*acceptanceFunction)(Product* product, char* givenString), int *length);
int getElementListLength(Repository* repository);
int undo(Repository* repository);
int redo(Repository* repository);

#endif //OOP3_REPOSITORY_H