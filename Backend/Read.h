#ifndef READ_H
#define READ_H
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <filesystem>

using namespace rapidjson;

class Read
{
public:
    Read() {}

    void read(std::string &fileName, string frontEndPath)
    {
        fs::path p = frontEndPath.c_str();
        fs::path fName = fileName.c_str();
        fs::path finalPath = frontEndPath / fName;
        
        fileName_ = finalPath.string();
    }

    bool save(const Document &doc)
    {
        // Check outputfile status- Write the JSON string to a file
        std::ofstream outFile(fileName_.c_str());
        if (!outFile.is_open()){
            std::cerr << "\nError: Failed to open output file" << std::endl;
            return false;
        }

        // Serialize the JSON document to a string
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        doc.Accept(writer);
        outFile << buffer.GetString() << std::endl;
        outFile.close();
        return true;
    }

    std::string load(Document &doc)
    {
        // Read the JSON string from the file
        std::ifstream inFile(fileName_.c_str());
        if (!inFile.is_open())
        {
            std::cerr << "\nError: Failed to open File" << std::endl;
            return "";
        }

        // Read Contents of the JSON file into a string using a string object
        std::string jsonStr((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

        // Parse the JSON string into a new document
        doc.Parse(jsonStr.c_str());
        inFile.close();

        return jsonStr;
    }

private:
    std::string fileName_;
};
#endif