#include "gtest/gtest.h"
#include "Frontend/UserAccount.h"
#include "Backend/Database.h"
#include "Backend/Collection.h"
#include "Backend/File.h"
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

TEST(UserAccountTestDatabase, testinsertDatabase) {
    UserAccount newbie;
    Database(db);
    string name = "testdb";
    newbie.insertDatabase(db);
    EXPECT_NO_THROW(newbie.getDatabases());
} 

TEST(DatabaseTestCreateDirectory, testCreateDirectory) {
    Database* db;
    EXPECT_NO_THROW(db->createDirectory());
}
TEST(FileTestCreateFile, testCreateFile) {
    Document doc;
    File(testFile);
    EXPECT_NO_THROW(testFile.createFile());
}
TEST(FileTestReadFile, testReadFile) {
    Document doc;
    File(testFile);
    EXPECT_NO_THROW(testFile.readFile());
}
TEST(FileTestSearchFile, testSearchFile) {
    Document doc;
    File(testFile);
    EXPECT_NO_THROW(testFile.searchFile());
}
TEST(FileTestUpdateFile, testUpdateFile) {
    Document doc;
    File(testFile);
    EXPECT_NO_THROW(testFile.updateFile()); 
}
TEST(FileTestDeleteFile, testDeleteFile) {
    Document doc;
    File(testFile);
    EXPECT_NO_THROW(testFile.deleteFile()); 
}


/* TEST(DatabaseTestDeleteDirectory, testDeleteDirectory) {
    Database* db;
    db->createDirectory();
    EXPECT_NO_THROW(db->deleteDirectory());
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
