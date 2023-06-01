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
    vector<Database> databases;
    Database db;
    EXPECT_NO_THROW(newbie.insertDatabase(db));
} 
TEST(DatabaseTestCreateDirectory, testCreateDirectory) {
    Database* db;
    EXPECT_NO_THROW(db->createDirectory());
}
TEST(FileTestCreateFile, testCreateFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.createFile(db));
}
TEST(FileTestReadFile, testReadFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.readFile(db));
}
TEST(FileTestSearchFile, testSearchFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.searchFile(db));
}
TEST(FileTestUpdateFile, testUpdateFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.updateFile(db)); 
}
TEST(FileTestDeleteFile, testDeleteFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.deleteFile(db)); 
}
TEST(FileTestConvertFile, testConvertFile) {
    Document doc;
    File(testFile);
    Database db;
    EXPECT_NO_THROW(testFile.convertFile(db));
}

/*TEST(DatabaseTestDeleteDirectory, testDeleteDirectory) {
    Database* db;
    db->createDirectory();
    EXPECT_NO_THROW(db->deleteDirectory());
} */

/* TEST(UserAccountTestDatabase, testinsertDatabase) {
    UserAccount newbie;
    vector<Database> databases;
    Database db;
    newbie.insertDatabase(db);
    EXPECT_EQ(newbie.getDatabases(),db);
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
