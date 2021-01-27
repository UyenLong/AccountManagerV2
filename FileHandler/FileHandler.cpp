#ifndef FILEHANDLER_CPP
#define FILEHANDLER_CPP

#include "FileHandler.h"
#include <fstream>
#include "../Utility/Utility.h"

FileHandler::FileHandler()
{
    _filePath = " ";
}

void FileHandler::setDataForFileHandler(string filePath)
{
    _filePath = filePath;
}

TableData *FileHandler::getDataFromDatabase()
{
    ifstream file{_filePath};
    string lineData;
    vector<RowData *> data;
    while (!file.eof())
    {
        string id, password, role, status;
        file >> id >> password >> role >> status;
        RowData *rowData;
        rowData->setRowData(id, password, role, status);
        data.push_back(rowData);
        delete(rowData);
    }
    file.close();
    TableData *tableData = new TableData(data);
    Utility::deleteVectorPtrs(data);
    return tableData;
}

void FileHandler::updateDataToDatabase(TableData *tableData)
{
    vector<RowData *> dataFromTableData = tableData->getTableData();
    ofstream file{_filePath};
    file.clear();
    for (RowData *rowData:dataFromTableData)
    {
        map<string, string> dataOfRow = rowData->getRowData();
        file << dataOfRow["ID"] << " " << dataOfRow["Password"] << " " << dataOfRow["Role"] << " " << dataOfRow["Status"] << "\n";
    }
    file.close();
    Utility::deleteVectorPtrs(dataFromTableData);
}

#endif