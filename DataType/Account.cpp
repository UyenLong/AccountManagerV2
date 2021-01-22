#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP

#include "Account.h"

void Account::setAccountInfo(RowData rowData)
{
    map<string, string> data = rowData.getRowData();
    setAccountInfo(data);
}

void Account::setAccountInfo(string username, string password)
{
    _username = username;
    _password = password;
}

void Account::setAccountInfo(map<string,string> data)
{
    _username = data["ID"];
    _password = data["Password"];
    _status = data["Status"];
    _role = data["Role"];
}

#endif