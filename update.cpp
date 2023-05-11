#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class JSONDatabase {
public:
    JSONDatabase(){}

    bool load(std::string fileName) 
    {
        // Read the JSON string from the file
        std::ifstream inFile(fileName);
        if (inFile.is_open()) {
            std::string json((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

            // Parse the JSON string into a new document
            Document doc;
            doc.Parse(json.c_str());
            inFile.close();
            return true;
        }
        else
        {
            std::cout << "Error: File " << fileName << " Could Not be Opened!";
            return false;
        }   
    }

    bool save(std::string fileName, Document& doc) 
    {
        // Serialize the JSON document to a string
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string jsonStr = buffer.GetString();

        // Write the JSON string to a file
        std::ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << jsonStr;
            outFile.close();
            return true;
        }
        return false;
    }
};


int main()
{
    JSONDatabase database;
    Document doc;
    int kpCount;
    std::string keyInputTemp;
    std::string valueInput;
    std::string fileName;

    doc.SetObject();

    std::cout << "Enter file you want to update: ";
    std::cin >> fileName; 

    database.load(fileName);

    std::cout << "Enter ammount of key-value pairs for this object: ";
    std::cin >> kpCount;
    
    for(int i = 0; i >= kpCount; i++)
    {
        std::cout << "Key: ";
        std::cin >> keyInputTemp;
        std::cout << "Value: ";
        std::cin >> valueInput;
        Value keyInput(keyInputTemp.c_str(), keyInputTemp.size(), doc.GetAllocator());
        doc.AddMember(keyInput, valueInput, doc.GetAllocator());
    }

    database.save(fileName, doc);

    return 0;
}