#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "UserAccount.h"
#include "filters.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"

using namespace std;

void registerAccount(vector<UserAccount> &accountList)
{
    string user;
    string pass;
    cout << "Enter a username: ";
    getline(cin, user);
    cout << "Enter a password: ";
    getline(cin, pass);
    UserAccount account(user, pass);
    accountList.push_back(account);
    cout << "Account created successfully!" << endl;
}

bool login(vector<UserAccount> &accountList, string username, string password)
{
    for (int i = 0; i < accountList.size(); i++)
    {
        if (accountList.at(i).getUsername() == username && accountList.at(i).getPassword() == password)
        {
            cout << "Logged in successfully!" << endl;
            return true;
        }
    }
    cout << "Invalid username or password." << endl;
    return false;
}

void changePassword(vector<UserAccount> &accountList)
{
    string username;
    string password;
    cout << "Enter your username: ";
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, password);
    for (int i = 0; i < accountList.size(); i++)
    {
        if (accountList.at(i).getUsername() == username && accountList.at(i).getPassword() == password)
        {
            cout << "Enter new password: ";
            getline(cin, password);
            accountList.at(i).setPassword(password);
            cout << "Password has been reset." << endl;
            return;
        }
    }
    cout << "Invalid username or password." << endl;
}

void printMainMenu(vector<UserAccount> &accountList)
{
    char choice = 'p';
    char menuChoice;
    while (choice != 'q')
    {
        cout << endl << "MENU" << endl
             << "a - Register account" << endl
             << "b - Login to account" << endl
             << "c - Reset Password" << endl
             << "d - Output JSON File" << endl
             << "e - return object's Keys" << endl
             << "q - Quit" << endl
             << endl
             << "Choose an option: " << endl;
        cin >> choice;
        cin.ignore();
        if (choice == 'a')
        {
            registerAccount(accountList);
        }
        else if (choice == 'b')
        {
            string username;
            string password;
            UserAccount account;
            cout << "Enter your username: ";
            getline(cin, username);
            cout << "Enter your password: ";
            getline(cin, password);
            if (login(accountList, username, password))
            {
                for (int i = 0; i < accountList.size(); i++)
                {
                    if (accountList.at(i).getUsername() == username && accountList.at(i).getPassword() == password)
                    {
                        account = accountList.at(i);
                    }
                }

                while (menuChoice != 'g')
                {
                    cout << endl;
                    cout << "What would you like to do? " << endl;
                    cout << "a. Create your database" << endl;
                    cout << "b. Delete your database" << endl;
                    cout << "c. return json keys " << endl;
                    cout << "d. " << endl;
                    cout << "e. " << endl;
                    cout << "f. " << endl;
                    cout << "g. Quit" << endl;
                    cin >> menuChoice;
                    cin.ignore();

                    if (menuChoice == 'a')
                    {
                        string dbName = account.getUsername().append("'s database");
                        Database db(dbName);
                        db.createDirectory();
                        Database* p = &db;
                        account.setDatabase(p);
                    }
                    else if (menuChoice == 'b')
                    {
                        account.getDatabase()->deleteDirectory();
                        account.setDatabase(nullptr);
                    }

                    else if (menuChoice == 'c')
                    {
                  
                    }
                    else if (menuChoice == 'd')
                    {
                    }

                    else if (menuChoice == 'e')
                    {
                    }
                    else if (menuChoice == 'f')
                    {
                    }
                }
            }
        }
        else if (choice == 'c')
        {
            changePassword(accountList);
        }

        else if (choice == 'd'){
            cout << "Please enter the JSON file name: ";
            string filename;
            cin >> filename;
            Filters filters;
            cout << "Below are the contents of " << filename << endl;
            std::vector<std::string> keys = filters.getKeysFromFirstObject(filename);
            for (const auto& key : keys) {
                std::cout << key << std::endl;
                }
         }

        else if (choice == 'e'){
            cout << "Please enter the JSON file name: ";
            string filename;
            cin >> filename;
            cout << endl << "Below are the key names for your JSON objects:" << endl << endl;
            // Load JSON from file
            std::ifstream ifs(filename);
            std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

            // Parse JSON
            Document doc;
            doc.Parse(json.c_str());

            // Extract keys of first data set
            const Value& manga = doc[0];
            for (Value::ConstMemberIterator it = manga.MemberBegin(); it != manga.MemberEnd(); ++it) {
            int i = 1;
            std::cout <<". " << it->name.GetString() << std::endl;
            i++;
        }
    }
}
}

int main()
{
    vector<UserAccount> accountList;
    printMainMenu(accountList);

    return 0;
}
