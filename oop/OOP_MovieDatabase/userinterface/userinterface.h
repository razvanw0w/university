//
// Created by razvan on 26.03.2019.
//

#ifndef OOP5_USERINTERFACE_H
#define OOP5_USERINTERFACE_H


#include "../controller/adminController.h"
#include "../controller/userController.h"

class UserInterface {
private:
    AdminController& adminController;
    UserController& userController;
    void uiAdminAdd();
    void uiAdminDelete();
    void uiAdminUpdate();
    void uiAdminList();
    void uiUserList();
    void uiUserDelete();
    void uiUserWatchlist();
    void uiUserAdd();
    void uiUserNext();
    void displayAdminOptions();
    void displayUserOptions();
    void displayUserListOptions();
    void runAdmin();
    void runUser();
    void printMovieUser(const Movie &movie);
    void printMovieAdmin(const Movie &movie) const;
    void playTrailerUser(const std::string& link);
    std::string getCurrentWorkingDir() const;

public:
    UserInterface(AdminController& adminController, UserController& userController);
    void runApplication();
};


#endif //OOP5_USERINTERFACE_H
