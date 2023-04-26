""" CS 180 - Organic Programming """
from UserAccount import *

def main():
    exampleUser = UserAccount("kprada", "password")
    accountList = [exampleUser]
    menu(accountList)

def menu(accountList):
    choice = "P"
    menuChoice = ""
    loggedIn = False

    while not loggedIn:
        userAccountMenu()
        choice = input("Choose an option: ")

        # Login
        if choice == "A":
            account = login(accountList)
            if not account:
                print("Try Again?")
            else:
                loggedIn = True
        # Register
        elif choice == "B":
            registerAccount(accountList)
        # Reset Password
        elif choice == "C":
            print("Resetting password!")
        else:
            exit(0)

    # Now we know they are logged in
    while not menuChoice == "X":
        landingPageMenu()
        menuChoice = input("Choose an option: ")

        # Create Database
        if menuChoice == "A":
            createMenu()
        # Read Database
        elif menuChoice == "B":
            readMenu()
        # Update Database
        elif menuChoice == "C":
            updateMenu()
        # Delete Database
        elif menuChoice == "D":
            deleteMenu()
        elif menuChoice == "E":
            viewMenu()
        else:
            exit(0)


def userAccountMenu():
    print("[A] Login")
    print("[B] Register")
    print("[C] Reset Password")

    print("[X] Quit")
    print()

def registerAccount(accountList):
    print("REGISTER ACCOUNT")
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    user = UserAccount(username, password)
    accountList.append(user)

    print("Account created successfully!")
    print()

def login(accountList):
    print("LOG-IN")
    username = input("Username: ")
    password = input("Password: ")

    for i in range(len(accountList)):
        if accountList[i].username == username and accountList[i].password == password:
            print("Logged in successfully!")
            print()
            return accountList[i]
        else:
            print("Invalid username or password.")
            return False

def landingPageMenu():
    print("What would you like to do with a database?")
    print("[A] Create")
    print("[B] Read")
    print("[C] Update")
    print("[D] Delete")
    print("[E] View")

    print("[X] Exit")

def readMenu():
    databaseFile = input("Database FileName: ")
    print("-= Verifying & Processing Database =-")
    print()
    # Verify database here
    # If verified, print success
    print("Database successfully read")
    print()

def updateMenu():
    databaseFile = input("Database FileName: ")
    print("-= Verifying & Processing Database =-")
    print()
    # Verify database here
    # If verified, print success
    print("Database successfully found")
    print()

    print("Update Options:")
    print("[A] Update")
    print("[B] Delete")
    print("[C] View")

    print("[X] Exit")

def createMenu():
    databaseFile = input("Database FileName: ")
    print("-= Verifying Database =-")
    # Verify database here
    # If verified, print success
    print("Database name available")
    print()

    print("Categories - ")
    print("Enter [X] when done.")

    # Create categories here

    print()
    print("Create Database record?")
    print("[Y] Yes")
    print("[N] No")

def deleteMenu():
    databaseFile = input("Database FileName: ")
    print("-= Verifying & Processing Database =-")
    # Verify database here
    # If verified, print success
    print("Database successfully found")

    print("Are you sure you want to delete", databaseFile, "?")
    print("[Y] Yes")
    print("[N] No")

    userChoice = input("")

    if userChoice == "Y":
        print("Deleting Database.")
        # Delete from vector
        print("Successfully deleted.")
    else:
        print("Okay!")

    print("[A] Main Menu")
    print("[X] Exit")

def viewMenu():
    databaseFile = input("Database FileName: ")
    print("-= Verifying & Processing Database =-")
    # Verify database here
    # If verified, print success
    print("Database successfully found")

    print("View Options:")
    print("[A] Sort")
    print("[B] Filter")
    print("[C] Search")

    print("[X] Exit")

main()