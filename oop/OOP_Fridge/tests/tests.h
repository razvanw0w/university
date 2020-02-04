#ifndef OOP3_TESTS_H
#define OOP3_TESTS_H

#include "../controller/controller.h"
#include "../validation/validation.h"
#include <assert.h>

void runTests();
// Date
void testDate();
void testCreateDate();
void testGetDateYear();
void testGetDateMonth();
void testGetDateDay();
void testSetDateYear();
void testSetDateMonth();
void testSetDateDay();
void testIsDateLess();
void testCountDaysUntilDate();
void testGetDayDifference();
// Product
void testProduct();
void testCreateProduct();
void testDestroyProduct();
void testGetProductName();
void testGetProductCategory();
void testGetProductQuantity();
void testGetProductExpirationDate();
void testSetProductName();
void testSetProductCategory();
void testSetProductQuantity();
void testSetProductExpirationDate();
void testAreProductsEqual();
void testIsLess();
void testDoesProductNameContainString();
void testIsNameLexicographicallyLarger();
void testIsCategoryNameEqualToString();
void testIsGreater();
// Validation
void testValidation();
void testValidateCategory();
void testValidateExpirationDate();
void testIsYearLeap();
// Repository
void testRepository();
void testCreateProductRepository();
void testDestroyRepository();
void testAddElement();
void testUpdateElement();
void testDeleteElement();
void testFindProductInList();
void testGetElementList();
void testGetElementListByCriteria();
void testGetElementListLength();
// Controller
void testController();
void testCreateController();
void testDestroyController();
void testAddProduct();
void testUpdateProduct();
void testDeleteProduct();
void testGetProductList();
void testGetProductListLength();
void testFilterProductList();
void testSortProductList();
// DynamicArray
void testDynamicArray();
void testCreateDynamicArray();
void testDestroyDynamicArray();
void testResizeElementList();
void testNeedsResize();
void testAppend();
void testDeleteByIndex();
void testUpdateByIndex();
void testGetElementByIndex();
void testSize();

#endif //OOP3_TESTS_H
