#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP

#include "Account.h"
#include <iostream>

using namespace std;

void Account::setAccountInfo()
{
    cout << "Enter username: " << endl;
    cin >> _username;
    cout << "Enter password: " << endl;
    cin >> _password;
    _role = "user";
    _status = "active";
}

void Account::setAccountInfo(Account account)
{
    map<string, string> accountInfo = account.getAccountInfo();
    _username = accountInfo["ID"];
    _password = accountInfo["Password"];
    _status = accountInfo["Status"];
    _role = accountInfo["Role"];
}

void Account::setAccountInfo(RowData rowData)
{
    map<string, string> data = rowData.getRowData();
    setAccountInfo(data);
}

void Account::setAccountInfo(map<string, string> data)
{
    _username = data["ID"];
    _password = data["Password"];
    _status = data["Status"];
    _role = data["Role"];
}

void Account::updateStatus(string status)
{
    _status = status;
}

void Account::updatePassword(string password)
{
    _password = password;
}

map<string, string> Account::getAccountInfo()
{
    map<string, string> accountInfo;
    accountInfo["ID"] = _username;
    accountInfo["Password"] = _password;
    accountInfo["Status"] = _status;
    accountInfo["Role"] = _role;
    return accountInfo;
}

#endif