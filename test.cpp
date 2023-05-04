#include "gtest/gtest.h"
#include "UserAccount.h"
#include <vector> 

using namespace std; 

TEST(UserAccountTestUser, testSetUser) {
    UserAccount newbie;
    string name = "Paul";
    newbie.setUsername(name);
    EXPECT_EQ(newbie.getUsername(), name);
}

TEST(UserAccountTestPass, testSetPass) {
    UserAccount newbie;
    string pass = "pass";
    newbie.setPassword(pass);
    EXPECT_EQ(newbie.getPassword(), pass);
}
