#ifndef UPDATE_H
#define UPDATE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

class Update{
    private:
        Document jsonFile;
        Value* result;
        string file,fileStr;
    
        //Format traditional JsonPath syntax to function with RapidJson
            const char* formatJsonPath(string input){
            //Declare & init variables for string --> cstring conversion
            string formatted= '/'+ input;
            size_t length = formatted.length();
            char *result = new char[length+1]; //account for null terminator
            strcpy(result,formatted.c_str());  //copy the string to c-string array
            
            //iterate through c-string to find the '.' to replace with '/'
            for (size_t i = 0; i < length; ++i) {
                if (result[i] == '.') {
                    result[i] = '/';
                }
            }
            return result;
        }
        void writeUpdate(){
            ofstream outFile(file); //Edit this to pass a variable rather than hard code
            if (!outFile.is_open()) {
                cerr<< "Error: Failed to open output file" << endl;
                return;
            }

            //Write the JSON document to String
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            jsonFile.Accept(writer);
            outFile << buffer.GetString() << endl;
            outFile.close();
        }

    public:
        //inline constructor
        Update(const std::string& fileName) : file(fileName){}

        void updateJson(){
            double updatedNumVal;
            string jsonPath,updatedStringVal;
            const char* rapidJsonPath;

            //Create Document Object (DOM) to Parse
            Document jsonFile;
            jsonFile.Parse(fileStr.c_str());

            //Prompt User to enter JSONPath Query
            //UPDATE to Prompt JSON path in FIle.h and pass along to CRUD ops
            cout<<"\nEnter the JsonPath: " ;
            cin >> jsonPath;
            rapidJsonPath= formatJsonPath(jsonPath);

            //Create value pointer to query rapidJson style JsonPath Query for One key:value pair.
            try{
                Value* result = Pointer(rapidJsonPath).Get(jsonFile);
                if(result){ //check if Value object is Valid in provided JsonPath
                    if (result->IsString()) {  //check the value to be a string
                        cout<<"\nEnter Updated Value: ";
                        cin >> updatedStringVal;
                        result->SetString(updatedStringVal.c_str(),updatedStringVal.length(),jsonFile.GetAllocator());
                    }else if (result->IsNumber()){
                        cout<<"\nEnter Updated Value: ";
                        cin >> updatedNumVal;
                        result->SetDouble(updatedNumVal);
                    }else cout<<"Value Field is Not a String or Number"<<endl;
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                return; 
            }
            writeUpdate();      //call helper function to write the update
            delete []rapidJsonPath;
        }
        void setJsonStr(string parsedStr){ //set the JSON string after file parse
            this->fileStr= parsedStr;
        }
        string getJsonStr(){     //get the JSON string
            return fileStr;
        }
        Value *getJsonObject(){  //return JsonObject from JsonPath Query
            return result;
        }
};

#endif