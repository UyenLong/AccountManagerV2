#ifndef ADMIN_H
#define ADMIN_H

#include "../DataHolder/TableData.h"
#include "Account.h"
#include "User.h"
#include <vector>

class Admin : public Account
{
private:
    vector<User> _allAccounts;
    vector<User> _inactiveAccounts;

public:
    void setListOfAccounts(TableData);
    void setListOfInactiveAccounts();
    vector<User> getListOfAccounts();
    vector<User> getListOfInactiveAccounts();
    void deleteAnAccount(string);
    void addNewAccount(Account);
};

#endif