#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../DataType/User.h"
#include "../DataType/Admin.h"
#include "../DataHolder/TableData.h"
#include "../UI/Menu.h"
#include "../FileHandler/FileHandler.h"

class Controller
{
private:
    FileHandler _fileHandler;
    TableData _tableData;
    Admin _admin;
    User _user;

public:
    bool login();
    void createNewAccount();
    void changePassword();
    void deleteCurrentAccount();
    void deleteAccountByUsername();
    void reviewListOfInactiveAccounts(); 
    map<string,string> getCurrentAccountInfo();
    void printAccountInfo(User);
    void printListOfAccounts(vector<User>);
    void printListOfAllAccounts();
    void printListOfInactiveAccounts();
    void setupData(string);
    void setCurrentAccountInfo(Account);
    bool isValidAccount(Account &);
    void updateData(User);
    void updateAdminData(User);
    void deleteAccountInAdminData(string);
    void updateToDatabase();
};

#endif