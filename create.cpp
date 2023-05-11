#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class JSONDatabase {
public:
    JSONDatabase(const std::string& fileName) : fileName_(fileName) {}

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

    void display(Document& doc, JSONDatabase db) 
    {
        // Load the JSON document from the database
        Document newDoc;
        db.load(newDoc);

        // Access the data in the new document
        const Value& test = newDoc["test"]["test"];

        // Print the data to the console
        std::cout << "Hello: " << test.GetString() << std::endl;
    }

private:
    std::string fileName_;
};

void createFile();
void createObject(Document& doc);
void testSaveLoadExample();
int main() {
    char choice1;
    std::cout << "Create JSON file?(Y or N)";
    std::cin >> choice1;
    
    if(toupper(choice1) == 'N') {"Okay have a nice day! \n";}
    else 
    {
        while(toupper(choice1) == 'Y')
        {
            createFile();
            std::cout << "Create another file?(Y or N)";
            std::cin >> choice1;
        }
    }
    std::cout << "Goodbye!";

    //testSaveLoadExample();
    return 0;
}


void createFile()
{
    std::string fileName;
    char choice;
    Document doc;
    doc.SetArray(); //SetObject, SetArray - array for root of json file

    std::cout << "Name of file: ";
    std::cin >> fileName;

    std::cout << "Would you like to add objects to your file?(Y or N)";
    std::cin >> choice;

    if(toupper(choice) == 'N') {"Okay have a nice day! \n";}
    else
    {
        while(choice != 'N')
        {
            createObject(doc);
            std::cout << "Create another object? (Y or N)";
            std::cin >> choice;
        }
    }

    JSONDatabase db(fileName);
    db.save(doc);
}

void createObject(Document& doc)
{
    std::string objectNameTemp;
    Value objectName(objectNameTemp.c_str(), objectNameTemp.size(), doc.GetAllocator());

    int objectCount;
    int kpCount;  
    std::string keyInputTemp;
    std::string valueInputTemp;
    std::string valueInput;

    std::cout << "Enter ammount of objects to add: ";
    std::cin >> objectCount;
    std::cout << "Object Name: ";
    std::cin >> objectNameTemp;
    std:: cout << std::endl;

    Value object(kObjectType);

    for(int i = 0; i < objectCount; i++)
    {
        std::cout << "Enter ammount of key-value pairs for this object: ";
        std::cin >> kpCount;
        
        for(int i = 0; i < kpCount; i++)
        {
            std::cout << "Key: ";
            std::cin >> keyInputTemp;
            std::cout << "Value: ";
            std::cin >> valueInputTemp;
            Value keyInput(keyInputTemp.c_str(), keyInputTemp.size(), doc.GetAllocator());
            Value valueInput(valueInputTemp.c_str(), valueInputTemp.size(), doc.GetAllocator());
            object.AddMember(keyInput, valueInput, doc.GetAllocator());
        }
    doc.PushBack(object, doc.GetAllocator());
    }
}

void testSaveLoadExample()
{
    // Create a JSON document
    Document doc;
    doc.SetObject();

    // Add some data to the JSON document
    Value person(kObjectType);
    person.AddMember("name", "John", doc.GetAllocator());
    person.AddMember("age", 30, doc.GetAllocator());
    person.AddMember("city", "New York", doc.GetAllocator());
    doc.AddMember("person", person, doc.GetAllocator());

    // Create a JSON database object
    JSONDatabase db("database.json");

    // Save the JSON document to the database
    db.save(doc);

    // Load the JSON document from the database
    Document newDoc;
    db.load(newDoc);

    // Access the data in the new document
    const Value& name = newDoc["person"]["name"];
    const Value& age = newDoc["person"]["age"];
    const Value& city = newDoc["person"]["city"];

    // Print the data to the console
    std::cout << "Name: " << name.GetString() << std::endl;
    std::cout << "Age: " << age.GetInt() << std::endl;
    std::cout << "City: " << city.GetString() << std::endl;
}

