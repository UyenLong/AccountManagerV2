#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include <iostream>
#define SERVER_DANANG '1'
#define SERVER_HANOI '2'
#define DATABASE_SERVER_DN ".\\DataBase\\Database1.txt"
#define DATABASE_SERVER_HN ".\\DataBase\\Database2.txt"
#define SIGN_UP '1'
#define SIGN_IN '2'
#define VIEW_LIST_OF_ALL_ACCOUNTS '1'
#define VIEW_LIST_OF_INACTIVE_ACCOUNTS '2'
#define DELETE_ACCOUNTS_IN_LIST_OF_ALL_ACCOUNTS '3'
#define DELETE_ACCOUNTS_IN_LIST_OF_INACTIVE_ACCOUNTS '4'
#define CHANGE_PASSWORD '1'
#define DELETE_CURRENT_ACCOUNT '2'

using namespace std;

Menu::Menu()
{
    Controller controller{};
    _controller = controller;
}

bool Menu::login()
{
    cout << "---------------------------" <<endl;
    return _controller.login();
    cout << "---------------------------" <<endl;
}

void Menu::createNewAccount()
{
    cout << "---------------------------" <<endl;
    _controller.createNewAccount();
    cout << "---------------------------" <<endl;
}

void Menu::changePassword()
{
    cout << "---------------------------" <<endl;
    _controller.changePassword();
    cout << "---------------------------" <<endl;
}

void Menu::deleteCurrentAccount()
{
    cout << "---------------------------" <<endl;
    _controller.deleteCurrentAccount();
    cout << "---------------------------" <<endl;
}

void Menu::deleteAccountsByAdminRole()
{
    cout << "---------------------------" <<endl;
    _controller.deleteAccountByUsername();
    cout << "---------------------------" <<endl;
}

void Menu::reviewListOfInactiveAccounts()
{
    cout << "---------------------------" <<endl;
    _controller.reviewListOfInactiveAccounts();
    cout << "---------------------------" <<endl;
}

void Menu::viewListOfAccounts()
{
    cout << "---------------------------" <<endl;
    _controller.printListOfAllAccounts();
    cout << "---------------------------" <<endl;
}

void Menu::viewListOfInactiveAccounts()
{
    cout << "---------------------------" <<endl;
    _controller.printListOfInactiveAccounts();
    cout << "---------------------------" <<endl;
}

void Menu::home()
{
    bool isExit = false;
    char serverSelection = getMenuSelectionForServer();
    cout << "Server selection is: " << serverSelection << endl;
    if (serverSelection == SERVER_DANANG || serverSelection == SERVER_HANOI)
    {
        string server = " ";
        if (serverSelection == SERVER_DANANG)
            server = DATABASE_SERVER_DN;
        else
            server = DATABASE_SERVER_HN;
        _controller.setupData(server);

        char selectionBeforeLogin;
        do
        {
            selectionBeforeLogin = setMenuSelectionBeforeLogin();
            switch (selectionBeforeLogin)
            {
            case SIGN_UP:
                char stopCondition;
                do
                {
                    cout << "-----------------------------------------------" << endl;
                    createNewAccount();
                    cout << "Do you want to continue?" << endl
                         << "Please enter 1 if you want to return home page." << endl
                         << "Enter other keys to continue." << endl;
                    cin >> stopCondition;
                } while (stopCondition != '1');
                break;
            case SIGN_IN:
                bool isLoginSuccess;
                char isBackToHome;
                do
                {
                    cout << "Please log in:" << endl;
                    bool isLoginSuccess = login();
                    if (isLoginSuccess)
                    {
                        isExit = executeAccordingToSelectionMenuAfterLogin();
                        if (isExit)
                            isBackToHome = '1';
                    }
                    else
                    {
                        cout << "Enter 1 to go back home page..." << endl
                             << "Enter other key to continue." << endl;
                        cin >> isBackToHome;
                    }
                } while (isBackToHome != '1');
                break;
            default:
                isExit = true;
                break;
            }
            _controller.updateToDatabase();
        } while (selectionBeforeLogin == '1' || selectionBeforeLogin == '2' || isExit == false);
    }
}

bool Menu::executeAccordingToSelectionMenuAfterLogin()
{
    bool isLogout = false;
    char selectionAfterLogin;
    char stopCondition = '1';
    map<string, string> accountInfo = _controller.getCurrentAccountInfo();
    cout << "Role is: " << accountInfo["Role"] << endl;
    if (accountInfo["Role"] == "admin")
    {
        do
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
        } while (isLogout == false);
    }
    else
    {
        do
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
        } while (isLogout == false);
    }
    return isLogout;
}

/*other functions*/

char Menu::getMenuSelectionForServer()
{
    char selection;
    cout << "Please enter according key below to select your server:" << endl
         << "Enter 1 to select server Da Nang" << endl
         << "Enter 2 to select server Ha Noi" << endl
         << "Enter any key isn't listed above to exit" << endl
         << "-----------------------------------------------" << endl
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
         << "-----------------------------------------------" << endl
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
         << "-----------------------------------------------" << endl
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
         << "-----------------------------------------------" << endl
         << "Your selection is: " << endl;
    cin >> selection;
    return selection;
}

#endif