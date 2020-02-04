#include "controller.h"

/**
 * This function creates a controller based on the desired capacity
 * @param repository: Repository* - the injected repository
 * @return controller: Controller* - the newly created controller
 */
Controller* createController(Repository* repository) {
    Controller* controller = (Controller*)malloc(sizeof(Controller));
    controller->repository = repository;
    return controller;
}

/**
 * This function destroys a controller
 * @param controller: Controller* - the controller to be destroyed
 */
void destroyController(Controller* controller) {
    destroyRepository(controller->repository);
    free(controller);
}

/**
 * This function adds a product to the record
 * @param controller: Controller* - the active controller
 * @param name: char* - the name of the product
 * @param category: char* - the category of the product (must be dairy, sweets, meat or fruit)
 * @param quantity: int - the quantity of the product
 * @param expirationYear: int - the expiration year of the product
 * @param expirationMonth: int - the expiration month of the product
 * @param expirationDay: int - the expiration day of the product
 * @param mustBeUndone: int - 1 if the operation must be undone
 *                            0 otherwise
 */
void addProduct(Controller* controller, char* name, char* category, int quantity, int expirationYear, int expirationMonth, int expirationDay, int mustBeUndone) {
    Date expirationDate = createDate(expirationYear, expirationMonth, expirationDay);
    Product* product = createProduct(name, category, quantity, expirationDate);
    addElement(controller->repository, product, mustBeUndone);
}

/**
 * This function updates a product with another one specified by the following parameters
 * @param controller: Controller* - the active controller
 * @param name: char* - the name of the product
 * @param category: char* - the category of the product (must be dairy, sweets, meat or fruit)
 * @param quantity: int - the quantity of the product
 * @param expirationYear: int - the expiration year of the product
 * @param expirationMonth: int - the expiration month of the product
 * @param expirationDay: int - the expiration day of the product
 * @return: 1 if the update has completed successfully
 *          0 otherwise
 */
int updateProduct(Controller* controller, char* name, char* category, int quantity, int expirationYear, int expirationMonth, int expirationDay, int mustBeUndone) {
    Date expirationDate = createDate(expirationYear, expirationMonth, expirationDay);
    Product* product = createProduct(name, category, quantity, expirationDate);
    return updateElement(controller->repository, product, mustBeUndone);
}

/**
 * This function deletes a product with another one specified by the following parameters
 * @param controller: Controller* - the active controller
 * @param name: char* - the name of the product
 * @param category: char* - the category of the product (must be dairy, sweets, meat or fruit)
 * @param quantity: int - the quantity of the product
 * @param expirationYear: int - the expiration year of the product
 * @param expirationMonth: int - the expiration month of the product
 * @param expirationDay: int - the expiration day of the product
 * @return: 1 if the delete has completed successfully
 *          0 otherwise
 */
int deleteProduct(Controller* controller, char* name, char* category, int mustBeUndone) {
    Date expirationDate = createDate(0, 0, 0);
    Product* product = createProduct(name, category, 0, expirationDate);
    return deleteElement(controller->repository, product, mustBeUndone);
}

/**
 * This function returns a copy of the list of records
 * @param controller: Controller* - the active controller
 * @return productList: Product** - the list of the products
 */
DynamicArray* getProductList(Controller* controller) {
    return getElementList(controller->repository);
}

/**
 * This function returns the product list length
 * @param controller: Controller* - the active controller
 * @return productListLength: int - the length of the product list
 */
int getProductListLength(Controller* controller) {
    return getElementListLength(controller->repository);
}

/**
 * This function returns a filtered list based on some acceptance function
 * @param controller: Controller* - the active controller
 * @param givenString: char* - the string which needs to be searched
 * @param acceptanceFunction: function pointer - the function which decides if one element must be kept or not
 * @param length: int* - the length of the new filtered list
 * @return: filteredProductList: Product** - the filtered product list
 */
DynamicArray* filterProductList(Controller* controller, char* givenString, int (*acceptanceFunction)(Product* product, char* searchString), int (*orderingFunction)(Product* product1, Product* product2), int* length) {
    DynamicArray* filteredProductList = getElementListByCriteria(controller->repository, givenString, acceptanceFunction, length);
    sortProductList(filteredProductList, *length, orderingFunction);
    return filteredProductList;
}

/**
 * This function sorts a product list by some ordering relation provided
 * @param productList: Product** - the list of the products
 * @param length: int - the length of the list
 * @param orderingFunction: function pointer - states the ordering of the elements
 */
void sortProductList(DynamicArray* productList, int length, int (*orderingFunction)(Product* product1, Product* product2)) {
    int i, j;
    Product* aux;
    Product *firstProduct, *secondProduct;
    for (i = 0; i < length - 1; ++i) {
        for (j = i + 1; j < length; ++j) {
            firstProduct = getElementByIndex(productList, i);
            secondProduct = getElementByIndex(productList, j);
            if (!orderingFunction(firstProduct, secondProduct)) {
                swapElements(productList, i, j);
            }
        }
    }
}

/**
 * This function undoes the current state to a previous state
 * @param controller: Controller* - the current controller
 * @return: 1 if the undo has completed successfully
 *          0 otherwise
 */
int undoChanges(Controller* controller) {
    return undo(controller->repository);
}

/**
 * This function redoes the current state to a next state
 * @param controller: Controller* - the current controller
 * @return: 1 if the redo has completed successfully
 *          0 otherwise
 */
int redoChanges(Controller* controller) {
    return redo(controller->repository);
}