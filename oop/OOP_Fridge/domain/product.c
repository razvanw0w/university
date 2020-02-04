#include "product.h"

/**
 * This function creates a product based by its parameters
 * constructor of the class
 * @param name: char* - the name of the product
 * @param category: char* - the category of the product
 * @param quantity: int - the quantity of the product
 * @param expirationDate: Date - the date of expiration
 * @return Product* - a pointer to the newly created product
 */
Product* createProduct(char *name, char *category, int quantity, Date expirationDate) {
    Product* product = (Product*)malloc(sizeof(Product));
    product->name = NULL;
    product->category = NULL;
    setProductName(product, name);
    setProductCategory(product, category);
    setProductQuantity(product, quantity);
    setProductExpirationDate(product, expirationDate);
    return product;
}

/**
 * This function destroys the current product
 * @param product: Product* - the current product
 */
void destroyProduct(Product* product) {
    free(product->name);
    free(product->category);
    free(product);
}

/**
 * This function returns the name of the product
 * @param product: Product* - the current product
 * @return productName: char* - the name of the product
 */
char* getProductName(Product* product) {
    return product->name;
}

/**
 * This function returns the category of the product
 * @param product: Product* - the current product
 * @return productCategory: char* - the category of the product
 */
char* getProductCategory(Product* product) {
    return product->category;
}

/**
 * This function returns the quantity of the product
 * @param product: Product* - the current product
 * @return productQuantity: int - the quantity of the product
 */
int getProductQuantity(Product* product) {
    return product->quantity;
}

/**
 * This function returns the expirationDate of the product
 * @param product: Product* - the current product
 * @return productExpirationDate: Date - the expiration date of the product
 */
Date getProductExpirationDate(Product* product) {
    return product->expirationDate;
}

/**
 * This function sets a product's name
 * @param product: Product* - a pointer to the current product
 * @param name: char* - the name which needs to be set
 */
void setProductName(Product* product, char *name) {
    if (product->name != NULL) {
        free(product->name);
        product->name = NULL;
    }
    product->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(product->name, name);
}

/**
 * This function sets a product's category
 * @param product: Product* - a pointer to the current product
 * @param category: char* - the category which needs to be set
 */
void setProductCategory(Product* product, char *category) {
    if (product->category != NULL) {
        free(product->category);
        product->category = NULL;
    }
    product->category = (char*)malloc(sizeof(char) * (strlen(category) + 1));
    strcpy(product->category, category);
}

/**
 * This function sets a product's quantity
 * @param product: Product* - a pointer to the current product
 * @param quantity: int - the quantity which needs to be set
 */
void setProductQuantity(Product* product, int quantity) {
    product->quantity = quantity;
}

/**
 * This function sets a product's expiration date
 * @param product: Product* - a pointer to the current product
 * @param expirationDate: Date - the expiration date which needs to be set
 */
void setProductExpirationDate(Product* product, Date expirationDate) {
    product->expirationDate = expirationDate;
}

/**
 * This function tells whether 2 products are equal or not
 * @param product1: Product* - pointer to the first product
 * @param product2: Product* - pointer to the second product
 * @return: 1 if they are equal
 *          0 otherwise
 */
int areProductsEqual(Product* product1, Product* product2) {
    return strcmp(product1->name, product2->name) == 0 && strcmp(product1->category, product2->category) == 0;
}


/**
 * This function copies all the contents from a source product to a destination product
 * @param destination: Product* - the destination of the copy process
 * @param source: Product* - the source of the copy process
 */
/*
void copy(Product* destination, Product* source) {
    setProductName(destination, getProductName(source));
    setProductCategory(destination, getProductCategory(source));
    setProductQuantity(destination, getProductQuantity(source));
    setProductExpirationDate(destination, getProductExpirationDate(source));
}*/


/**
 * This function tells if a product is considered less that another
 * regarding the quantity
 * @param product1: Product* - the first product to be compared
 * @param product2: Product* - the second product to be compared
 * @return: 1 if the first product is less than the other
 *          0 otherwise
 */
int isLess(Product* product1, Product* product2) {
    return product1->quantity < product2->quantity;
}

/**
 * This function tells if a product's name contains a given string
 * @param product: Product* - the given product
 * @param givenString: char* - the given string
 * @return: 1 if the product's name contains the string
 *          0 otherwise
 */
int doesProductNameContainString(Product* product, char* givenString) {
    return strstr(product->name, givenString) != NULL;
}

/**
 * This function tells if a product is considered larger than another one
 * regarding the name
 * @param product1: Product* - the first product
 * @param product2: Product* - the second product
 * @return: 1 if the name of the first product is lexicographically larger than the second one
 *          0 otherwise
 */
int isNameLexicographicallyLarger(Product* product1, Product* product2) {
    return strcmp(getProductName(product1), getProductName(product2)) > 0;
}

/**
 * This function tells if this product's category is equal to some string
 * @param product: Product* - the given product
 * @param givenString: char* - the given string
 * @return 1 if the product's category is equal to the string or if the string is empty
 *         0 otherwise
 */
int isCategoryNameEqualToString(Product* product, char* givenString) {
    return strcmp(getProductCategory(product), givenString) == 0 || strcmp(givenString, "") == 0;
}

/**
 * This function tells if a product is considered greater than another
 * regarding the quantity
 * @param product1
 * @param product2
 * @return
 */
int isGreater(Product* product1, Product* product2) {
    return product1->quantity > product2->quantity;
}

Product* getProductCopy(Product* product) {
    return createProduct(getProductName(product),
                         getProductCategory(product),
                         getProductQuantity(product),
                         getProductExpirationDate(product));
}