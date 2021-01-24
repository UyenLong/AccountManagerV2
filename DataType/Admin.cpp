#ifndef ADMIN_CPP
#define ADMIN_CPP

#include "Admin.h"

void Admin::setListOfAccounts(TableData tableData)
{
    vector<RowData> data = tableData.getTableData();
    for (RowData rowData : data)
    {
        User user;
        user.setAccountInfo(rowData);
        map<string, string> userData = user.getAccountInfo();
        if (userData["Role"] == "user")
        {
            _allAccounts.push_back(user);
        }
    }
}

void Admin::setListOfInactiveAccounts()
{
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
    for (User user:_allAccounts)
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

#endif