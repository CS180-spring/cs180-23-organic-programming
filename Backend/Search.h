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
        
        //Format traditional JsonPath syntax to function with RapidJson
        char* formatJsonPath(string input){
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
        //Default Constructor
        Search (){}
        
        void filter(Document &jsonFile){      //Return filtered JSON Objects
            int count=0;
            string key,value;
            vector<Value *> searchResults;
            vector<pair<string,string>> filters;

            //Parse RapidJson Document Object (DOM)
            jsonFile.Parse(fileStr.c_str());

            //Prompt user input for Key-Val Pairs to use as filters
            cout<<"\nEnter the Key-Value Pairs at the Same time as: <Key> <Value> (or '-1' to Stop)\n"<<endl;
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
            
            //Output Results of Filtered Search
            for (auto&obj : searchResults) {
                StringBuffer buffer;
                PrettyWriter<StringBuffer> writer(buffer);
                obj->Accept(writer);
                cout << buffer.GetString() << endl;
            }
        }
        void jsonPathQuery(Document &jsonFile){   //Search by JsonPath Query (RapidJson Style)
            const char* jsonPath;
            jsonPath= buildJsonPath();

            //Parse RapidJson Document Object (DOM)
            jsonFile.Parse(fileStr.c_str());

            //Exception Handler for Json Object Values
            try{
                Value *result = Pointer(jsonPath).Get(jsonFile);
                if(result){
                    if(result->IsObject()){
                        StringBuffer buffer;
                        PrettyWriter<StringBuffer> writer(buffer);
                        result->Accept(writer);
                        cout <<endl<< buffer.GetString() << endl<<endl;
                    }else if (result->IsString()) {
                        cout<<endl<< result->GetString() << endl<<endl;
                        //this->strVal= result->GetString();
                    }else if (result->IsNumber()){
                        cout<<endl<< result->GetDouble()<<endl<<endl;
                        //this->numVal= result->GetDouble();
                    }else cout<<"JSON Path Was not Object and/or Value Field is Not a String or Number"<<endl;
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                delete []jsonPath;
                return; 
            }
            //Clean up memory
            delete []jsonPath;
        }
        const char* buildJsonPath(){
            string jsonPath;
            const char* rapidJsonPath;
            
            //Prompt User to enter JSONPath Query
            cout<<"\nEnter the JsonPath: " ;
            cin >> jsonPath;
            rapidJsonPath= formatJsonPath(jsonPath);
            return rapidJsonPath;
        }
};

#endif