#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include <iostream>
#include "../Constants/Constants.h"

using namespace std;

bool Menu::login()
{
    return _controller.login();
}

void Menu::createNewAccount()
{
    _controller.createNewAccount();
}

void Menu::changePassword()
{
    _controller.changePassword();
}

void Menu::deleteCurrentAccount()
{
    _controller.deleteCurrentAccount();
}

void Menu::deleteAccountsByAdminRole()
{
    _controller.deleteAccountByUsername();
}

void Menu::reviewListOfInactiveAccounts()
{
    _controller.reviewListOfInactiveAccounts();
}

void Menu::viewListOfAccounts()
{
    _controller.printListOfAllAccounts();
}

void Menu::viewListOfInactiveAccounts()
{
    _controller.printListOfInactiveAccounts();
}

void Menu::home()
{
    bool isExit = false;
    char serverSelection = getMenuSelectionForServer();
    if (serverSelection == SERVER_DANANG || serverSelection == SERVER_HANOI)
    {
        string server = " ";
        if (serverSelection == SERVER_DANANG)
            server = DATABASE_SERVER_DN;
        else
            server = DATABASE_SERVER_HN;
        _controller.setupData(DATABASE_SERVER_DN);

        char selectionBeforeLogin;
        do
        {
            selectionBeforeLogin = setMenuSelectionBeforeLogin();
            switch (selectionBeforeLogin)
            {
            case SIGN_UP:
                createNewAccount();
                break;
            case SIGN_IN:
                bool isLoginSuccess;
                char isBackToHome;
                do
                {
                    bool isLoginSuccess = login();
                    cout << "Enter 1 to go back home page..." << endl;
                    cin >> isBackToHome;
                } while (!isLoginSuccess && isBackToHome != '1');
                if (isLoginSuccess)
                {
                    isExit = executeAccordingToSelectionMenuAfterLogin();
                }
                break;
            default:
                isExit = true;
                break;
            }
        } while (selectionBeforeLogin == '1' || selectionBeforeLogin == '2' || isExit == false);
        _controller.updateToDatabase();
    }
}

bool Menu::executeAccordingToSelectionMenuAfterLogin()
{
    bool isLogout = false;
    char selectionAfterLogin;
    map<string, string> accountInfo = _controller.getCurrentAccountInfo();
    if (accountInfo["Role"] == "admin")
    {
        selectionAfterLogin = setMenuSelectionAfterLoginAsAdminRole();
        switch (selectionAfterLogin)
        {
        case VIEW_LIST_OF_ALL_ACCOUNTS:
            viewListOfAccounts();
            break;
        case VIEW_LIST_OF_INACTIVE_ACCOUNTS:
            viewListOfInactiveAccounts();
            break;
        case DELETE_ACCOUNTS_IN_LIST_OF_ALL_ACCOUNTS:
            deleteAccountsByAdminRole();
            break;
        case DELETE_ACCOUNTS_IN_LIST_OF_INACTIVE_ACCOUNTS:
            reviewListOfInactiveAccounts();
            break;
        default:
            isLogout = true;
            break;
        }
    }
    else
    {
        selectionAfterLogin = setMenuSelectionAfterLoginAsUserRole();
        switch (selectionAfterLogin)
        {
        case CHANGE_PASSWORD:
            changePassword();
            break;
        case DELETE_CURRENT_ACCOUNT:
            deleteCurrentAccount();
            break;
        default:
            isLogout = true;
            break;
        }
    }
}

/*other functions*/

char Menu::getMenuSelectionForServer()
{
    char selection;
    cout << "Please enter according key below to select your server:" << endl
         << "Enter 1 to select server Da Nang" << endl
         << "Enter 2 to select server Ha Noi" << endl
         << "Enter any key isn't listed above to exit" << endl
         << "Your selection is: " << endl;
    cin >> selection;
    return selection;
}

char Menu::setMenuSelectionBeforeLogin()
{
    char selection;
    cout << "Welcome!" << endl
         << "Do you have any account?" << endl
         << "Enter any key isn't listed below to exit" << endl
         << "Enter 1 to sign up" << endl
         << "Enter 2 to sign in" << endl
         << "Your selection is: " << endl;
    cin >> selection;
    return selection;
}

char Menu::setMenuSelectionAfterLoginAsAdminRole()
{
    char selection;
    cout << "Enter any key isn't listed below to log out" << endl
         << "Enter 1 to review list of all accounts" << endl
         << "Enter 2 to review list of inactive accounts" << endl
         << "Enter 3 to delete accounts in list of all accounts" << endl
         << "Enter 4 to delete accounts in list of inactive accounts" << endl
         << "Your selection is: " << endl;
    cin >> selection;
    return selection;
}

char Menu::setMenuSelectionAfterLoginAsUserRole()
{
    char selection;
    cout << "Enter any key isn't listed below to log out" << endl
         << "Enter 1 to change password" << endl
         << "Enter 2 to delete current account" << endl
         << "Your selection is: " << endl;
    cin >> selection;
    return selection;
}

#endif