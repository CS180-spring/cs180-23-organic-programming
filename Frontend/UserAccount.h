#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Backend/Database.h"

using namespace std;

class UserAccount
{
public:
    UserAccount()
    {
        this->username = "";
        this->password = "";
    }

    UserAccount(string username, string password)
    {
        this->username = username;
        this->password = password;
    }

    void setUsername(string user)
    {
        this->username = user;
    }

    void setPassword(string pass)
    {
        this->password = pass;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }

    void insertDatabase(Database db)
    {
        databases.push_back(db);
    }

    vector<Database> getDatabases()
    {
        return databases;
    }

private:
    string username;
    string password;
    vector<Database> databases;
};

#endif
