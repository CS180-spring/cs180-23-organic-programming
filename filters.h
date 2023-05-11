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
std::vector<std::string> getKeysFromFirstObject(const std::string& filename) {
    std::vector<std::string> keys;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        rapidjson::Document doc;
        doc.Parse(jsonStr.c_str());
        cout << jsonStr;
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

};
#endif