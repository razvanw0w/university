#ifndef OOP3_USERINTERFACE_H
#define OOP3_USERINTERFACE_H

#include "../controller/controller.h"
#include "../validation/validation.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    Controller* controller;
}UserInterface;

UserInterface* createUserInterface(Controller* controller);
void destroyUserInterface(UserInterface* userInterface);
void uiAddProduct(UserInterface* userInterface);
void uiUpdateProduct(UserInterface* userInterface);
void uiDeleteProduct(UserInterface* userInterface);
void uiListProducts(UserInterface* userInterface);
void uiRunApplication(UserInterface* userInterface);
void uiPrintHelp(UserInterface* userInterface);
void uiDisplayProducts(UserInterface* userInterface);
void uiDisplayProductsByName(UserInterface* userInterface);
void uiDisplayProductsByCategory(UserInterface* userInterface);
void uiDisplayProductsByCategoryWhichExpireSoon(UserInterface* userInterface, int ascending);
void uiUndo(UserInterface* userInterface);
void uiRedo(UserInterface* userInterface);

#endif //OOP3_USERINTERFACE_H
