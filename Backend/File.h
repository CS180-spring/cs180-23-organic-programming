#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Create.h"
#include "Read.h"

using namespace rapidjson;

class File {
public:
    File(const std::string& fileName_) : fileName(fileName_) {}
    File(){}

    void createFile()
    {
        Document newFile;
        newFile.SetArray(); //SetObject, SetArray - array for root of json file
        fileName = " ";
        std::string choice;

        std::cout << "Create a new file?(Y or N): ";
        std::cin >> choice;
        validator().checkInputChar(choice);

        if(choice == "N" || choice == "n") {std::cout << "Okay have a nice day! \n";}
        else 
        {
            while(choice == "Y" || choice == "y")
            {
                std::cout << "Name of file: ";
                std::cin >> fileName;
                newFile = create().createFile();
                
                read(fileName).save(newFile);
                std::cout << "\nCreated the JSON file \"" << fileName << "\"\n";
                
                std::cout << "Create another file?(Y or N): ";
                std::cin >> choice;
            }
            std::cout << "OKay have a nice day!";
        }
    }

private:
    std::string fileName;
    Validate validator();

protected:
    Create create(); 
    Read read(std::string fileName);
};

#endif