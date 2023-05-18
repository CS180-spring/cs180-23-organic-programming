#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "File.h"

using namespace rapidjson;

class Create
{
public:
    Create(){}

    void createFile()
    {
        std::string fileName = " ";
        std::string choice;
        Document doc;
        doc.SetArray(); //SetObject, SetArray - array for root of json file

        std::cout << "Create a new file?(Y or N): ";
        std::cin >> choice;
        checkInputChar(choice);

        if(choice == "N" || choice == "n") {"Okay have a nice day! \n";}
        else 
        {
            while(choice == "Y" || choice == "y")
            {
                std::cout << "Name of file: ";
                std::cin >> fileName;

                std::cout << "\nWould you like to add objects to your file?(Y or N): ";
                std::cin >> choice;
                checkInputChar(choice);
                
                if(choice == "N" || choice == "n") {std::cout << "Okay have a nice day! \n";}
                else
                {
                    while(choice == "Y" || choice == "y")
                    {
                        createObject(doc);
                        std::cout << "Create another object? (Y or N): ";
                        std::cin >> choice;
                        checkInputChar(choice);
                    }
                }

                fileName = fileName + ".json"; 
                File db(fileName);
                db.save(doc);
                std::cout << "\nCreated the JSON file \"" << fileName;
            }
        }
    }

    void createObject(Document& doc)
    {
        std::string objectNameTemp;
        Value objectName(objectNameTemp.c_str(), objectNameTemp.size(), doc.GetAllocator());

        int objectCount; 
        int kpCount;  

        std::cout << "Enter ammount of objects to add: ";
        std::cin >> objectCount;
        checkInputInt(objectCount);
        std::cout << "Object Name: ";
        std::cin >> objectNameTemp;
        std:: cout << std::endl;

        Value object(kObjectType);

        for(int i = 0; i < objectCount; i++)
        {
            createKVP(doc, object);
            doc.PushBack(object, doc.GetAllocator());
        }
    }

    void createKVP(Document& doc, Value& object)
    {
        int kpCount; 
        std::string keyInputTemp;
        std::string valueInputTemp;

        std::cout << "Enter ammount of key-value pairs for this object: ";
        std::cin >> kpCount;
        checkInputInt(kpCount);
        
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
    }

    void checkInputChar(std::string &userInput)
    {   
        do{
            if((userInput != "y" && userInput != "Y" && userInput != "n" && userInput != "N" )|| userInput.size() > 1 || userInput == " ") {validInput = false;} else {validInput = true;}
            if (validInput == false) 
            {
                std::cout << "Invalid Input! Please only input Y or N: ";
                std::cin >> userInput; 
            }

        }while(validInput == false);
    }

    void checkInputInt(int &userInput)
    {   
        /*do{
            if(std::cin.fail()) {validInput = false;} else {validInput = true;}
            if (validInput == false) 
            {
                std::cout << "Invalid Input! Please only input a numerical value: ";
                std::cin >> userInput; 
            }
        }while(validInput == false);*/
        
        /*if(std::cin.fail()){validInput = false;}

        while(validInput = false)
        {
            std::cout << "Invalid! Please only input a numerical value: ";
            while(std::cin.fail())
            {
                std::cin >> userInput;
            }
            validInput = true;
        }*/
    }

private:
    File file(std::string name);
    bool validInput = false;
    std::string fileName_;
};




