#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

class Search{
    private:
        Document jsonFile;
        Value* result;
        const char* strVal;
        double numVal;
        string file,fileStr;
        vector<pair<string,string>> filters;
        vector<Value *> searchResults;

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

    public:
        //inline constructor
        Search(const std::string& fileName) : file(fileName){}
        void filter(){      //Return filtered JSON Objects
            int count=0;
            string key,value;

            //Parse RapidJson Document Object (DOM)
            jsonFile.Parse(fileStr.c_str());

            //Prompt user input for Key-Val Pairs to use as filters
            cout<<"\nEnter the Key-Value Pairs at the Same time as: <Key> <Value>. \nEnter (-1) to Stop.\n"<<endl;
            while(key != to_string(-1)){
                cin>>key;
                if(key== to_string(-1)) break;
                cin>>value;
                filters.push_back(make_pair(key,value));
            } 
            
            //Iterate through parsed DOM and store matching Key-Val pairs in Results vector
            for (SizeType i = 0; i < jsonFile.Size(); i++) {
                Value& obj= jsonFile[i];
                if (obj.IsObject()){
                    for (const auto& entry : filters){
                        if (obj.HasMember(entry.first.c_str()) && obj[entry.first.c_str()].GetString() == entry.second){
                            ++count;
                        }
                    }
                    if (count == filters.size()){
                        searchResults.push_back(&obj);
                    }
                }
                count=0;
            }
        }
        void jsonPathQuery(){   //Search by JsonPath Query (RapidJson Style)
            string jsonPath;
            const char* rapidJsonPath;

            //Parse RapidJson Document Object (DOM)
            jsonFile.Parse(fileStr.c_str());

            //Prompt User to enter JSONPath Query
            cout<<"\nEnter the JsonPath: " ;
            cin >> jsonPath;
            rapidJsonPath= formatJsonPath(jsonPath);

            //Exception Handler for Json Object Values
            try{
                this->result = Pointer(rapidJsonPath).Get(jsonFile);
                if(result){
                    if (result->IsString()) {
                        //cout<< result->GetString() << endl;
                        this->strVal= result->GetString();
                    }else if (result->IsNumber()){
                        //cout<< result->GetDouble()<<endl;
                        this->numVal= result->GetDouble();
                    }else cout<<"Value Field is Not a String or Number"<<endl;
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                return; 
            }
            //Clean up memory
            delete []rapidJsonPath;
        }
        void printFilteredSearch(){        //Output filtered Objects   
            for (auto&obj : searchResults) {
                StringBuffer buffer;
                PrettyWriter<StringBuffer> writer(buffer);
                obj->Accept(writer);
                cout << buffer.GetString() << endl;
            }
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
        const char* getStrVal(){ //get Json Object's string Value from JsonPath Query
            return strVal;
        }
        double getNumVal(){      //get Json Object's number Value from JsonPath Query
            return numVal;
        }

};

#endif