// CS 180 - Organic Programming // 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "UserAccount.h"

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
    cout << "[B] Read" << endl;
    cout << "[C] Update" << endl;
    cout << "[D] Delete" << endl;
    cout << "[E] View" << endl;
    
    cout << "[X] Quit" << endl;
    cout << "" << endl;
}

void readMenu()
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    // Verify database here

    // If verified, print success
    cout << "Database successfully read." << endl;
    cout << endl;
}

void updateMenu()
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    // Verify database here

    // If verified, print success
    cout << "Database successfully found." << endl;
    cout << endl;

    cout << "Update Options:" << endl;
    cout << "[A] Update" << endl;
    cout << "[B] Delete" << endl;
    cout << "[C] View" << endl;
    
    cout << "[X] Quit" << endl;
}

void createMenu()
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying Database=-" << endl;
    cout << endl;

    // Verify database here

    // If verified, print success
    cout << "Database name available." << endl;
    cout << endl;

    cout << "Categories - " << endl;
    cout << "Enter [X] when done." << endl;

    cout << "Create Database record?" << endl;
    cout << "[Y] Yes" << endl;
    cout << "[N] No" << endl;
    
    cout << "[X] Quit" << endl;
}

void deleteMenu()
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    // Verify database here

    // If verified, print success
    cout << "Database successfully found." << endl;
    cout << endl;

    cout << "Are you sure you want to delete" << databaseFile << "?" << endl;
    cout << "[Y] Yes" << endl;
    cout << "[N] No" << endl;

    char userChoice;
    cin >> userChoice;

    if (userChoice == 'Y')
    {
        cout << "Deleting database." << endl;
        // Delete
        cout << "Successfully deleted." << endl;
    }
    else
    {
        cout << "No longer deleting!" << endl;
    }
    
    cout << "[A] Main Menu" << endl;
    cout << "[X] Quit" << endl;
}

void viewMenu()
{
    string databaseFile;
    cout << "Database FileName: ";
    getline(cin, databaseFile);

    cout << "-= Verifying & Processing Database =-" << endl;
    cout << endl;

    // Verify database here

    // If verified, print success
    cout << "Database successfully found." << endl;
    cout << endl;

    cout << "View Options:" << endl;
    cout << "[A] Sort" << endl;
    cout << "[B] Filter" << endl;
    cout << "[C] Search" << endl;

    cout << "[X] Quit" << endl;
}

void menu(vector<UserAccount> &accountList)
{
    char choice = 'p';
    char menuChoice;
    bool loggedIn = false;

    while (!loggedIn)
    {
        userAccountMenu();
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        // LOG-IN
        
        if(choice == 'A')
        {
            // Log-in
            UserAccount account;
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

        else if(choice == 'B')
        {
            registerAccount(accountList);
        }
        else if(choice == 'C')
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

    while(menuChoice != 'X')
    {
        landingPageMenu();
        cout << "Choose an option: " << endl;
        cin >> menuChoice;

        // Database Menu
        if(menuChoice == 'A')
        {
            createMenu();
        }
        else if(menuChoice == 'B')
        {
            readMenu();
        }
        else if(menuChoice == 'C')
        {
            updateMenu();
        }
        else if(menuChoice == 'D')
        {
            deleteMenu();
        }
        else if(menuChoice == 'E')
        {
            viewMenu();
        }
        else
        {
            exit(0);
        }
    }
    


}

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
}