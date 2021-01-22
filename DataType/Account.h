#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "RowData.h"

class Account
{
protected:
    RowData _rowData;
    string _username;
    string _password;
    string _status;
    string _role;

public:
    void setAccountInfo(RowData);
    void setAccountInfo(string, string);
    void setAccountInfo(map<string, string>);
};

#endif