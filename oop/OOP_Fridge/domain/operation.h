//
// Created by razvan on 25.03.2019.
//

#ifndef OOP3_OPERATION_H
#define OOP3_OPERATION_H

#include "product.h"

typedef struct {
    char action;
    Product* product;
}Operation;

Operation* createOperation(char action, Product* product);
void destroyOperation(Operation* operation);
char getOperationAction(Operation* operation);
Product* getOperationProduct(Operation* operation);

#endif //OOP3_OPERATION_H
