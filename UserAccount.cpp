#include "UserAccount.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

UserAccount::UserAccount()
{
    username = "";
    password = "";
}

void UserAccount::setUsername(string user)
{
    this->username = user;
}

void UserAccount::setPassword(string pass)
{
    this->password = pass;
}

string UserAccount::getUsername()
{
    return username;
}

string UserAccount::getPassword()
{
    return password;
}
