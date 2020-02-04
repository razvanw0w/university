#include "operation.h"

/**
 * This function creates an operation
 * @param action: char - the character of the operation (must be a/d/u)
 * @param product: Product* - the product which is going to be stored
 * @return: Operation* - the newly created operation
 */
Operation* createOperation(char action, Product* product) {
    Operation *operation = (Operation*)malloc(sizeof(Operation));
    operation->action = action;
    operation->product = product;
    return operation;
}

/**
 * This function destroys an existing operation
 * @param operation: Operation* - the operation which needs to be destroyed
 */
void destroyOperation(Operation* operation) {
    destroyProduct(operation->product);
    free(operation);
}

/**
 * This function returns the action of the operation
 * @param operation: Operation* - the given operation
 * @return: char - the action of the operation
 */
char getOperationAction(Operation* operation) {
    return operation->action;
}

/**
 * This function returns the product of the operation
 * @param operation: Operation* - the given operation
 * @return: Product* - the product of the operation
 */
Product* getOperationProduct(Operation* operation) {
    return operation->product;
}