#ifndef MENU_H
#define MENU_H

#include "../DataProcessing/Controller.h"

class Menu
{
private:
    Controller _controller;

public:
    Menu();
    bool login();
    void createNewAccount();
    void changePassword();
    void deleteAccountsByAdminRole();
    void deleteCurrentAccount();
    void reviewListOfInactiveAccounts();
    void viewListOfAccounts();
    void viewListOfInactiveAccounts();
    void home();
    bool executeAccordingToSelectionMenuAfterLogin();
    char getMenuSelectionForServer();
    char setMenuSelectionBeforeLogin();
    char setMenuSelectionAfterLoginAsAdminRole();
    char setMenuSelectionAfterLoginAsUserRole();
};

#endif