#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include "Controller.h"
#include <regex>
#include <iostream>
#include <string>
#include "../Utility/Utility.h"

using namespace std;

bool isPasswordInCorrectForm(string password)
{
    return regex_match(password, regex(PASSWORD_RULES));
}

Controller::Controller()
{
    _fileHandler = new FileHandler();
    _tableData = new TableData();
    _admin = new Admin();
    _user = new User();
}

Controller::~Controller()
{
    delete(_fileHandler);
    delete(_tableData);
    delete(_admin);
    delete(_user);
}

bool Controller::isValidAccount(Account *account)
{
    bool isValid = false;
    vector<RowData *> tableData = _tableData->getTableData();
    map<string, string> accountInfo = account->getAccountInfo();
    for (RowData *rowData : tableData)
    {
        map<string, string> dataOfRow = rowData->getRowData();
        if (dataOfRow["ID"] == accountInfo["ID"] && dataOfRow["Password"] == accountInfo["Password"])
        {
            accountInfo["Role"] = dataOfRow["Role"];
            accountInfo["Status"] = dataOfRow["Role"];
            account->setAccountInfo(accountInfo);
            isValid = true;
            break;
        }
    }
    Utility::deleteVectorPtrs(tableData);
    return isValid;
}

bool Controller::login()
{
    Account *account;
    account->setAccountInfo();
    bool isAccountValid = isValidAccount(account);
    if (isAccountValid)
    {
        cout << "Login successfully!" << endl;
        setCurrentAccountInfo(account);
    }
    else
        cout << "Login fail!" << endl;
    delete(account);
    return isAccountValid;
}

void Controller::setCurrentAccountInfo(Account *account)
{
    map<string, string> accountInfo = account->getAccountInfo();
    _user->setAccountInfo(account);
}

void Controller::createNewAccount()
{
    User *user;
    user->setAccountInfo();
    map<string, string> accountInfo = user->getAccountInfo();
    if (isPasswordInCorrectForm(accountInfo["Password"]) && !isExistAccount(accountInfo["ID"]))
    {
        _admin->addNewAccount(user);
        _tableData->setTableData(_admin->getListOfAccounts());
        cout << "------------------------------------" << endl;
        cout << "Create account successfully!" << endl;
    }
    else
    {
        cout << "------------------------------------" << endl;
        cout << "Please try again!" << endl;
    }
    delete(user);
}

void Controller::changePassword()
{
    string newPassword;
    cout << "Please enter new password: " << endl;
    cin >> newPassword;
    _user->updatePassword(newPassword);
    updateAdminData(_user);
    _tableData->setTableData(_admin->getListOfAccounts());
}

void Controller::reviewListOfInactiveAccounts()
{
    vector<User *> list = _admin->getListOfInactiveAccounts();
    printListOfAccounts(list);
    char stopKey = '1';
    char selection;
    do
    {
        cout << "Do you want to delete any account? " << endl
             << "Please enter 1 to exit" << endl
             << "Enter any key to delete account(s)" << endl;
        cin >> selection;
        switch (selection)
        {
        case '1':
            stopKey = '1';
            break;
        default:
            deleteAccountByUsername();
            break;
        }
    } while (stopKey != '1');
    Utility::deleteVectorPtrs(list);
}

void Controller::deleteCurrentAccount()
{
    _user->updateStatus("inactive");
    updateAdminData(_user);
    _tableData->setTableData(_admin->getListOfAccounts());
}

void Controller::deleteAccountByUsername()
{
    cout << "Please enter username: " << endl;
    string username;
    cin >> username;
    deleteAccountInAdminData(username);
    _tableData->setTableData(_admin->getListOfAccounts());
}

map<string, string> Controller::getCurrentAccountInfo()
{
    return _user->getAccountInfo();
}

void Controller::printAccountInfo(User *user)
{
    map<string, string> accountInfo = user->getAccountInfo();
    cout << accountInfo["ID"] << " " << accountInfo["Password"] << " "
         << accountInfo["Role"] << " " << accountInfo["Status"] << endl;
}

void Controller::printListOfAccounts(const vector<User *> &list)
{
    for (User *user : list)
    {
        printAccountInfo(user);
    }
}

void Controller::printListOfAllAccounts()
{
    printListOfAccounts(_admin->getListOfAccounts());
}

void Controller::printListOfInactiveAccounts()
{
    printListOfAccounts(_admin->getListOfInactiveAccounts());
}

void Controller::setupData(string fileName)
{
    _fileHandler->setDataForFileHandler(fileName);
    _tableData = _fileHandler->getDataFromDatabase();
    _admin->setListOfAccounts(_tableData);
    _admin->setListOfInactiveAccounts();
}

void Controller::updateAdminData(User *user)
{
    _admin->updateAccountInfo(user);
}

void Controller::deleteAccountInAdminData(string username)
{
    _admin->deleteAnAccount(username);
    _admin->setListOfInactiveAccounts();
}

void Controller::updateToDatabase()
{
    _fileHandler->updateDataToDatabase(_tableData);
}

bool Controller::isExistAccount(string username)
{
    bool isExist = false;
    vector<User *> listOfAccounts = _admin->getListOfAccounts();
    for (User *user : listOfAccounts)
    {
        map<string, string> userInfo = user->getAccountInfo();
        if (userInfo["ID"] == username)
        {
            isExist = true;
            break;
        }
    }
    Utility::deleteVectorPtrs(listOfAccounts);
    return isExist;
}

#endif