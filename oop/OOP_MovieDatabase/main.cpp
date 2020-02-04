#include <iostream>
#include "tests/Tests.h"
#include "repository/repository.h"
#include "repository/CSVRepository.h"
#include "repository/HTMLRepository.h"
#include "repository/MYSQLRepository.h"
#include "controller/adminController.h"
#include "userinterface/userinterface.h"

int main() {
    const int TESTING_ONLY = 0;

    if (TESTING_ONLY == 1) {
        Tests::testAll();
        std::cout << "All tests passed!\n";
    }
    else {
        Repository *repository;
        std::cout << "CSV, MYSQL or HTML?: ";
        std::string response;
        std::cin >> response;
        bool choseCSV = false;
        if (response == "CSV") {
            repository = new CSVRepository{"movies.csv", "watchlist.csv"};
            choseCSV = true;
        }
        else if (response == "HTML") {
            repository = new HTMLRepository{"movies.csv", "watchlist.html"};
        }
        else {
            repository = new MYSQLRepository{"movies.csv"};
        }
        AdminController adminController {*repository};
        UserController userController {*repository, response};
        UserInterface userInterface {adminController, userController};
        userInterface.runApplication();
        delete repository;
    }
    return 0;
}