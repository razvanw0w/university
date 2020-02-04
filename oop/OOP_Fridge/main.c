#include "ui/userinterface.h"
#include "tests/tests.h"

int main() {
    Repository* repository = createProductRepository(10, 2);
    Controller* controller = createController(repository);
    UserInterface* ui = createUserInterface(controller);
    addProduct(ui->controller, "ham", "meat", 103, 2019, 10, 11, 0);
    addProduct(ui->controller, "yogurt", "dairy", 203, 2020, 11, 11, 0);
    addProduct(ui->controller, "apple", "fruit", 1002, 2021, 10, 11, 0);
    addProduct(ui->controller, "cheese", "dairy", 53, 2020, 10, 11, 0);
    addProduct(ui->controller, "spongecake", "sweets", 25, 2020, 10, 11, 0);
    addProduct(ui->controller, "salami", "meat", 300, 2023, 10, 11, 0);
    addProduct(ui->controller, "lemon", "fruit", 503, 2019, 10, 19, 0);
    addProduct(ui->controller, "chocolate", "sweets", 1010, 2019, 12, 11, 0);
    addProduct(ui->controller, "chicken_breast", "meat", 932, 2019, 12, 20, 0);
    addProduct(ui->controller, "milk", "dairy", 103, 2019, 10, 11, 0);
    initProductRepository(ui->controller->repository);


    runTests();
    uiRunApplication(ui);
    destroyUserInterface(ui);
    return 0;
}