#ifndef OOP3_PRODUCT_H
#define OOP3_PRODUCT_H

#include "date.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *category;
    int quantity;
    Date expirationDate;
}Product;

Product* createProduct(char *name, char *category, int quantity, Date expirationDate);
void destroyProduct(Product* product);
char* getProductName(Product* product);
char* getProductCategory(Product* product);
int getProductQuantity(Product* product);
Date getProductExpirationDate(Product* product);
void setProductName(Product* product, char *name);
void setProductCategory(Product* product, char *category);
void setProductQuantity(Product* product, int quantity);
void setProductExpirationDate(Product* product, Date expirationDate);
Product* getProductCopy(Product* product);
int areProductsEqual(Product* product1, Product* product2);
int isLess(Product* product1, Product* product2);
int doesProductNameContainString(Product* product, char* givenString);
int isNameLexicographicallyLarger(Product* product1, Product* product2);
int isCategoryNameEqualToString(Product* product, char* givenString);
int isGreater(Product* product1, Product* product2);

#endif //OOP3_PRODUCT_H