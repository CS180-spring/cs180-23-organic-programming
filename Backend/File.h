#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class File {
public:
    File(const std::string& fileName) : fileName_(fileName) {}

    bool save(const Document& doc) 
    {
        // Serialize the JSON document to a string
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string jsonStr = buffer.GetString();

        // Write the JSON string to a file
        std::ofstream outFile(fileName_);
        if (outFile.is_open()) {
            outFile << jsonStr;
            outFile.close();
            return true;
        }
        return false;
    }

    bool load(Document& doc) 
    {
        // Read the JSON string from the file
        std::ifstream inFile(fileName_);
        if (inFile.is_open()) {
            std::string fileStr((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

            // Parse the JSON string into a new document
            doc.Parse(fileStr.c_str());
            inFile.close();
            return true;
        }
        return false;
    }

    void display(Document& doc, File crud) 
    {
        // Load the JSON document from the database
        Document newDoc;
        crud.load(newDoc);

        // Access the data in the new document
        const Value& test = newDoc["test"]["test"];

        // Print the data to the console
        std::cout << "Hello: " << test.GetString() << std::endl;
    }

private:
    std::string fileName_;
};