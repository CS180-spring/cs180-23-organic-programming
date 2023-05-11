#include "gtest/gtest.h"
#include "Frontend/UserAccount.h"
#include "Backend/Database.h"
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

TEST(UserAccountTestDatabase, testSetDatabase) {
    UserAccount newbie;
    Database* db;
    newbie.setDatabase(db);
    EXPECT_EQ(newbie.getDatabase(), db);
}

TEST(DatabaseTestCreateDirectory, testCreateDirectory) {
    Database* db;
    EXPECT_NO_THROW(db->createDirectory());
}
TEST(DatabaseTestDeleteDirectory, testDeleteDirectory) {
    Database* db;
    db->createDirectory();
    EXPECT_NO_THROW(db->deleteDirectory());
}

