// CS 180 - Organic Programming //
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "UserAccount.h"
#include "../Backend/File.h"

using namespace std;

void userAccountMenu()
{
    cout << "[A] Login" << endl;
    cout << "[B] Register" << endl;
    cout << "[C] Reset Password" << endl;

    cout << "[X] Quit" << endl;
    cout << "" << endl;
}

void registerAccount(vector<UserAccount> &accountList)
{
    string user;
    string pass;
    UserAccount account;
    cout << "Enter a username: ";
    getline(cin, user);
    cout << "Enter a password: ";
    getline(cin, pass);
    account.setUsername(user);
    account.setPassword(pass);
    accountList.push_back(account);
    cout << "Account created successfully!" << endl;
    cout << endl;
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
            cout << endl;
            return;
        }
    }
    cout << "Invalid username or password." << endl;
    cout << endl;
}

bool login(vector<UserAccount> &accountList, string username, string password)
{
    for (int i = 0; i < accountList.size(); i++)
    {
        if (accountList.at(i).getUsername() == username && accountList.at(i).getPassword() == password)
        {
            cout << "Logged in successfully!" << endl;
            cout << endl;
            return true;
        }
    }
    cout << "Invalid username or password." << endl;
    cout << endl;
    return false;
}

void landingPageMenu()
{
    cout << "What would you like to do with a database?" << endl;
    cout << "[A] Create" << endl;
    cout << "[B] Update" << endl;
    cout << "[C] Delete" << endl;
    cout << "[D] View" << endl;

    cout << "[X] Quit" << endl;
    cout << "" << endl;
}

// void readMenu(UserAccount &account, File &file)
// {
//     string databaseFile;
//     cout << "Database FileName: ";
//     getline(cin, databaseFile);

//     vector<Database> dbs = account.getDatabases();
//     for (auto i = dbs.begin(); i != dbs.end(); i++)
//     {
//         Database &db = *i;
//         if (db.getName() == databaseFile)
//         {
//             // If verified, print success
//             cout << "Database successfully found." << endl;
//             cout << endl;
//             file.readFile();
//             // If verified, print success
//             cout << "Database successfully read." << endl;
//             cout << endl;
//             break;
//         }
//     }
// }

void updateMenu(UserAccount &account, File &file)
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    vector<Database> dbs = account.getDatabases();
    for (auto i = dbs.begin(); i != dbs.end(); i++)
    {
        Database &db = *i;
        if (db.getName() == databaseFile)
        {
            // If verified, print success
            cout << "Database successfully found." << endl;
            cout << endl;

            bool backendTest = true;
            int choice;
            string input;

            while (backendTest)
            {
                cout << "\nSelect File Operation\n"
                        "----------------------\n"
                        "1. Create\n"
                        "2. Update\n"
                        "3. Delete\n"
                        "4. Convert"
                     << std::endl;

                cout << "\nEnter Choice of Operation (or -1 to Prompt Quit): ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    file.createFile(db);
                    break;
                case 2:
                    file.updateFile();
                    break;
                case 3:
                    file.deleteFile();
                    break;
                case 4:
                    file.convertFile();
                    break;
                default:
                    cout << "Continue Operations? (Y or N): ";
                    cin >> input;
                    if (input == "N" || input == "n")
                        backendTest = false;
                    else
                    {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        backendTest = true;
                    }
                }
            }
            break;
        }
    }
}

void createMenu(UserAccount &account)
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying Database=-" << endl;
    cout << endl;

    fs::path dbDirectory = databaseFile.c_str();
    if (fs::exists(dbDirectory))
    {
        cout << "Directory already exists\n";
    }
    else
    {

        // If verified, print success
        cout << "Database name available." << endl;
        cout << endl;

        cout << "Create Database record?" << endl;
        cout << "[Y] Yes" << endl;
        cout << "[N] No" << endl;

        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'Y')
        {
            Database db(databaseFile);
            account.insertDatabase(db);
            db.createDirectory();
        }
    }
}

void deleteMenu(UserAccount &account)
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;
    vector<Database> dbs = account.getDatabases();
    for (auto i = dbs.begin(); i != dbs.end(); i++)
    {
        Database &db = *i;
        if (db.getName() == databaseFile)
        {
            // If verified, print success
            cout << "Database successfully found." << endl;
            cout << endl;

            cout << "Are you sure you want to delete " << databaseFile << "?" << endl;
            cout << "[Y] Yes" << endl;
            cout << "[N] No" << endl;

            char userChoice;
            cin >> userChoice;
            cin.ignore();

            if (userChoice == 'Y')
            {
                cout << "Deleting database." << endl;
                db.deleteDirectory();
                account.getDatabases().erase(i);
            }
            else
            {
                break;
            }
        }
    }
}

void viewMenu(UserAccount &account, File &file)
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    vector<Database> dbs = account.getDatabases(); 
    for (auto i = dbs.begin(); i != dbs.end(); i++)
    {
        Database &db = *i;
        if (db.getName() == databaseFile)
        {
            // If verified, print success
            cout << "Database successfully found." << endl;
            cout << endl;

            cout << "View Options:" << endl;
            cout << "[A] Search" << endl;
            cout << "[B] Filter" << endl;

            cout << "[X] Quit" << endl;

            char userChoice;
            cin >> userChoice;
            cin.ignore();

            if (userChoice == 'A')
            {
                file.searchFile();
            }
            else if (userChoice == 'B')
            {
                // implement filter
            }
            else
            {
                break;
            }
        }
    }
}

void menu(vector<UserAccount> &accountList)
{
    char choice = 'p';
    char menuChoice;
    bool loggedIn = false;
    UserAccount account;
    while (!loggedIn)
    {
        userAccountMenu();
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        // LOG-IN

        if (choice == 'A')
        {
            // Log-in

            string username;
            string password;
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
                        loggedIn = true;
                    }
                }
            }
        }

        else if (choice == 'B')
        {
            registerAccount(accountList);
        }
        else if (choice == 'C')
        {
            changePassword(accountList);
        }

        else
        {
            exit(0);
        }
    }

    // If they were able to log-in successfully,
    // they would have broken the while loop
    File file;
    while (menuChoice != 'X')
    {
        landingPageMenu();
        cout << "Choose an option: " << endl;
        cin >> menuChoice;
        cin.ignore();

        // Database Menu
        if (menuChoice == 'A')
        {
            createMenu(account);
        }
        else if (menuChoice == 'B')
        {
            updateMenu(account, file);
        }
        else if (menuChoice == 'C')
        {
            deleteMenu(account);
        }
        else if (menuChoice == 'D')
        {
            viewMenu(account, file);
        }
        else
        {
            exit(0);
        }
    }
}
