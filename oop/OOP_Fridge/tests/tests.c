#include <stdio.h>
#include "tests.h"
#include "../repository/dynamicarray.h"

void runTests() {
    testDate();
    testProduct();
    testValidation();
    testDynamicArray();
    testRepository();
    testController();
}

void testDate() {
    testCreateDate();
    testGetDateYear();
    testGetDateMonth();
    testGetDateDay();
    testSetDateYear();
    testSetDateMonth();
    testSetDateDay();
    testIsDateLess();
    testCountDaysUntilDate();
    testGetDayDifference();
}

void testProduct() {
    testCreateProduct();
    testDestroyProduct();
    testGetProductName();
    testGetProductCategory();
    testGetProductQuantity();
    testGetProductExpirationDate();
    testSetProductName();
    testSetProductCategory();
    testSetProductQuantity();
    testSetProductExpirationDate();
    testAreProductsEqual();
    testIsLess();
    testIsGreater();
    testDoesProductNameContainString();
    testIsNameLexicographicallyLarger();
    testIsCategoryNameEqualToString();
}

void testValidation() {
    testValidateCategory();
    testValidateExpirationDate();
    testIsYearLeap();
}

void testRepository() {
    testCreateProductRepository();
    testDestroyRepository();
    testAddElement();
    testUpdateElement();
    testDeleteElement();
    testFindProductInList();
    testGetElementList();
    testGetElementListByCriteria();
    testGetElementListLength();
}

void testController() {
    testCreateController();
    testDestroyController();
    testAddProduct();
    testUpdateProduct();
    testDeleteProduct();
    testGetProductList();
    testGetProductListLength();
    testFilterProductList();
    testSortProductList();
}

void testDynamicArray() {
    testCreateDynamicArray();
    testResizeElementList();
    testNeedsResize();
    testAppend();
    testDeleteByIndex();
    testUpdateByIndex();
    testGetElementByIndex();
    testSize();
}

void testCreateDate() {
    Date date = createDate(2020, 12, 1);
    assert(getDateYear(date) == 2020);
    assert(getDateMonth(date) == 12);
    assert(getDateDay(date) == 1);

    date = createDate(2030, 1, 10);
    assert(getDateYear(date) == 2030);
    assert(getDateMonth(date) == 1);
    assert(getDateDay(date) == 10);
}

void testGetDateYear() {
    Date date = createDate(2020, 12, 1);
    assert(getDateYear(date) == 2020);

    date = createDate(2030, 1, 10);
    assert(getDateYear(date) == 2030);

    date = createDate(1999, 9, 15);
    assert(getDateYear(date) == 1999);
}

void testGetDateMonth() {
    Date date = createDate(2020, 12, 1);
    assert(getDateMonth(date) == 12);

    date = createDate(2030, 1, 10);
    assert(getDateMonth(date) == 1);

    date = createDate(1999, 9, 15);
    assert(getDateMonth(date) == 9);
}

void testGetDateDay() {
    Date date = createDate(2020, 12, 1);
    assert(getDateDay(date) == 1);

    date = createDate(2030, 1, 10);
    assert(getDateDay(date) == 10);

    date = createDate(1999, 9, 15);
    assert(getDateDay(date) == 15);
}

void testSetDateYear() {
    Date date = createDate(2020, 12, 1);
    assert(getDateYear(date) == 2020);

    setDateYear(&date, 2019);
    assert(getDateYear(date) == 2019);
}

void testSetDateMonth() {
    Date date = createDate(2020, 12, 1);
    assert(getDateMonth(date) == 12);

    setDateMonth(&date, 5);
    assert(getDateMonth(date) == 5);
}

void testSetDateDay() {
    Date date = createDate(2020, 12, 1);
    assert(getDateDay(date) == 1);

    setDateDay(&date, 23);
    assert(getDateDay(date) == 23);
}

void testIsDateLess() {
    Date date1 = createDate(1999, 3, 31);
    Date date2 = createDate(2000, 1, 1);

    assert(isDateLess(date1, date2) == 1);
    assert(isDateLess(date2, date1) == 0);
    assert(isDateLess(date1, date1) == 0);
    assert(isDateLess(date2, date2) == 0);
}

void testGetDayDifference() {
    Date date1 = createDate(2016, 2, 27);
    Date date2 = createDate(2019, 3, 18);
    assert(getDayDifference(date1, date2) == 1115);
}

void testCountDaysUntilDate() {
    Date date = createDate(2016, 2, 27);
    assert(countDaysUntilDate(date) == 736464);
    date = createDate(2019, 3, 18);
    assert(countDaysUntilDate(date) == 737579);
}

void testCreateProduct() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(strcmp(getProductName(product), "boom") == 0);
    assert(strcmp(getProductCategory(product), "dairy") == 0);
    assert(getProductQuantity(product) == 13);
    Date date = getProductExpirationDate(product);
    assert(getDateYear(date) == 2019);
    assert(getDateMonth(date) == 10);
    assert(getDateDay(date) == 10);

    destroyProduct(product);
}

void testDestroyProduct() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    destroyProduct(product);
}

void testGetProductName() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(strcmp(getProductName(product), "boom") == 0);
    destroyProduct(product);

    product = createProduct("bang", "meat", 13, createDate(2019, 11, 11));
    assert(strcmp(getProductName(product), "bang") == 0);
    destroyProduct(product);
}

void testGetProductCategory() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(strcmp(getProductCategory(product), "dairy") == 0);
    destroyProduct(product);

    product = createProduct("bang", "meat", 13, createDate(2019, 11, 11));
    assert(strcmp(getProductCategory(product), "meat") == 0);
    destroyProduct(product);
}

void testGetProductQuantity() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(getProductQuantity(product) == 13);
    destroyProduct(product);

    product = createProduct("bang", "meat", 19, createDate(2019, 11, 11));
    assert(getProductQuantity(product) == 19);
    destroyProduct(product);
}

void testGetProductExpirationDate() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    Date date = getProductExpirationDate(product);
    assert(getDateYear(date) == 2019);
    assert(getDateMonth(date) == 10);
    assert(getDateDay(date) == 10);
    destroyProduct(product);

    product = createProduct("bang", "meat", 13, createDate(2023, 11, 11));
    date = getProductExpirationDate(product);
    assert(getDateYear(date) == 2023);
    assert(getDateMonth(date) == 11);
    assert(getDateDay(date) == 11);
    destroyProduct(product);
}

void testSetProductName() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(strcmp(getProductName(product), "boom") == 0);

    setProductName(product, "bang");
    assert(strcmp(getProductName(product), "bang") == 0);
    assert(strcmp(getProductName(product), "boom") != 0);
    destroyProduct(product);
}

void testSetProductCategory() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(strcmp(getProductCategory(product), "dairy") == 0);

    setProductCategory(product, "meat");
    assert(strcmp(getProductCategory(product), "meat") == 0);
    assert(strcmp(getProductCategory(product), "dairy") != 0);
    destroyProduct(product);
}

void testSetProductQuantity() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    assert(getProductQuantity(product) == 13);

    setProductQuantity(product, 20);
    assert(getProductQuantity(product) == 20);
    assert(getProductQuantity(product) != 13);
    destroyProduct(product);
}

void testSetProductExpirationDate() {
    Product* product = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    Date date = getProductExpirationDate(product);
    assert(getDateYear(date) == 2019);
    assert(getDateMonth(date) == 10);
    assert(getDateDay(date) == 10);

    setProductExpirationDate(product, createDate(2020, 11, 11));
    date = getProductExpirationDate(product);
    assert(getDateYear(date) == 2020);
    assert(getDateMonth(date) == 11);
    assert(getDateDay(date) == 11);
    destroyProduct(product);
}

void testAreProductsEqual() {
    Product* product1 = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    Product* product2 = createProduct("boom", "dairy", 13, createDate(2019, 10, 10));
    Product* product3 = createProduct("bang", "dairy", 13, createDate(2019, 10, 10));

    assert(areProductsEqual(product1, product2) == 1);
    assert(areProductsEqual(product1, product3) == 0);
    assert(areProductsEqual(product2, product3) == 0);
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testIsLess() {
    Product* product1 = createProduct("boom", "dairy", 19, createDate(2019, 10, 10));
    Product* product2 = createProduct("bee", "dairy", 13, createDate(2019, 10, 10));
    Product* product3 = createProduct("bang", "dairy", 14, createDate(2019, 10, 10));

    assert(isLess(product1, product2) == 0);
    assert(isLess(product1, product3) == 0);
    assert(isLess(product2, product1) == 1);
    assert(isLess(product2, product3) == 1);
    assert(isLess(product3, product1) == 1);
    assert(isLess(product3, product2) == 0);
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testDoesProductNameContainString() {
    Product* product1 = createProduct("boom", "dairy", 19, createDate(2019, 10, 10));
    assert(doesProductNameContainString(product1, "o") == 1);
    assert(doesProductNameContainString(product1, "oo") == 1);
    assert(doesProductNameContainString(product1, "ox") == 0);
    assert(doesProductNameContainString(product1, "") == 1);
    assert(doesProductNameContainString(product1, "bang") == 0);
    destroyProduct(product1);
}

void testIsNameLexicographicallyLarger() {
    Product* product1 = createProduct("boom", "dairy", 19, createDate(2019, 10, 10));
    Product* product2 = createProduct("bee", "dairy", 13, createDate(2019, 10, 10));
    Product* product3 = createProduct("bang", "dairy", 14, createDate(2019, 10, 10));

    assert(isNameLexicographicallyLarger(product1, product2) == 1);
    assert(isNameLexicographicallyLarger(product2, product1) == 0);
    assert(isNameLexicographicallyLarger(product1, product1) == 0);
    assert(isNameLexicographicallyLarger(product1, product3) == 1);
    assert(isNameLexicographicallyLarger(product3, product1) == 0);
    assert(isNameLexicographicallyLarger(product2, product3) == 1);
    assert(isNameLexicographicallyLarger(product3, product3) == 0);
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testIsCategoryNameEqualToString() {
    Product* product1 = createProduct("boom", "dairy", 19, createDate(2019, 10, 10));
    Product* product2 = createProduct("bee", "meat", 13, createDate(2019, 10, 10));
    Product* product3 = createProduct("bang", "sweets", 14, createDate(2019, 10, 10));

    assert(isCategoryNameEqualToString(product1, "meat") == 0);
    assert(isCategoryNameEqualToString(product1, "sweets") == 0);
    assert(isCategoryNameEqualToString(product1, "dairy") == 1);
    assert(isCategoryNameEqualToString(product1, "") == 1);
    assert(isCategoryNameEqualToString(product2, "meat") == 1);
    assert(isCategoryNameEqualToString(product2, "") == 1);
    assert(isCategoryNameEqualToString(product2, "dairy") == 0);
    assert(isCategoryNameEqualToString(product2, "sweets") == 0);
    assert(isCategoryNameEqualToString(product3, "") == 1);
    assert(isCategoryNameEqualToString(product3, "sweets") == 1);
    assert(isCategoryNameEqualToString(product3, "meat") == 0);
    assert(isCategoryNameEqualToString(product3, "dairy") == 0);

    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testIsGreater() {
    Product* product1 = createProduct("boom", "dairy", 19, createDate(2019, 10, 10));
    Product* product2 = createProduct("bee", "dairy", 13, createDate(2019, 10, 10));
    Product* product3 = createProduct("bang", "dairy", 14, createDate(2019, 10, 10));

    assert(isGreater(product1, product2) == 1);
    assert(isGreater(product1, product3) == 1);
    assert(isGreater(product2, product1) == 0);
    assert(isGreater(product2, product3) == 0);
    assert(isGreater(product3, product1) == 0);
    assert(isGreater(product3, product2) == 1);
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
}

void testValidateCategory() {
    int response;
    response = validateCategory("dairy");
    assert(response == 1);
    response = validateCategory("meat");
    assert(response == 1);
    response = validateCategory("fruit");
    assert(response == 1);
    response = validateCategory("fruits");
    assert(response == 0);
    response = validateCategory("aspkfjopawjegoi");
    assert(response == 0);
    response = validateCategory("sweets");
    assert(response == 1);
    response = validateCategory("sweet");
    assert(response == 0);
}

void testValidateExpirationDate() {
    int response;
    response = validateExpirationDate(2020, 10, 10);
    assert(response == 1);
    response = validateExpirationDate(2020, 2, 29);
    assert(response == 1);
    response = validateExpirationDate(2019, 2, 29);
    assert(response == 0);
    response = validateExpirationDate(2020, -1, 10);
    assert(response == 0);
    response = validateExpirationDate(2020, 13, 10);
    assert(response == 0);
    response = validateExpirationDate(2020, 10, 200);
    assert(response == 0);
    response = validateExpirationDate(2020, 10, -1);
    assert(response == 0);
}

void testIsYearLeap() {
    assert(isYearLeap(2020) == 1);
    assert(isYearLeap(2000) == 1);
    assert(isYearLeap(2019) == 0);
    assert(isYearLeap(2032) == 1);
    assert(isYearLeap(2026) == 0);
    assert(isYearLeap(2012) == 1);
}

void testCreateProductRepository() {
    Repository* repository = createProductRepository(10, 1);
    assert(getElementListLength(repository) == 0);
    assert(repository->productArray->capacity == 10);
    destroyRepository(repository);
}

void testDestroyRepository() {
    Repository* repository = createProductRepository(10,1 );
    destroyRepository(repository);
}

void testAddElement() {
    Repository* repository = createProductRepository(1, 1);
    Product* product = createProduct("a", "b", 3, createDate(1, 1, 1));
    addElement(repository, product, 0);
    Product* extractedProduct = getElementByIndex(repository->productArray, 0);
    assert(strcmp(getProductName(extractedProduct), "a") == 0);
    assert(strcmp(getProductCategory(extractedProduct), "b") == 0);
    assert(getProductQuantity(extractedProduct) == 3);
    Date date = getProductExpirationDate(extractedProduct);
    assert(getDateYear(date) == 1);
    assert(getDateMonth(date) == 1);
    assert(getDateDay(date) == 1);
    destroyRepository(repository);
}

void testUpdateElement() {
    Repository* repository = createProductRepository(1, 1);
    Product* product = createProduct("a", "b", 3, createDate(1, 1, 1));
    addElement(repository, product, 0);

    Product* extractedProduct = getElementByIndex(repository->productArray, 0);
    assert(strcmp(getProductName(extractedProduct), "a") == 0);
    assert(strcmp(getProductCategory(extractedProduct), "b") == 0);
    assert(getProductQuantity(extractedProduct) == 3);
    Date date = getProductExpirationDate(extractedProduct);
    assert(getDateYear(date) == 1);
    assert(getDateMonth(date) == 1);
    assert(getDateDay(date) == 1);

    Product* product1 = createProduct("a", "b", 100, createDate(2, 2, 2));
    updateElement(repository, product1, 0);

    extractedProduct = getElementByIndex(repository->productArray, 0);
    assert(strcmp(getProductName(extractedProduct), "a") == 0);
    assert(strcmp(getProductCategory(extractedProduct), "b") == 0);
    assert(getProductQuantity(extractedProduct) == 100);
    date = getProductExpirationDate(extractedProduct);
    assert(getDateYear(date) == 2);
    assert(getDateMonth(date) == 2);
    assert(getDateDay(date) == 2);
    destroyRepository(repository);
}

void testDeleteElement() {
    Repository* repository = createProductRepository(1, 1);
    Product* product = createProduct("a", "b", 3, createDate(1, 1, 1));
    addElement(repository, product, 0);
    
    Product* extractedProduct = getElementByIndex(repository->productArray, 0);
    assert(strcmp(getProductName(extractedProduct), "a") == 0);
    assert(strcmp(getProductCategory(extractedProduct), "b") == 0);
    assert(getProductQuantity(extractedProduct) == 3);
    Date date = getProductExpirationDate(extractedProduct);
    assert(getDateYear(date) == 1);
    assert(getDateMonth(date) == 1);
    assert(getDateDay(date) == 1);
    Product* product1 = createProduct("a", "b", 0, createDate(0, 0, 0));
    deleteElement(repository, product1, 0);
    assert(getElementListLength(repository) == 0);
    destroyRepository(repository);
}

void testFindProductInList() {
    Repository* repository = createProductRepository(10, 1);
    Product* product1 = createProduct("a", "b", 3, createDate(1, 1, 1));
    Product* product2 = createProduct("b", "c", 4, createDate(1, 1, 1));
    Product* product3 = createProduct("x", "y", 3, createDate(1, 1, 1));
    addElement(repository, product1, 0);
    addElement(repository, product2, 0);

    int response;
    response = findProductInList(repository, product1);
    assert(response == 0);
    response = findProductInList(repository, product2);
    assert(response == 1);
    response = findProductInList(repository, product3);
    assert(response == -1);
    destroyProduct(product3);
    destroyRepository(repository);
}

void testGetElementList() {
    Repository* repository = createProductRepository(10, 1);
    Product* product1 = createProduct("a", "b", 3, createDate(1, 1, 1));
    Product* product2 = createProduct("b", "c", 4, createDate(1, 1, 1));
    addElement(repository, product1, 0);
    addElement(repository, product2, 0);

    DynamicArray* list = getElementList(repository);

    assert(areProductsEqual((Product*)getElementByIndex(repository->productArray, 0), getElementByIndex(list, 0)));
    assert(areProductsEqual((Product*)getElementByIndex(repository->productArray, 1), getElementByIndex(list, 1)));
    int i;
    for (i = 0; i < 2; ++i)
        destroyProduct(getElementByIndex(list, i));
    destroyDynamicArray(&list);
    destroyRepository(repository);
}

void testGetElementListByCriteria() {
    Repository* repository = createProductRepository(10, 1);
    Product* product1 = createProduct("a", "b", 3, createDate(1, 1, 1));
    Product* product2 = createProduct("b", "c", 4, createDate(1, 1, 1));
    addElement(repository, product1, 0);
    addElement(repository, product2, 0);

    int length, i;
    DynamicArray* list = getElementListByCriteria(repository, "a", &doesProductNameContainString, &length);
    assert(length == 1);
    assert(areProductsEqual(getElementByIndex(list, 0), (Product*)getElementByIndex(repository->productArray, 0)));
    for (i = 0; i < length; ++i)
        destroyProduct(getElementByIndex(list, i));
    destroyDynamicArray(&list);
    destroyRepository(repository);
}

void testGetElementListLength() {
    Repository* repository = createProductRepository(10, 1);
    Product* product1 = createProduct("a", "b", 3, createDate(1, 1, 1));
    Product* product2 = createProduct("b", "c", 4, createDate(1, 1, 1));
    addElement(repository, product1, 0);
    assert(getElementListLength(repository) == 1);
    addElement(repository, product2, 0);
    assert(getElementListLength(repository) == 2);
    destroyRepository(repository);
}

void testCreateController() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    assert(getProductListLength(controller) == 0);
    assert(controller->repository->productArray->capacity == 10);
    destroyController(controller);
}

void testDestroyController() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    assert(getProductListLength(controller) == 0);
    assert(controller->repository->productArray->capacity == 10);
    destroyController(controller);
}

void testAddProduct() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    Product *product = createProduct("a", "b", 3, createDate(1, 1, 1));
    assert(getProductListLength(controller) == 1);
    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 0), product));
    destroyProduct(product);
    destroyController(controller);
}

void testUpdateProduct() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    Product *product = createProduct("a", "b", 3, createDate(1, 1, 1));
    assert(getProductListLength(controller) == 1);
    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 0), product));
    Product *product1 = createProduct("a", "b", 100, createDate(2, 2, 2));
    updateProduct(controller, "a", "b", 100, 2, 2, 2, 0);
    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 0), product1));
    destroyProduct(product);
    destroyProduct(product1);
    destroyController(controller);
}

void testDeleteProduct() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    Product *product = createProduct("a", "b", 3, createDate(1, 1, 1));
    assert(getProductListLength(controller) == 1);
    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 0), product));
    deleteProduct(controller, "a", "b", 0);
    assert(getProductListLength(controller) == 0);
    destroyProduct(product);
    destroyController(controller);
}

void testGetProductList() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    addProduct(controller, "b", "c", 3, 1, 1, 1, 0);
    DynamicArray* list = getProductList(controller);

    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 0), getElementByIndex(list, 0)));
    assert(areProductsEqual(getElementByIndex(controller->repository->productArray, 1), getElementByIndex(list, 1)));
    int i;
    for (i = 0; i < 2; ++i)
        destroyProduct(getElementByIndex(list, i));
    destroyDynamicArray(&list);
    destroyController(controller);
}

void testGetProductListLength() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    addProduct(controller, "b", "c", 3, 1, 1, 1, 0);
    assert(getProductListLength(controller) == 2);
    addProduct(controller, "x", "y", 3, 1, 1, 1, 0);
    assert(getProductListLength(controller) == 3);
    destroyController(controller);
}

void testFilterProductList() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 3, 1, 1, 1, 0);
    addProduct(controller, "b", "c", 3, 1, 1, 1, 0);
    addProduct(controller, "aa", "y", 1, 1, 1, 1, 0);
    Product* product1 = createProduct("a", "b", 3, createDate(1, 1, 1));
    Product* product2 = createProduct("aa", "y", 1, createDate(1, 1, 1));

    int length, i;
    DynamicArray *list = filterProductList(controller, "a", &doesProductNameContainString, &isLess, &length);

    assert(length == 2);
    assert(areProductsEqual(product1, getElementByIndex(list, 1)));
    assert(areProductsEqual(product2, getElementByIndex(list, 0)));
    destroyProduct(product1);
    destroyProduct(product2);
    for (i = 0; i < 2; ++i)
        destroyProduct(getElementByIndex(list, i));
    destroyDynamicArray(&list);
    destroyController(controller);
}

void testSortProductList() {
    Repository* repository = createProductRepository(10, 1);
    Controller* controller = createController(repository);
    addProduct(controller, "a", "b", 2, 1, 1, 1, 0);
    addProduct(controller, "b", "c", 3, 1, 1, 1, 0);
    addProduct(controller, "aa", "y", 1, 1, 1, 1, 0);

    Product* product1 = createProduct("a", "b", 2, createDate(1, 1, 1));
    Product* product2 = createProduct("b", "c", 3, createDate(1, 1, 1));
    Product* product3 = createProduct("aa", "y", 1, createDate(1, 1, 1));

    DynamicArray *list = getProductList(controller);
    sortProductList(list, getProductListLength(controller), &isLess);
    assert(areProductsEqual(product1, getElementByIndex(list, 1)));
    assert(areProductsEqual(product2, getElementByIndex(list, 2)));
    assert(areProductsEqual(product3, getElementByIndex(list, 0)));
    destroyProduct(product1);
    destroyProduct(product2);
    destroyProduct(product3);
    int i;
    for (i = 0; i < 3; ++i) {
        destroyProduct(getElementByIndex(list, i));
    }
    destroyDynamicArray(&list);
    destroyController(controller);
}

void testCreateDynamicArray() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    assert(dynamicArray->size == 0);
    assert(dynamicArray->capacity == 1);
    destroyDynamicArray(&dynamicArray);
}

void testResizeElementList() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    assert(dynamicArray->size == 0);
    assert(dynamicArray->capacity == 1);
    destroyDynamicArray(&dynamicArray);
}

void testNeedsResize() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int i = 1;
    assert(needsResize(dynamicArray) == 0);
    append(dynamicArray, &i);
    assert(needsResize(dynamicArray) == 1);
    destroyDynamicArray(&dynamicArray);
}

void testAppend() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int a[] = {1, 2, 3, 4, 5};
    int *element, i;
    for (i = 0; i < 5; ++i) {
        append(dynamicArray, &a[i]);
        if (i == 1)
            assert(dynamicArray->capacity == 2);
        else if (i == 2)
            assert(dynamicArray->capacity == 4);
        else if (i == 4)
            assert(dynamicArray->capacity == 8);
        element = (int*)getElementByIndex(dynamicArray, i);
        assert(*element == a[i]);
    }
    destroyDynamicArray(&dynamicArray);
}

void testDeleteByIndex() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int a[] = {1, 2, 3, 4, 5};
    int *element, i;
    for (i = 0; i < 5; ++i) {
        append(dynamicArray, &a[i]);
    }
    int nr = 2;
    int sz = 5;
    while (size(dynamicArray) > 0) {
        assert(size(dynamicArray) == sz);
        deleteByIndex(dynamicArray, 0);
        --sz;
        assert(size(dynamicArray) == sz);
        if (size(dynamicArray) > 0) {
            assert(nr == *((int*)getElementByIndex(dynamicArray, 0)));
            ++nr;
        }
    }
    destroyDynamicArray(&dynamicArray);
}

void testUpdateByIndex() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *element, i;
    for (i = 0; i < 5; ++i) {
        append(dynamicArray, &a[i]);
    }
    for (i = 5; i < 10; ++i) {
        updateByIndex(dynamicArray, i - 5, &a[i]);
    }
    for (i = 0; i < 5; ++i) {
        element = (int*)getElementByIndex(dynamicArray, i);
        assert(*element == a[i + 5]);
    }
    destroyDynamicArray(&dynamicArray);
}

void testGetElementByIndex() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *element, i;
    for (i = 0; i < 5; ++i) {
        append(dynamicArray, &a[i]);
    }
    for (i = 5; i < 10; ++i) {
        updateByIndex(dynamicArray, i - 5, &a[i]);
    }
    for (i = 0; i < 5; ++i) {
        element = (int*)getElementByIndex(dynamicArray, i);
        assert(*element == a[i + 5]);
    }
    destroyDynamicArray(&dynamicArray);
}

void testSize() {
    DynamicArray *dynamicArray = createDynamicArray(1);
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *element, i;
    assert(size(dynamicArray) == 0);
    for (i = 0; i < 5; ++i) {
        assert(size(dynamicArray) == i);
        append(dynamicArray, &a[i]);
        assert(size(dynamicArray) == i + 1);
    }
    destroyDynamicArray(&dynamicArray);
}