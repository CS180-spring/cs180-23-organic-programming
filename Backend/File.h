#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "Create.h"
#include "Read.h"
#include "Update.h"
#include "Delete.h"
#include "Search.h"
#include "csv.h"

using namespace rapidjson;

//Composition class for all CRUD operations
class File {
    private:
        Document jsonDoc;
        std::string fileName;
        std::string fileJSONStr; 

        //Helper function for changing string input to const string;
        string getUserInput(void){
            string userStrInput;
            cin >> userStrInput;
            return userStrInput;
        }

    protected:
        Create create; 
        Read read;
        Update update;
        Delete remove;
        Search search;
        CSV csv;
        Validate validator;

    public:
        File(const std::string& fileName_) : fileName(fileName_) {}
        File(){}

        void createFile(){

            fileName = " ";
            //Document newFile;
            this->jsonDoc.SetArray(); //SetObject, SetArray - array for root of json file
            std::string choice;

            std::cout << "=============================================================\n";
            std::cout << "CREATE"<<std::endl;
            std::cout << "=============================================================\n";
            std::cout << "\nCreate a new file?(Y or N): ";
            std::cin >> choice;
            validator.checkInputChar(choice);

            if(choice == "N" || choice == "n"){
                std::cout << "Okay have a nice day! \n";
                return;
            }else{
                while(choice == "Y" || choice == "y")
                {
                    std::cout << "Name of file: ";
                    std::cin >> fileName;
                    this->jsonDoc = create.buildFile(); //usage of Create member 
                    
                    read.read(fileName);
                    read.save(jsonDoc); //usage of Read member
                    std::cout << "\nCreated the JSON file \"" << fileName << "\"\n";
                    
                    std::cout << "Create another file?(Y or N): ";
                    std::cin >> choice;
                    validator.checkInputChar(choice);
                }
                std::cout << "OKay have a nice day!";
            }
        }
        void readFile(){
            std::cout << "Name of file: ";
            std::cin >> fileName;
            read.read(fileName);

            try{
                this->fileJSONStr= read.load(jsonDoc);
                if(fileJSONStr== ""){
                    throw invalid_argument("\n###  FileName Does Not Exist  ###");
                }
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                return;
            }
        }
        void updateFile(){
            std::cout << "=============================================================\n";
            std::cout << "UPDATE"<<std::endl;
            std::cout << "=============================================================\n";
            
            int choice;
            readFile();     //read most current file and save to JSON file string
            if(fileJSONStr == "")return;

            //prompt User input for update options
            std::cout<<"\nUpdate Options\n"
                        "------------------\n" 
                        "1. Add New JSON Object\n"
                        "2. Update Single Value in JSON Object\n"
                        "3. Update All Specified Keys in JSON File\n"
                        "4. Update Single Key in JSON Object\n"
                        "5. Add Key to All JSON Objects in File\n"
                        "6. Add Single Key-Value Pair to JSON Object\n"<<std::endl;
            
            std::cout<<"\nEnter Update Option: ";
            cin>>choice; 
            
            //Invoke update function based on user input
            switch(choice){
                case 1:
                    create.createObject(jsonDoc);
                    read.save(jsonDoc);
                    break;
                case 2:
                    update.updateKVP(jsonDoc,fileJSONStr,fileName);
                    read.save(jsonDoc);
                    break;
                case 3:{
                    cout<<"\nEnter the Old Key to Replace: ";
                    const string oldKey= getUserInput();
                    cout<<"\nEnter the New Key: ";
                    const string newKey= getUserInput();
                    update.updateAllKeys(jsonDoc,oldKey,newKey,jsonDoc.GetAllocator());
                    read.save(jsonDoc);
                    break;
                }
                case 4:{
                    cout<<"\nEnter the Old Key to Replace: ";
                    const string oldKey= getUserInput();
                    cout<<"\nEnter the New Key: ";
                    const string newKey= getUserInput();
                    update.updateSingleKey(jsonDoc,oldKey,newKey,jsonDoc.GetAllocator());
                    read.save(jsonDoc);
                    break;
                }
                case 5:{
                    cout<<"\nEnter the New Key to Add: ";
                    const string newKey= getUserInput();
                    update.addNewKeyAllObjects(jsonDoc,newKey,jsonDoc.GetAllocator());
                    read.save(jsonDoc);
                    break;
                }
                case 6:{
                    cout<<"\nEnter the New Key to Add: ";
                    const string newKey= getUserInput();
                    cout<<"\nEnter the New Value to Add: ";
                    const string newVal= getUserInput();
                    update.addNewKVPtoObject(jsonDoc,newKey,newVal,jsonDoc.GetAllocator());
                    read.save(jsonDoc);
                    break;
                }
                default:
                    cout<<"\nInvalid Choice"<<endl;
                    return;     //wrong choice input
            }
        }
        void deleteFile(){
            std::cout << "=============================================================\n";
            std::cout << "DELETE"<<std::endl;
            std::cout << "=============================================================\n";

            int choice;
            readFile();     //read most current file and save to JSON file string
            if(fileJSONStr == "")return;

            //prompt User input for update options
            std::cout<<"\nDelete Options\n"
                        "------------------\n" 
                        "1. Delete JSON Object from File\n"
                        "2. Delete A Key-Value Pair From a JSON Object\n"
                        "3. Delete A Key-Value Pair from All JSON Objects\n"
                        "4. Delete Multiple Key-Value Pairs From a JSON Object\n"
                        "5. Delete Multiple Key-Value Pairs From All JSON Objects\n"<<std::endl;
            
            std::cout<<"\nEnter Update Option: ";
            cin>>choice; 
            
            switch(choice){
                case 1:
                    remove.deleteObject(jsonDoc);
                    read.save(jsonDoc);
                    break;
                case 2:{
                    cout<<"\nEnter the Key to Remove: ";
                    const string keyRemoved = getUserInput();
                    remove.deleteSingleKVPfromObject(jsonDoc,keyRemoved);
                    read.save(jsonDoc);
                    break;
                }
                case 3:{
                    vector<string>keys;
                    cout<<"\nEnter the Key to Remove: ";
                    string key= getUserInput();
                    keys.push_back(key);

                    //Assign mutable vector to const vector
                    const vector<string>& keysToDelete= keys;
                    remove.deleteKeysFromAllObjects(jsonDoc,keysToDelete);
                    read.save(jsonDoc);
                    break;
                }
                case 4:{
                    vector<string>keys;
                    string key;
                    while (true) {
                        cout << "Enter a Key (or '-1' to Stop): ";
                        key=getUserInput();

                        if (key == "-1") {
                            break;
                        }
                        keys.push_back(key);
                    }
                    //Assign mutable vector to const vector
                    const vector<string>& keysToDelete= keys;
                    remove.deleteMultipleKeysFromObject(jsonDoc,keysToDelete);
                    read.save(jsonDoc);
                    break;
                }
                case 5:{
                    vector<string>keys;
                    string key;
                    while (true) {
                        cout << "Enter a Key (or '-1' to Stop): ";
                        key=getUserInput();

                        if (key == "-1") {
                            break;
                        }
                        keys.push_back(key);
                    }
                    //Assign mutable vector to const vector
                    const vector<string>& keysToDelete= keys;
                    remove.deleteKeysFromAllObjects(jsonDoc,keysToDelete);
                    read.save(jsonDoc);
                    break;
                }
                default:
                    cout<<"\nInvalid Choice"<<endl;
                    return;
            }
        }
        void searchFile(){
            std::cout << "=============================================================\n";
            std::cout << "SEARCH"<<std::endl;
            std::cout << "=============================================================\n";
            
            int choice;
            readFile();     //read most current file and save to JSON file string
            if(fileJSONStr == "")return;

            //prompt User input for search options
            std::cout<<"\nSearch Options\n"
                        "------------------\n" 
                        "1. Search for Value by JSONPath Query\n"
                        "2. Search for JSON Object by JSONPath Query\n"
                        "3. Filter Objects by Key-Value Pairs\n"<<std::endl;
                        
            std::cout<<"\nEnter Update Option: ";
            cin>>choice; 
            
            switch(choice){
                case 1:
                    search.jsonPathQuery(jsonDoc);
                    break;
                case 2:
                    search.jsonPathQuery(jsonDoc);
                    break;
                case 3:
                    search.filter(jsonDoc);
                    break;
                default:
                    cout<<"\nInvalid Choice"<<endl;
                    return;
            }
        }
        void convertFile(){
            cout<<"\nConverting CSV ---> JSON\n--------------------------------"<<endl<<endl;
            csv.convertCSV();
        }
        void print(){
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            jsonDoc.Accept(writer);
            std::cout << buffer.GetString() << std::endl;
        }
};
#endif