#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "UserAccount.h"
#include "menu.h"

using namespace std;

int main()
{

    // Account List
    vector<UserAccount> accountList;
    // Test User
    UserAccount testUser;
    testUser.setUsername("organic");
    testUser.setPassword("password");
    accountList.push_back(testUser);

    // Menu
    menu(accountList);

    return 0;
}
