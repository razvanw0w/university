#include <iostream>
#include "userinterface.h"
#include <unistd.h>

void UserInterface::uiAdminAdd() {
    std::string name, genre, trailer;
    int yearOfRelease, numberOfLikes;
    std::cin.get();
    std::cout << "name: ";
    getline(std::cin, name);
    std::cout << "\ngenre: ";
    getline(std::cin, genre);
    std::cout << "\nyear of release: ";
    std::cin >> yearOfRelease;
    std::cout << "\nnumber of likes: ";
    std::cin >> numberOfLikes;
    std::cout << "\ntrailer link: ";
    std::cin >> trailer;
    std::cout << '\n';
    //if ((trailer.find("http://") != 0 && trailer.find("https://") != 0) || numberOfLikes < 0 || yearOfRelease < 1900)
        //throw std::runtime_error("invalid movie");

    adminController.adminAddMovie(name, genre, yearOfRelease, numberOfLikes, trailer);
}

void UserInterface::uiAdminDelete() {
    std::string name, genre;
    std::cin.get();
    int yearOfRelease;
    std::cout << "name: ";
    getline(std::cin, name);
    std::cout << "\ngenre: ";
    getline(std::cin, genre);
    std::cout << "\nyear of release: ";
    std::cin >> yearOfRelease;
    std::cout << '\n';
    //if (yearOfRelease < 1900)
        //throw std::runtime_error("invalid movie");

    adminController.adminDeleteMovie(name, genre, yearOfRelease);
}

void UserInterface::uiAdminUpdate() {
    std::string name, genre, trailer;
    int yearOfRelease, numberOfLikes;
    std::cin.get();
    std::cout << "name: ";
    getline(std::cin, name);
    std::cout << "\ngenre: ";
    getline(std::cin, genre);
    std::cout << "\nyear of release: ";
    std::cin >> yearOfRelease;
    std::cout << "\nnew number of likes: ";
    std::cin >> numberOfLikes;
    std::cout << "\nnew trailer link: ";
    std::cin >> trailer;
    std::cout << '\n';
    //if ((trailer.find("http://") != 0 && trailer.find("https://") != 0) || numberOfLikes < 0 || yearOfRelease < 1900)
        //throw std::runtime_error("invalid movie");

    adminController.adminUpdateMovie(name, genre, yearOfRelease, numberOfLikes, trailer);
}

void UserInterface::uiAdminList() {
    auto list = adminController.adminGetMovieList();
    std::cout << "========== MOVIE LIST ==========\n";
    if (list.size() == 0)
        std::cout << "No movies!\n";
    for (const Movie& movie: list) {
        printMovieAdmin(movie);
    }
    std::cout << "========== MOVIE LIST ==========\n";
}

void UserInterface::printMovieAdmin(const Movie &movie) const {
    std::cout << "title: " << movie.getTitle() << '\n'
              << "genre: " << movie.getGenre() << '\n'
              << "year of release: " << movie.getYearOfRelease() << '\n'
              << "number of likes: " << movie.getNumberOfLikes() << '\n'
              << "trailer link: " << movie.getTrailer() << '\n';
    std::cout << '\n';
}

UserInterface::UserInterface(AdminController &adminController, UserController &userController): adminController{adminController}, userController {userController}
{}

void UserInterface::runApplication() {
    std::string mode = "";
    while (mode != "exit") {
        std::cout << "admin, user or exit?: ";
        std::cin >> mode;
        if (mode == "admin")
            runAdmin();
        if (mode == "user")
            runUser();
    }
}

void UserInterface::displayAdminOptions() {
    std::cout << "add - add a new movie\n"
              << "delete - delete a movie\n"
              << "update - update a movie\n"
              << "list - list all movies\n"
              << "exit - exit the application\n";
}

void UserInterface::displayUserOptions() {
    std::cout << "list - see the movies in the database having a given genre\n"
              << "delete - delete a movie from the watch list\n"
              << "watchlist - see the watchlist\n"
              << "exit - exit the application\n";
}

void UserInterface::runAdmin() {
    std::string choice = "";
    while (choice != "exit") {
        displayAdminOptions();
        std::cout << "Your choice?: ";
        std::cin >> choice;
        try {
            if (choice == "add")
                uiAdminAdd();
            else if (choice == "update")
                uiAdminUpdate();
            else if (choice == "delete")
                uiAdminDelete();
            else if (choice == "list")
                uiAdminList();
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << '\n';
        }
    }
}

void UserInterface::runUser() {
    std::string choice = "";
    while (choice != "exit") {
        displayUserOptions();
        std::cout << "Your choice?: ";
        std::cin >> choice;
        try {
            if (choice == "list")
                uiUserList();
            else if (choice == "delete")
                uiUserDelete();
            else if (choice == "watchlist")
                uiUserWatchlist();
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << '\n';
        }
    }
}

void UserInterface::printMovieUser(const Movie& movie) {
    std::cout << "title: " << movie.getTitle() << '\n'
              << "genre: " << movie.getGenre() << '\n'
              << "year of release: " << movie.getYearOfRelease() << '\n'
              << "number of likes: " << movie.getNumberOfLikes() << '\n';
    std::cout << '\n';
    playTrailerUser(movie.getTrailer());
}

void UserInterface::playTrailerUser(const std::string &link) {
    std::string command = "firefox " + link;
    system(command.c_str());
}

void UserInterface::displayUserListOptions() {
    std::cout << "add - add the current movie to the watch list\n"
              << "next - go to the next movie from the watch list\n"
              << "stop - stop seeing the movies from the database\n";
}

void UserInterface::uiUserList() {
    std::string genre, choice = "";
    std::cout << "Enter the desired genre: ";
    std::cin >> genre;
    std::cout << "\n\n";

    userController.listMoviesByGenre(genre);
    Movie currentMovie;
    while (choice != "stop") {
        currentMovie = userController.getCurrentMovie();
        printMovieUser(currentMovie);
        displayUserListOptions();
        std::cout << "Your choice: ";
        std::cin >> choice;
        if (choice == "add") {
            uiUserAdd();
            uiUserNext();
        }
        else if (choice == "next")
            uiUserNext();
    }
}

void UserInterface::uiUserDelete() {
    std::string name, genre, choice;
    int yearOfRelease;
    std::cin.get();
    std::cout << "name: ";
    getline(std::cin, name);
    std::cout << "\ngenre: ";
    getline(std::cin, genre);
    std::cout << "\nyear of release: ";
    std::cin >> yearOfRelease;
    std::cout << "\ndid you like the movie? (yes/no): ";
    std::cin >> choice;
    bool liked = (choice == "yes");
    userController.deleteMovieFromWatchlist(name, genre, yearOfRelease, liked);
}

void UserInterface::uiUserWatchlist() {
    std::string command = "";
    if (userController.isRepositoryCSV())
        command = "libreoffice --calc " + std::string("\"") + getCurrentWorkingDir() + std::string("\"/") + userController.getExternalFilename();
    else if (userController.isRepositoryHTML())
        command = "firefox " + std::string("\"")+ getCurrentWorkingDir() + std::string("\"/") + userController.getExternalFilename();
    system(command.c_str());
}

void UserInterface::uiUserAdd() {
    userController.addMovieToWatchlist();
}

void UserInterface::uiUserNext() {
    userController.goToNextMovieByGenre();
}

std::string UserInterface::getCurrentWorkingDir() const {
    char buffer[300];
    getcwd(buffer, 300);
    return std::string(buffer);
}
