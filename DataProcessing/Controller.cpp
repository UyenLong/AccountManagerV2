#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP

#include "Controller.h"
#include <regex>
#include "../Constants/Constants.h"
#include <iostream>
#include <string>

using namespace std;

bool isPasswordInCorrectForm(string password)
{
    return regex_match(password, regex(PASSWORD_RULES));
}

bool Controller::isValidAccount(Account &account)
{
    bool isValid = false;
    vector<RowData> tableData = _tableData.getTableData();
    map<string, string> accountInfo = account.getAccountInfo();
    for (RowData rowData : tableData)
    {
        map<string, string> dataOfRow = rowData.getRowData();
        if (dataOfRow["ID"] == accountInfo["ID"])
        {
            accountInfo["Role"] = dataOfRow["Role"];
            accountInfo["Status"] = dataOfRow["Role"];
            isValid = true;
            break;
        }
    }
}

bool Controller::login()
{
    Account account;
    account.setAccountInfo();
    bool isAccountValid = isValidAccount(account);
    if (isAccountValid)
    {
        cout << "Login successfully!" << endl;
        setCurrentAccountInfo(account);
    }
    else
        cout << "Login fail!" << endl;
    return isAccountValid;
}

void Controller::setCurrentAccountInfo(Account account)
{
    map<string, string> accountInfo = account.getAccountInfo();
    if (accountInfo["Role"] == "admin")
    {
        _admin.setAccountInfo(account);
    }
    else
        _user.setAccountInfo(account);
}

void Controller::createNewAccount()
{
    User account;
    account.setAccountInfo();
    _admin.addNewAccount(account);
    updateData(account);
}

void Controller::changePassword()
{
    string newPassword;
    cout << "Please enter new password: " << endl;
    cin >> newPassword;
    _user.updatePassword(newPassword);
    updateAdminData(_user);
    _tableData.setTableData(_admin.getListOfAccounts());
}

void Controller::reviewListOfInactiveAccounts()
{
    vector<User> list = _admin.getListOfInactiveAccounts();
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
            cout << "Please enter ID you want to delete: " << endl;
            string username;
            cin >> username;
            deleteAccountByUsername();
            break;
        }
    } while (stopKey != '1');
}

void Controller::deleteCurrentAccount()
{
    _user.updateStatus("inactive");
    updateData(_user);
}

void Controller::deleteAccountByUsername()
{
    cout << "Please enter username: " << endl;
    string username;
    cin >> username;
    deleteAccountInAdminData(username);
    _tableData.setTableData(_admin.getListOfAccounts());
}

map<string, string> Controller::getCurrentAccountInfo()
{
    return _user.getAccountInfo();
}

void Controller::printAccountInfo(User user)
{
    map<string, string> accountInfo = user.getAccountInfo();
    cout << accountInfo["ID"] << " " << accountInfo["Password"] << " "
         << accountInfo["Role"] << " " << accountInfo["Status"] << endl;
}

void Controller::printListOfAccounts(vector<User> list)
{
    for (User user : list)
    {
        printAccountInfo(user);
    }
}

void Controller::printListOfAllAccounts()
{
    printListOfAccounts(_admin.getListOfAccounts());
}

void Controller::printListOfInactiveAccounts()
{
    printListOfAccounts(_admin.getListOfInactiveAccounts());
}

void Controller::setupData(string fileName)
{
    _fileHandler.setDataForFileHandler(fileName);
    _tableData = _fileHandler.getDataFromDatabase();
}

void Controller::updateData(User user)
{
    updateAdminData(user);
    _tableData.setTableData(_admin.getListOfAccounts());
}

void Controller::updateAdminData(User user)
{
    _admin.setAccountInfo(user.getAccountInfo());
}

void Controller::deleteAccountInAdminData(string username)
{
    _admin.deleteAnAccount(username);
    _admin.setListOfInactiveAccounts();
}

void Controller::updateToDatabase()
{
    _fileHandler.updateDataToDatabase(_tableData);
}

#endif