#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Validate.h"

using namespace rapidjson;

class Create
{
public:
    Create(){}

    Document buildFile()
    {
        Document doc;
        std::string choice;
        doc.SetArray(); //SetObject, SetArray - array for root of json file

        std::cout << "\nWould you like to add objects to your file?(Y or N): ";
        std::cin >> choice;
        validator.checkInputChar(choice);
        
        if(choice == "N" || choice == "n") {std::cout << "Okay have a nice day! \n";}
        else
        {
            while(choice == "Y" || choice == "y")
            {
                createObject(doc);
                std::cout << "\nCreate another object? (Y or N): ";
                std::cin >> choice;
                validator.checkInputChar(choice);
                std::cout << std::endl;
            }
        }
    
        return doc;
    }

    void createObject(Document& doc)
    {
        std::string objectNameTemp;
        Value objectName(objectNameTemp.c_str(), objectNameTemp.size(), doc.GetAllocator());

        int objectCount; 

        std::cout << "Enter ammount of objects to add: ";
        std::cin >> objectCount;

        //validator.checkInputInt(objectCount);
        std::cout << "Object Name:";
        std::cin >> objectNameTemp;
        std::cout << std::endl;

        Value object(kObjectType);

        for(int i = 0; i < objectCount; i++)
        {
            std::cout << "=============================================================\n";
            std::cout << "Object " << (i+1) << ": " << objectNameTemp;
            std::cout << "\n=============================================================";
            createKVP(doc, object);
            std::cout << "Created object: " << objectNameTemp << std::endl;
            doc.PushBack(object, doc.GetAllocator());
        }
    }

    void createKVP(Document& doc, Value& object)
    {
        int kpCount; 
        std::string keyInputTemp;
        std::string valueInputTemp;

        std::cout << "\nEnter ammount of key-value pairs for this object: ";
        std::cin >> kpCount;
        validator.checkInputInt(kpCount);
        
        for(int i = 0; i < kpCount; i++)
        {
            std::cout << "Key" << "(" << (i+1) << "): ";
            std::cin >> keyInputTemp;
            std::cout << "Value" << "(" << (i+1) << "): ";
            std::cin >> valueInputTemp;


            Value keyInput(keyInputTemp.c_str(), keyInputTemp.size(), doc.GetAllocator());
            Value valueInput(valueInputTemp.c_str(), valueInputTemp.size(), doc.GetAllocator());
            object.AddMember(keyInput, valueInput, doc.GetAllocator());
        }
    }

private:
    Validate validator;
    Document doc;
    std::string fileName_;
};






