#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../DataHolder/RowData.h"
#include <string>

using namespace std;

class Account
{
protected:
    string _username;
    string _password;
    string _status;
    string _role;

public:
    void setAccountInfo();
    void setAccountInfo(Account);
    void setAccountInfo(RowData);
    void setAccountInfo(map<string, string>);
    void updateStatus(string);
    void updatePassword(string);
    map<string, string> getAccountInfo();
};

#endif