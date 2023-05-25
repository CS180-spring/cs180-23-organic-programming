#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Database.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

class Filters
{
public:
/*
void outputFirstDataSet(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    if (doc.HasParseError()) {
        std::cerr << "Failed to parse JSON file: " << filename << std::endl;
        return;
    }

    if (!doc.IsArray() || doc.Empty()) {
        std::cerr << "JSON file does not contain an array or the array is empty" << std::endl;
        return;
    }

    const rapidjson::Value& firstDataSet = doc[0];
    // Output the first data set as a string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    firstDataSet.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
}*/

void checkValueIsObject(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();

    rapidjson::Document document;
    document.Parse(json.c_str());

    int index;
    std::string key;
    std::cout << "Enter the index of the object: ";
    std::cin >> index;
    std::cout << "\nEnter the key: ";
    std::cin >> key;

    if (document.IsArray() && index >= 0 && index < document.Size()) {
        if (document[index].HasMember(key.c_str())) {
            if (document[index][key.c_str()].IsObject()) {
                rapidjson::StringBuffer strbuf;
                rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
                document[index][key.c_str()].Accept(writer);

                std::cout << "\nThe value is an object: ";
                std::cout << strbuf.GetString() << std::endl;
            } else {
                std::cout << "\nThe value is not an object." << std::endl;
            }
        } else {
            std::cout << "\nKey not found." << std::endl;
        }
    } else {
        std::cout << "\nIndex out of range." << std::endl;
    }
}


void pathQueryObject(const std::string& filename){
    std::ifstream file("mangaCollection.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();

    rapidjson::Document document;
    document.Parse(json.c_str());

    int index;
    std::cout << "Enter the index of the object: ";
    std::cin >> index;

    if (document.IsArray() && index >= 0 && index < document.Size()) {              // compare index to size of array
        rapidjson::StringBuffer strbuf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);            
        document[index].Accept(writer);

        std::cout << "\nThe object is: ";
        std::cout << strbuf.GetString() << std::endl;
    } else {
        std::cout << "\nIndex out of range." << std::endl;
    }
}
void pathQueryValue(const std::string& filename){
        std::ifstream file("mangaCollection.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();

    rapidjson::Document document;
    document.Parse(json.c_str());

    int index;
    std::string key;
    std::cout << "Enter the index of the object: ";
    std::cin >> index;
    std::cout << "\nEnter the key: ";
    std::cin >> key;

    if (document.IsArray() && index >= 0 && index < document.Size()) {
        if (document[index].HasMember(key.c_str())) {
            std::cout << "\nThe value is: ";
            std::cout << document[index][key.c_str()].GetString() << std::endl;
        } else {
            std::cout << "\nKey not found." << std::endl;
        }
    } else {
        std::cout << "\nIndex out of range." << std::endl;
    }
}
void outputJSON(const std::string& filename){
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        rapidjson::Document doc;
        doc.Parse(jsonStr.c_str());
        cout << jsonStr;
}
}
std::vector<std::string> getKeysFromFirstObject(const std::string& filename) {
    std::vector<std::string> keys;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        rapidjson::Document doc;
        doc.Parse(jsonStr.c_str());

        if (doc.IsArray() && !doc.Empty() && doc[0].IsObject()) {
            for (auto it = doc[0].MemberBegin(); it != doc[0].MemberEnd(); ++it) {
                keys.push_back(it->name.GetString());
            }
        }
    }
      else if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    return keys;
}

void searchObject(string filename){
        // Open the input stream and parse the JSON
    std::ifstream input(filename);
    IStreamWrapper isw(input);
    Document document;
    document.ParseStream(isw);

    // Prompt the user to enter values for each key
    std::string manga_name, volume_number, mangaka_name, publisher_name, print_edition, extra_comments;
    std::cout << "Enter manga name: ";
    std::getline(std::cin, manga_name);
    std::cout << "Enter volume number: ";
    std::getline(std::cin, volume_number);
    std::cout << "Enter mangaka name: ";
    std::getline(std::cin, mangaka_name);
    std::cout << "Enter publisher name: ";
    std::getline(std::cin, publisher_name);
    std::cout << "Enter print edition: ";
    std::getline(std::cin, print_edition);
    std::cout << "Enter extra comments: ";
    std::getline(std::cin, extra_comments);

    // Iterate over the objects in the array
    for (Value::ConstValueIterator itr = document.Begin(); itr != document.End(); ++itr) {
        const Value& obj = *itr;
        // Check if the object matches the user's input
        if (obj["manga_name"].IsString() && obj["manga_name"].GetString() == manga_name &&
            obj["volume_number"].IsString() && obj["volume_number"].GetString() == volume_number &&
            obj["mangaka_name"].IsString() && obj["mangaka_name"].GetString() == mangaka_name &&
            obj["publisher_name"].IsString() && obj["publisher_name"].GetString() == publisher_name &&
            obj["print_edition"].IsString() && obj["print_edition"].GetString() == print_edition &&
            obj["extra_comments"].IsString() && obj["extra_comments"].GetString() == extra_comments) {
            // If it does, print the object
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            obj.Accept(writer);
            std::cout << buffer.GetString() << std::endl;
        }
    }
}

};
#endif