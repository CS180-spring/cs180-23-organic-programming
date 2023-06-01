#ifndef DELETE_H
#define DELETE_H
#include <iostream>
#include <vector>
#include <fstream>
#include<filesystem>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "Search.h"

using namespace std;
using namespace rapidjson;

class Delete : public Search{
    private:
        Document jsonFile;
        Value* result;
        string fileStr;
        string file; //potentially get rid of
    public:
        //Default Constructor
        Delete(){}

        void deleteObject(Value& doc){
            const char* jsonPath;
            jsonPath= buildJsonPath();
            
            try{
                Value *object = Pointer(jsonPath).Get(doc);
                if(object){
                    if(object->IsObject() || object->IsArray() || object->IsNumber() || object->IsString()){
                        if(doc.IsArray()) doc.Erase(object);
                        else if(doc.IsObject()) Pointer(jsonPath).Erase(doc);
                    }else cout<<"JsonPath is Not an Object, Array, Number or String"<<endl;   
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                delete []jsonPath;
                return; 
            }
            delete []jsonPath;
        }
        void deleteSingleKVPfromObject(Value& doc, const string& key) {
            const char* jsonPath;
            jsonPath= buildJsonPath();

            try{
                Value *object = Pointer(jsonPath).Get(doc);
                if (object){
                    if(object->IsObject()){
                        object->RemoveMember(key.c_str());
                    }
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                return; 
            }
        }
        void deleteKeysFromAllObjects(Value& value, const vector<string>& keysToDelete) {
            if (value.IsObject()){
                deleteKeyFromObjects(value, keysToDelete);
                for (auto& member : value.GetObject()) {
                    deleteKeysFromAllObjects(member.value,keysToDelete);
                }
            }else if (value.IsArray()) {
                for (SizeType i = 0; i < value.Size(); ++i)
                    deleteKeysFromAllObjects(value[i], keysToDelete);
            }
        }
        void deleteKeyFromObjects(Value& object, const vector<string>& keysToDelete) {
            for (const auto& key : keysToDelete) {
                if (object.HasMember(key.c_str()))
                    object.RemoveMember(key.c_str());
            }
        }
        void deleteMultipleKeysFromObject(Value& doc, const vector<string>& keysToDelete) {
            const char* jsonPath;
            jsonPath= buildJsonPath();
            try{
                Value *object = Pointer(jsonPath).Get(doc);
                if (object){
                    Value& objRef= *object;
                    for (const auto& key : keysToDelete) {
                        if(object->IsArray()){
                            cout<<"JSONPATH referrs to Array and Not an Object"<<endl;
                            return;
                        }else{
                            if (object->HasMember(key.c_str()))
                                object->RemoveMember(key.c_str());
                        }
                    }
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                return; 
            }
        }
        void deleteJSONfile(string &file,Database &db,fs::path path){
            // Convert std::string to C-style string
            //const char* cStrFilename = file.c_str();
            
            fs::path finalPath = path / db.getName()/ file;
            string removeFile = finalPath.string();
            //int val;
            //val= remove(cStrFilename);

            //cout<<"Value of Remove ="<<val<<endl;

            //Delete the file
            if (remove(removeFile.c_str()) != 0) cout<< "\nFailed to delete the file.\n"<<endl;
            else cout<< "\nFile deleted successfully.\n"<<endl;
        }
};
#endif