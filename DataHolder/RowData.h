#ifndef ROWDATA_H
#define ROWDATA_H

#include <string>
#include <map>

using namespace std;

class RowData
{
protected:
    map<string, string> _rowData;

public:
    void setRowData(string, string, string, string);
    void setRowData(map<string, string>);
    map<string, string> getRowData();
};

#endif