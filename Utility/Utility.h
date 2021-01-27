#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "../DataType/User.h"
#include "../DataHolder/RowData.h"

#define PASSWORD_RULES "(?=.*?[A-Z])(?=.*?[a-z])((?=.*?[0-9])|).{8,}"

class Utility
{
public:
    static void deleteVectorPtrs(vector<RowData *> &);
    static void deleteVectorPtrs(vector<User *> &);
};

#endif