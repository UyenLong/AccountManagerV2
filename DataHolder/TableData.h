#ifndef TABLEDATA_H
#define TABLEDATA_H

#include "RowData.h"
#include <vector>
#include "../DataType/User.h"

class TableData
{
private:
    vector<RowData> _tableData;

public:
    TableData();
    TableData(vector<RowData>);
    void setTableData(vector<User>);
    vector<RowData> getTableData();
};

#endif