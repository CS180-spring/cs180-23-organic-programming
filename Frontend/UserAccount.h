#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include "Backend/Database.h"

using namespace std;

class UserAccount
{
public:
    UserAccount()
    {
        this->username = "";
        this->password = "";
        this->db = nullptr;
    }

    UserAccount(string username, string password)
    {
        this->username = username;
        this->password = password;
        this->db = nullptr;
    }

    void setDatabase(Database* db)
    {
        if (db != nullptr) {
            this->db = db;
        } else {
            // handle null pointer
        }
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

    Database* getDatabase()
    {
        return db;
    }

private:
    string username;
    string password;
    Database* db;
};

#endif
