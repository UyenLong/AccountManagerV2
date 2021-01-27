#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "../DataHolder/TableData.h"

using namespace std;

class FileHandler
{
private:
    string _filePath;

public:
    FileHandler();
    void setDataForFileHandler(string);
    TableData *getDataFromDatabase();
    void updateDataToDatabase(TableData *);
};

#endif