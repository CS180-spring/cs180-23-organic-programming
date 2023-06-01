#ifndef DATABASE_H
#define DATABASE_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <filesystem>
#include "Collection.h"

using namespace std;
using namespace rapidjson;
namespace fs = std::filesystem;

class Database
{
private:
    string name;
    vector<Collection> collections;

public:
    Database()
    {
        this->name = "";
    }
    
    Database(string name)
    {
        this->name = name;
    }

    string getName()
    {
        return name;
    }

    void insertCollection(Collection collection)
    {
        collections.push_back(collection);
    }

    void createDirectory()
    {
        fs::path tmp = fs::current_path();
        fs::create_directories(tmp / name);

        if(fs::exists(tmp / name))
        {
            cout << "Directory created successfully\n";
        }
    }


    void deleteDirectory()
    {
        fs::path tmp = fs::current_path();
        uintmax_t n = fs::remove_all(tmp / name);
        if (!fs::exists(tmp))
        {
            cout << "Directory deleted successfully\n";
        }
        cout << "Deleted " << n << " files or directories\n";
    }
};
#endif