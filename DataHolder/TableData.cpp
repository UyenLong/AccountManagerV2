#ifndef TABLEDATA_CPP
#define TABLEDATA_CPP

#include "TableData.h"
#include "../Utility/Utility.h"

TableData::TableData()
{
    _tableData.resize(0);
}

TableData::~TableData()
{
    Utility::deleteVectorPtrs(_tableData);
}

TableData::TableData(vector<RowData *> tableData)
{
    _tableData.resize(0);
    _tableData = tableData;
}

vector<RowData *> TableData::getTableData()
{
    return _tableData;
}

void TableData::setTableData(vector<User *> data)
{
    _tableData.resize(0);
    for (User *user:data)
    {
        RowData *rowData;
        rowData->setRowData(user->getAccountInfo());
        _tableData.push_back(rowData);
        delete(rowData);
    }
}

#endif