#ifndef OOP3_CONTROLLER_H
#define OOP3_CONTROLLER_H

#include "../repository/repository.h"

typedef struct {
    Repository* repository;
}Controller;

Controller* createController(Repository* repository);
void destroyController(Controller* controller);
void addProduct(Controller* controller, char* name, char* category, int quantity, int expirationYear, int expirationMonth, int expirationDay, int mustBeUndone);
int updateProduct(Controller* controller, char* name, char* category, int quantity, int expirationYear, int expirationMonth, int expirationDay, int mustBeUndone);
int deleteProduct(Controller* controller, char* name, char* category, int mustBeUndone);
DynamicArray* getProductList(Controller* controller);
int getProductListLength(Controller* controller);
DynamicArray* filterProductList(Controller* controller, char* givenString, int (*acceptanceFunction)(Product* product, char* searchString), int (*orderingFunction)(Product* product1, Product* product2), int *length);
void sortProductList(DynamicArray* productList, int length, int (*orderingFunction)(Product* product1, Product* product2));
int undoChanges(Controller* controller);
int redoChanges(Controller* controller);

#endif //OOP3_CONTROLLER_H