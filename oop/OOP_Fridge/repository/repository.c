#include "repository.h"
#include "../domain/command.h"

/**
 * This function returns a pointer to a repository which is going to be created
 * by its capacity
 * @param capacity: int - the capacity of the list
 * @param undoMode: int - 1 or 2 = 1 for history list, 2 for operation list
 * @return: repository: Repository* - the newly created repository
 */
Repository* createProductRepository(int capacity, int undoMode) {
    Repository* repository = (Repository*)malloc(sizeof(Repository));
    repository->productArray = createDynamicArray(capacity);
    if (undoMode == 1)
        repository->historyArray = createDynamicArray(1);
    else
        repository->commandArray = createDynamicArray(1);
    repository->currentHistoryIndex = -1;
    repository->undoMode = undoMode;
    return repository;
}

/**
 * This function destroys the repository product list
 * @param repository: Repository* - the current repository
 */
void destroyProductList(DynamicArray *dynamicArray) {
    int i;
    for (i = 0; i < size(dynamicArray); ++i) {
        destroyProduct(dynamicArray->elements[i]);
    }
}

/**
 * This function destroys the repository history list
 * @param repository: Repository* - the current repository
 */
void destroyHistoryList(DynamicArray *dynamicArray) {
    int i, j;
    DynamicArray *list;
    for (i = 0; i < size(dynamicArray); ++i) {
        list = (DynamicArray*)getElementByIndex(dynamicArray, i);
        destroyProductList(list);
        destroyDynamicArray(&list);
    }
}

void destroyCommandList(DynamicArray *dynamicArray) {
    int i;
    for (i = 0; i < size(dynamicArray); ++i) {
        destroyCommand(dynamicArray->elements[i]);
    }
}

/**
 * This function destroys a given repository along with its content
 * @param repository: Repository* - a pointer to the repository
 */
void destroyRepository(Repository* repository) {
    destroyProductList(repository->productArray);
    destroyDynamicArray(&(repository->productArray));
    if (repository->undoMode == 1) {
        destroyHistoryList(repository->historyArray);
        destroyDynamicArray(&(repository->historyArray));
    }
    else {
        destroyCommandList(repository->commandArray);
        destroyDynamicArray(&(repository->commandArray));
    }
    free(repository);
}

/**
 * This function cleans the rest of the history when a new operation is done and there are 1 or more states after
 * the principially new state which must be created
 * @param repository: Repository* - the active repository
 */
void cleanFurtherHistory(Repository *repository) {
    if (repository->undoMode == 1) {
        if (repository->currentHistoryIndex < size(repository->historyArray) - 1) {
            DynamicArray *list;
            while (repository->currentHistoryIndex < size(repository->historyArray) - 1) {
                list = (DynamicArray*)getElementByIndex(repository->historyArray, size(repository->historyArray) - 1);
                destroyProductList(list);
                destroyDynamicArray(&list);
                deleteByIndex(repository->historyArray, size(repository->historyArray) - 1);
            }
        }
    }
    else {
        if (repository->currentHistoryIndex < size(repository->commandArray) - 1) {
            Command *command;
            while (repository->currentHistoryIndex < size(repository->commandArray) - 1) {
                command = (Command*)getElementByIndex(repository->commandArray, size(repository->commandArray) - 1);
                destroyCommand(command);
                deleteByIndex(repository->commandArray, size(repository->commandArray) - 1);
            }
        }
    }
}

/**
 * This function appends the current list into the list history
 * @param repository: Repository* - the current repository
 */
void appendCurrentStateInHistory(Repository *repository) {
    append(repository->historyArray, getElementList(repository));
    ++repository->currentHistoryIndex;
}

void appendCurrentCommandInHistory(Repository *repository, Command* command) {
    append(repository->commandArray, command);
    ++repository->currentHistoryIndex;
}

/**
 * This function adds a product into the product list
 * if the product is already in the product list, its quantity
 * will be updated
 * @param repository: Repository* - the active repository
 * @param product: Product* - the product to be added
 */
void addElement(Repository* repository, Product* product, int mustBeUndone) {
    int productPosition = findProductInList(repository, product);
    if (mustBeUndone)
        cleanFurtherHistory(repository);
    if (productPosition == -1) {
        append(repository->productArray, product);
        if (mustBeUndone) {
            if (repository->undoMode == 1) {
                appendCurrentStateInHistory(repository);
            }
            else {
                Product* undoProduct = getProductCopy(product);
                Product* redoProduct = getProductCopy(product);
                Operation* redo = createOperation('a', redoProduct);
                Operation* undo = createOperation('d', undoProduct);
                Command* command = createCommand(redo, undo);
                appendCurrentCommandInHistory(repository, command);
            }
        }
    }
    else {
        int previousQuantity, actualQuantity;
        Date previousDate;
        Product* productToBeDestroyed = getElementByIndex(repository->productArray, productPosition);
        previousQuantity = getProductQuantity(productToBeDestroyed);
        actualQuantity = getProductQuantity(product);
        previousDate = getProductExpirationDate(productToBeDestroyed);
        Product *undoProduct = NULL, *redoProduct = NULL;
        if (repository->undoMode == 2 && mustBeUndone) {
            undoProduct = getProductCopy(productToBeDestroyed);
        }
        destroyProduct(productToBeDestroyed);
        setProductQuantity(product, previousQuantity + actualQuantity);
        setProductExpirationDate(product, previousDate);
        if (repository->undoMode == 2 && mustBeUndone) {
            redoProduct = getProductCopy(product);
        }
        updateByIndex(repository->productArray, productPosition, product);
        if (mustBeUndone) {
            if (repository->undoMode == 1) {
                appendCurrentStateInHistory(repository);
            }
            else if (repository->undoMode == 2) {
                Operation* redo = createOperation('a', redoProduct);
                Operation* undo = createOperation('u', undoProduct);
                Command* command = createCommand(redo, undo);
                appendCurrentCommandInHistory(repository, command);
            }
        }
    }
}

/**
 * This function updates a product with another one
 * @param repository: Repository* - the current repository
 * @param product: Product* - the product which needs to be updated
 * @return: 1 if the update has completed successfully
 *          0 otherwise
 */
int updateElement(Repository* repository, Product* product, int mustBeUndone) {
    int elementToUpdatePosition = findProductInList(repository, product);
    if (elementToUpdatePosition == -1) {
        destroyProduct(product);
        return 0;
    }
    if (mustBeUndone)
        cleanFurtherHistory(repository);
    Product *undoProduct = NULL, *redoProduct = NULL;
    Product* productToBeDestroyed = getElementByIndex(repository->productArray, elementToUpdatePosition);
    if (repository->undoMode == 2 && mustBeUndone) {
        undoProduct = getProductCopy(productToBeDestroyed);
        redoProduct = getProductCopy(product);
    }
    destroyProduct(productToBeDestroyed);
    updateByIndex(repository->productArray, elementToUpdatePosition, product);
    if (mustBeUndone) {
        if (repository->undoMode == 1) {
            appendCurrentStateInHistory(repository);
        }
        else {
            Operation *redo = createOperation('u', redoProduct);
            Operation *undo = createOperation('u', undoProduct);
            Command *command = createCommand(redo, undo);
            appendCurrentCommandInHistory(repository, command);
        }
    }
    return 1;
}

/**
 * This function deletes a product from the product list
 * @param repository: Repository* - the current repository
 * @param product: Product* - the product which needs to be deleted
 * @return: 1 if the deletion has completed successfully
 *          0 otherwise
 */
int deleteElement(Repository* repository, Product* product, int mustBeUndone) {
    int i;
    int elementToDeletePosition = findProductInList(repository, product);
    if (elementToDeletePosition == -1) {
        destroyProduct(product);
        return 0;
    }
    if (mustBeUndone)
        cleanFurtherHistory(repository);
    Product *undoProduct = NULL, *redoProduct = NULL;
    Product* productToBeDestroyed = getElementByIndex(repository->productArray, elementToDeletePosition);
    if (repository->undoMode == 2 && mustBeUndone) {
        undoProduct = getProductCopy(productToBeDestroyed);
        redoProduct = getProductCopy(product);
    }
    destroyProduct(productToBeDestroyed);
    deleteByIndex(repository->productArray, elementToDeletePosition);
    if (mustBeUndone) {
        if (repository->undoMode == 1)
            appendCurrentStateInHistory(repository);
        else {
            Operation* undo = createOperation('a', undoProduct);
            Operation* redo = createOperation('d', redoProduct);
            Command *command = createCommand(redo, undo);
            appendCurrentCommandInHistory(repository, command);
        }
    }
    destroyProduct(product);
    return 1;
}

/**
 * This function searches for a product in the product list
 * @param repository: Repository* - the target repository
 * @param product: Product* - the product which needs to be searched
 * @return: the index of the found product if it exists in the list
 *          -1 otherwise
 */
int findProductInList(Repository* repository, Product* product) {
    int i;
    int position = -1;
    Product* candidate;
    for (i = 0; i < size(repository->productArray) && position == -1; ++i) {
        candidate = getElementByIndex(repository->productArray, i);
        if (areProductsEqual(candidate, product))
            position = i;
    }
    return position;
}

/**
 * This function returns a deep copy of a product list
 * @param productList: DynamicArray* - a list of pointers to Product (Product*)
 * @return: productListCopy: DynamicArray* - a deep copy of productList
 */
DynamicArray* getProductListCopy(DynamicArray* productList) {
    DynamicArray *dynamicArray = createDynamicArray(size(productList));
    Product* currentProduct;
    Product* newProduct;
    int i;
    for (i = 0; i < size(productList); ++i) {
        currentProduct = getElementByIndex(productList, i);
        newProduct = createProduct(getProductName(currentProduct),
                                   getProductCategory(currentProduct),
                                   getProductQuantity(currentProduct),
                                   getProductExpirationDate(currentProduct));
        append(dynamicArray, newProduct);
    }
    return dynamicArray;
}

/**
 * This function returns a copy of the element list
 * @param repository: Repository* - the active repository
 * @return productListCopy: DynamicArray* - a copy of the list
 */
DynamicArray* getElementList(Repository* repository) {
    DynamicArray *dynamicArray = getProductListCopy(repository->productArray);
    return dynamicArray;
}

/**
 * This function returns the length of the element list
 * @param repository: Repository* - the active repository
 * @return length: int - the length of the repository list
 */
int getElementListLength(Repository* repository) {
    return size(repository->productArray);
}

/**
 * This function returns an element list generated by a given criteria
 * @param repository: Repository* - the current repository
 * @param givenString: char* - the given string
 * @param acceptanceFunction: function pointer - the function which decides if the element must be kept or not
 * @param length: int* - the length of the newly created list
 * @return: filteredProductList - Product** - the list of products which satisfy the given criteria
 */
DynamicArray* getElementListByCriteria(Repository* repository, char* givenString, int (*acceptanceFunction)(Product* product, char* givenString), int *length) {
    *length = 0;
    int i = 0;
    Product* currentProduct;
    Product* newProduct;
    for (i = 0; i < size(repository->productArray); ++i) {
        currentProduct = getElementByIndex(repository->productArray, i);
        if (acceptanceFunction(currentProduct, givenString)) {
            ++(*length);
        }
    }

    DynamicArray *filteredProductList = createDynamicArray(*length);
    int currentPosition = 0;
    for (i = 0; i < size(repository->productArray); ++i) {
        currentProduct = getElementByIndex(repository->productArray, i);
        if (acceptanceFunction(currentProduct, givenString)) {
            newProduct = createProduct(getProductName(currentProduct),
                                       getProductCategory(currentProduct),
                                       getProductQuantity(currentProduct),
                                       getProductExpirationDate(currentProduct));
            append(filteredProductList, newProduct);
        }
    }
    return filteredProductList;
}

/**
 * This function reverts the changes to a previous state
 * @param repository: Repository* - the current repository
 * @return: 1 if the undo has completed successfully
 *          0 otherwise
 */
int undo(Repository* repository) {
    if (repository->undoMode == 1) {
        if (repository->currentHistoryIndex == 0)
            return 0;
        destroyProductList(repository->productArray);
        destroyDynamicArray(&repository->productArray);
        repository->productArray = getProductListCopy((DynamicArray*)getElementByIndex(repository->historyArray, repository->currentHistoryIndex - 1));
    }
    else {
        if (repository->currentHistoryIndex == -1)
            return 0;
        Command *command = getElementByIndex(repository->commandArray, repository->currentHistoryIndex);
        Operation *undo = getUndoOperation(command);
        char action = getOperationAction(undo);
        Product* product = getProductCopy(getOperationProduct(undo));
        if (action == 'a')
            addElement(repository, product, 0);
        else if (action == 'u')
            updateElement(repository, product, 0);
        else
            deleteElement(repository, product, 0);
    }
    --repository->currentHistoryIndex;
    return 1;
}

/**
 * This function reverts the changes to a next state
 * @param repository: Repository* - the current repository
 * @return: 1 if the redo has completed successfully
 *          0 otherwise
 */
int redo(Repository* repository) {
    if (repository->undoMode == 1) {
        if (repository->currentHistoryIndex == size(repository->historyArray) - 1)
            return 0;
        destroyProductList(repository->productArray);
        destroyDynamicArray(&repository->productArray);
        repository->productArray = getProductListCopy(
                (DynamicArray *) getElementByIndex(repository->historyArray, repository->currentHistoryIndex + 1));
    }
    else {
        if (repository->currentHistoryIndex >= size(repository->commandArray) - 1)
            return 0;
        Command *command = getElementByIndex(repository->commandArray, repository->currentHistoryIndex + 1);
        Operation *redo = getRedoOperation(command);
        char action = getOperationAction(redo);
        Product* product = getProductCopy(getOperationProduct(redo));
        if (action == 'a')
            addElement(repository, product, 0);
        else if (action == 'u')
            updateElement(repository, product, 0);
        else
            deleteElement(repository, product, 0);
    }
    ++repository->currentHistoryIndex;
    return 1;
}

/**
 * This function initialises the product repository
 * @param repository: Repository* - the current repository
 */
void initProductRepository(Repository* repository) {
    if (repository->undoMode == 1)
        appendCurrentStateInHistory(repository);
}
