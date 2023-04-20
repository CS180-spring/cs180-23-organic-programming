#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UserAccount {
    public:
        UserAccount();
        void setUsername(string);
        void setPassword(string);
        string getUsername();
        string getPassword();

        
    protected:
        string username;
        string password;
};

#endif
