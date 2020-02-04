#include "userinterface.h"

UserInterface* createUserInterface(Controller* controller) {
    UserInterface* ui = (UserInterface*)malloc(sizeof(UserInterface));
    ui->controller = controller;
}

void destroyUserInterface(UserInterface *userInterface) {
    destroyController(userInterface->controller);
    free(userInterface);
}

void uiPrintHelp(UserInterface* userInterface) {
    printf("list - List all available products\n");
    printf("add - Add a product\n");
    printf("update - Update a product\n");
    printf("delete - Delete a product\n");
    printf("display - Display all the products whose names contain a given string sorted ascendingly by their quantities\n");
    printf("displaybyname - Display all the products whose names contain a given string sorted descendingly by their names\n");
    printf("displaysoonexpiringproducts ascending/descending - Display all the products of some category which expire in a specified number of days sorted ascendingly/descendingly by quantity\n");
    printf("displaybycategory - Display all the products which have a specified category\n");
    printf("undo - Undo the last change\n");
    printf("redo - Redo the last change\n");
    printf("exit - Exit the application\n");
}

void uiAddProduct(UserInterface* userInterface) {
    char name[30] = {};
    char category[30] = {};
    int quantity;
    int year, month, day;

    printf("Enter the product's name: ");
    int foundName = scanf("%s", name);
    if (foundName != 1) {
        printf("\nInvalid name.\n");
        return;
    }

    printf("\nEnter the product's category: ");
    int foundCategory = scanf("%s", category);
    if (foundCategory != 1 || !validateCategory(category)) {
        printf("\nInvalid category.\n");
        return;
    }

    printf("\nEnter the product's quantity: ");
    int foundQuantity = scanf("%d", &quantity);
    if (foundQuantity != 1) {
        printf("\nInvalid quantity.\n");
        return;
    }

    printf("\nEnter the product's expiration date (year month day): ");
    int foundDate = scanf("%d %d %d", &year, &month, &day);
    if (foundDate != 3 || !validateExpirationDate(year, month, day)) {
        printf("\nInvalid expiration date.\n");
        return;
    }

    addProduct(userInterface->controller, name, category, quantity, year, month, day, 1);
    printf("\n");
}

void uiUpdateProduct(UserInterface* userInterface) {
    char name[30];
    char category[30];
    int quantity;
    int year, month, day;

    printf("Enter the product's name: ");
    int foundName = scanf("%s", name);
    if (foundName != 1) {
        printf("\nInvalid name.\n");
        return;
    }

    printf("\nEnter the product's category: ");
    int foundCategory = scanf("%s", category);
    if (foundCategory != 1 || !validateCategory(category)) {
        printf("\nInvalid category.\n");
        return;
    }

    printf("\nEnter the product's quantity: ");
    int foundQuantity = scanf("%d", &quantity);
    if (foundQuantity != 1 || quantity <= 0) {
        printf("\nInvalid quantity.\n");
        return;
    }

    printf("\nEnter the product's expiration date (year month day): ");
    int foundDate = scanf("%d %d %d", &year, &month, &day);
    if (foundDate != 3 || !validateExpirationDate(year, month, day)) {
        printf("\nInvalid expiration date.\n");
        return;
    }
    printf("\n");
    int updated = updateProduct(userInterface->controller, name, category, quantity, year, month, day, 1);
    if (updated == 0) {
        printf("The element wasn't found.\n");
    }
}

void uiDeleteProduct(UserInterface* userInterface) {
    char name[30];
    char category[30];
    printf("Enter the product's name: ");
    int foundName = scanf("%s", name);
    if (foundName != 1) {
        printf("\nInvalid name.\n");
        return;
    }

    printf("\nEnter the product's category: ");
    int foundCategory = scanf("%s", category);
    if (foundCategory != 1 || !validateCategory(category)) {
        printf("\nInvalid category.\n");
        return;
    }
    printf("\n");
    int deleted = deleteProduct(userInterface->controller, name, category, 1);
    if (deleted == 0) {
        printf("Nothing to delete, the element wasn't found.\n");
    }
}

void uiListProducts(UserInterface* userInterface) {
    DynamicArray *list = getProductList(userInterface->controller);
    int length = getProductListLength(userInterface->controller), i;

    Product* currentProduct;
    char name[30], category[30];
    int quantity, year, month, day;
    Date date;

    if (length == 0)
        printf("The list is empty!");
    for (i = 0; i < length; ++i) {
        currentProduct = getElementByIndex(list, i);
        strcpy(name, getProductName(currentProduct));
        strcpy(category, getProductCategory(currentProduct));
        quantity = getProductQuantity(currentProduct);
        date = getProductExpirationDate(currentProduct);
        year = getDateYear(date);
        month = getDateMonth(date);
        day = getDateDay(date);
        printf("Name: %s Category: %s Quantity: %d Expiration date: %d-%d-%d\n", name, category, quantity,
                                                                                 year, month, day);
    }
    destroyProductList(list);
    destroyDynamicArray(&list);
}

void uiDisplayProducts(UserInterface* userInterface) {
    char givenString[50];
    int filteredListLength, i;

    printf("Please provide the string to be searched: ");
    scanf("%s", givenString);
    printf("\n");

    DynamicArray* filteredList = filterProductList(userInterface->controller, givenString, &doesProductNameContainString, &isLess,  &filteredListLength);
    Product* currentProduct;
    char name[30], category[30];
    int quantity, year, month, day;
    Date date;

    if (filteredListLength == 0)
        printf("The list is empty!");
    for (i = 0; i < filteredListLength; ++i) {
        currentProduct = getElementByIndex(filteredList, i);
        strcpy(name, getProductName(currentProduct));
        strcpy(category, getProductCategory(currentProduct));
        quantity = getProductQuantity(currentProduct);
        date = getProductExpirationDate(currentProduct);
        year = getDateYear(date);
        month = getDateMonth(date);
        day = getDateDay(date);
        printf("Name: %s Category: %s Quantity: %d Expiration date: %d-%d-%d\n", name, category, quantity,
               year, month, day);
    }
    destroyProductList(filteredList);
    destroyDynamicArray(&filteredList);
}


void uiDisplayProductsByName(UserInterface* userInterface) {
    char givenString[50];
    int filteredListLength, i;

    printf("Please provide the string to be searched: ");
    scanf("%s", givenString);
    printf("\n");

    DynamicArray* filteredList = filterProductList(userInterface->controller, givenString, &doesProductNameContainString, &isNameLexicographicallyLarger, &filteredListLength);
    Product* currentProduct;
    char name[30], category[30];
    int quantity, year, month, day;
    Date date;

    if (filteredListLength == 0)
        printf("The list is empty!");
    for (i = 0; i < filteredListLength; ++i) {
        currentProduct = getElementByIndex(filteredList, i);
        strcpy(name, getProductName(currentProduct));
        strcpy(category, getProductCategory(currentProduct));
        quantity = getProductQuantity(currentProduct);
        date = getProductExpirationDate(currentProduct);
        year = getDateYear(date);
        month = getDateMonth(date);
        day = getDateDay(date);
        printf("Name: %s Category: %s Quantity: %d Expiration date: %d-%d-%d\n", name, category, quantity,
               year, month, day);
    }
    destroyProductList(filteredList);
    destroyDynamicArray(&filteredList);
}

void uiDisplayProductsByCategoryWhichExpireSoon(UserInterface* userInterface, int ascending) {
    char givenString[50];
    int filteredListLength, i, dayOffset;
    int year, month, day;

    printf("Please provide the category to be searched: ");
    int foundString = scanf("%s", givenString);
    if (foundString != 1) {
        printf("Invalid string\n");
        return;
    }
    printf("\n");

    printf("Please enter today's date (year month day): ");
    int foundDate = scanf("%d %d %d", &year, &month, &day);
    if (foundDate != 3 || !validateExpirationDate(year, month, day)) {
        printf("Invalid date\n");
        return;
    }
    printf("\n");

    printf("Please provide the maximum number of days between today's date and the products expiration date:" );
    int foundDays = scanf("%d", &dayOffset);
    if (foundDays != 1) {
        printf("Invalid provided day difference");
        return;
    }
    printf("\n");
    Date todaysDate = createDate(year, month, day);

    DynamicArray* filteredList = NULL;
    if (ascending == 1)
        filteredList = filterProductList(userInterface->controller, givenString, &isCategoryNameEqualToString, &isLess, &filteredListLength);
    else
        filteredList = filterProductList(userInterface->controller, givenString, &isCategoryNameEqualToString, &isGreater, &filteredListLength);
    Product* currentProduct;
    char name[30], category[30];
    int quantity;
    Date date;
    int dayDifference;

    if (filteredListLength == 0)
        printf("The list is empty!\n");
    for (i = 0; i < filteredListLength; ++i) {
        dayDifference = getDayDifference(todaysDate, getProductExpirationDate((Product*)getElementByIndex(filteredList, i)));
        if (dayDifference >= 0 && dayDifference <= dayOffset) {
            currentProduct = getElementByIndex(filteredList, i);
            strcpy(name, getProductName(currentProduct));
            strcpy(category, getProductCategory(currentProduct));
            quantity = getProductQuantity(currentProduct);
            date = getProductExpirationDate(currentProduct);
            year = getDateYear(date);
            month = getDateMonth(date);
            day = getDateDay(date);
            printf("Name: %s Category: %s Quantity: %d Expiration date: %d-%d-%d\n", name, category, quantity,
                   year, month, day);
        }
    }
    destroyProductList(filteredList);
    destroyDynamicArray(&filteredList);
}

void uiDisplayProductsByCategory(UserInterface* userInterface) {
    char givenString[50];
    int filteredListLength, i;

    printf("Please provide the string to be searched: ");
    scanf("%s", givenString);
    printf("\n");
    if (!validateCategory(givenString)) {
        printf("Invalid category\n");
        return;
    }

    DynamicArray* filteredList = filterProductList(userInterface->controller, givenString, &isCategoryNameEqualToString, &isLess, &filteredListLength);
    Product* currentProduct;
    char name[30], category[30];
    int quantity, year, month, day;
    Date date;

    if (filteredListLength == 0)
        printf("The list is empty!");
    for (i = 0; i < filteredListLength; ++i) {
        currentProduct = getElementByIndex(filteredList, i);
        strcpy(name, getProductName(currentProduct));
        strcpy(category, getProductCategory(currentProduct));
        quantity = getProductQuantity(currentProduct);
        date = getProductExpirationDate(currentProduct);
        year = getDateYear(date);
        month = getDateMonth(date);
        day = getDateDay(date);
        printf("Name: %s Category: %s Quantity: %d Expiration date: %d-%d-%d\n", name, category, quantity,
               year, month, day);
    }
    destroyProductList(filteredList);
    destroyDynamicArray(&filteredList);
}

void uiUndo(UserInterface* userInterface) {
    int completedUndo = undoChanges(userInterface->controller);
    if (completedUndo == 0)
        printf("Nothing to undo!\n");
}

void uiRedo(UserInterface* userInterface) {
    int completedRedo = redoChanges(userInterface->controller);
    if (completedRedo == 0)
        printf("Nothing to redo!\n");
}

void uiRunApplication(UserInterface* userInterface) {
    uiPrintHelp(userInterface);
    char choice[40] = {};
    char sortingAlignment[40] = {};

    while (strcmp(choice, "exit") != 0) {
        printf(">> ");
        scanf("%s", choice);
        if (strcmp(choice, "add") == 0)
            uiAddProduct(userInterface);
        else if (strcmp(choice, "update") == 0)
            uiUpdateProduct(userInterface);
        else if (strcmp(choice, "delete") == 0)
            uiDeleteProduct(userInterface);
        else if (strcmp(choice, "list") == 0)
            uiListProducts(userInterface);
        else if (strcmp(choice, "display") == 0)
            uiDisplayProducts(userInterface);
        else if (strcmp(choice, "displaybyname") == 0)
            uiDisplayProductsByName(userInterface);
        else if (strcmp(choice, "displaysoonexpiringproducts") == 0) {
            scanf("%s", sortingAlignment);
            if (strcmp(sortingAlignment, "ascending") == 0)
                uiDisplayProductsByCategoryWhichExpireSoon(userInterface, 1);
            else if (strcmp(sortingAlignment, "descending") == 0)
                uiDisplayProductsByCategoryWhichExpireSoon(userInterface, 0);
            else {
                printf("Invalid sorting alignment\n");
            }
        }
        else if (strcmp(choice, "displaybycategory") == 0)
            uiDisplayProductsByCategory(userInterface);
        else if (strcmp(choice, "undo") == 0)
            uiUndo(userInterface);
        else if (strcmp(choice, "redo") == 0)
            uiRedo(userInterface);
        else if (strcmp(choice, "exit") != 0)
            printf("\nInvalid command.\n");
    }
}