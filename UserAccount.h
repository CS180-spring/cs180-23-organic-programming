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

        void addShow(string name, string genre, int rating, int episodes);
        void addMovie(string name, string genre, int rating);
        
        void editShow(string name, int episodes, int rating);
        void editMovie(string name, int rating);
       
        void removeMedia(string name);
        void removeShow(string name);
        void removeMovie(string name);

        void displayAll();
        void displayMovies();
        void displayShows();
        
    protected:
        string username;
        string password;
};

#endif