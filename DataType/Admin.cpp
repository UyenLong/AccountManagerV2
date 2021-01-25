#ifndef ADMIN_CPP
#define ADMIN_CPP

#include "Admin.h"

Admin::Admin()
{
    _allAccounts.resize(0);
    _inactiveAccounts.resize(0);
}

void Admin::setListOfAccounts(TableData tableData)
{
    _allAccounts.clear();
    vector<RowData> data = tableData.getTableData();
    for (RowData rowData : data)
    {
        User user;
        user.setAccountInfo(rowData);
        map<string, string> userData = user.getAccountInfo();
        _allAccounts.push_back(user);
    }
}

void Admin::setListOfInactiveAccounts()
{
    _inactiveAccounts.clear();
    for (User user : _allAccounts)
    {
        map<string, string> userData = user.getAccountInfo();
        if (userData["Status"] == "inactive")
        {
            _inactiveAccounts.push_back(user);
        }
    }
}

vector<User> Admin::getListOfAccounts()
{
    return _allAccounts;
}

vector<User> Admin::getListOfInactiveAccounts()
{
    return _inactiveAccounts;
}

void Admin::deleteAnAccount(string username)
{
    int index = 0;
    for (User user : _allAccounts)
    {
        map<string, string> userData = user.getAccountInfo();
        if (userData["ID"] == username)
        {
            _allAccounts.erase(_allAccounts.begin() + index);
            if (userData["Status"] == "inactive")
            {
                setListOfInactiveAccounts();
            }
            break;
        }
        index++;
    }
}

void Admin::addNewAccount(User user)
{
    _allAccounts.push_back(user);
}

void Admin::updateAccountInfo(User user)
{
    map<string, string> userInfo = user.getAccountInfo();
    deleteAnAccount(userInfo["ID"]);
    addNewAccount(user);
    setListOfInactiveAccounts();
}

#endif