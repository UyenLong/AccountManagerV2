#ifndef ROWDATA_CPP
#define ROWDATA_CPP

#include "RowData.h"

void RowData::setRowData(map<string, string> rowData)
{
    _rowData.clear();
    _rowData = rowData;
}

map<string, string> RowData::getRowData()
{
    return _rowData;
}

#endif