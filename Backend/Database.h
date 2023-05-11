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

using namespace std;
using namespace rapidjson;
namespace fs = std::filesystem;

class Database
{
private:
    string name;

public:
    Database()
    {
        this->name = "";
    }
    
    Database(string name)
    {
        this->name = name;
    }

    void createDirectory()
    {
        string databaseName = name;
        databaseName.insert(0, "../");
        fs::path dbDirectory = databaseName.c_str();
        fs::create_directory(dbDirectory);

        if (fs::exists(dbDirectory))
        {
            cout << "Directory created successfully\n";
        }
        // Create the example sub directories
        fs::create_directory(dbDirectory / "Collection1");
        fs::create_directory(dbDirectory / "Collection2");
        fs::create_directory(dbDirectory / "Collection3");
        
        fs::current_path(dbDirectory);
        cout << "The Current Path = " << fs::current_path() << endl;
    }

    void deleteDirectory()
    {
        string databaseName = name;
        databaseName.insert(0, "../");
        fs::path dbDirectory = databaseName.c_str();
        fs::remove_all(dbDirectory);

        // Check if the directory exists
        if (!fs::exists(dbDirectory))
        {
            cout << "Directory deleted successfully\n";
        }
    }
};
#endif