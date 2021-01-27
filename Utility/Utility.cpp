#ifndef UTILITY_CPP
#define UTILITY_CPP

#include "Utility.h"

void Utility::deleteVectorPtrs(vector<RowData *> &data)
{
    for (RowData *rowData : data)
    {
        delete(rowData);
    }
    data.resize(0);
}

void Utility::deleteVectorPtrs(vector<User *> &data)
{
    for (User *user : data)
    {
        delete(user);
    }
    data.resize(0);
}

#endif