#ifndef ROWDATA_CPP
#define ROWDATA_CPP

#include "RowData.h"

void RowData::setRowData(string username,string password, string role, string status)
{
    _rowData.clear();
    _rowData["ID"] = username;
    _rowData["Password"] = password;
    _rowData["Role"] = role;
    _rowData["Status"] = status;   
}

map<string, string> RowData::getRowData()
{
    return _rowData;
}

void RowData::setRowData(User user)
{
    map<string, string> userInfo = user.getAccountInfo();
    _rowData.clear();
    _rowData["ID"] = userInfo["ID"];
    _rowData["Password"] = userInfo["Password"];
    _rowData["Role"] = userInfo["Role"];
    _rowData["Status"] = userInfo["Status"];
}

#endif