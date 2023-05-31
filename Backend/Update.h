#ifndef UPDATE_H
#define UPDATE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "Search.h"

using namespace std;
using namespace rapidjson;

class Update : public Search{
    private:
        Document jsonDoc;
        const char* rapidJsonPath;
        Value* result;
        string fileStr;
        string file; //potentially get rid of

    public:
        //Default Constructor
        Update(){}

        void updateKVP(Document& jsonFile, std::string fileStr, const std::string file){
            double updatedNumVal;
            string updatedStringVal;
            const char* jsonPath;
            jsonPath= buildJsonPath();
            jsonFile.Parse(fileStr.c_str());

            //Create value pointer to query rapidJson style JsonPath Query for One key:value pair.
            try{
                Value *result = Pointer(jsonPath).Get(jsonFile);
                if(result){ //check if Value object is Valid in provided JsonPath
                    if (result->IsString() || result->IsNull()) {  //check the value to be a string
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
            delete []jsonPath;
        }
        void updateAllKeys(Value& value, const std::string& oldKey, const std::string& newKey, Document::AllocatorType& allocator){
            if (value.IsObject()) {
                Value::Object object = value.GetObject();
                for (auto itr = object.MemberBegin(); itr != object.MemberEnd(); ++itr) {
                    if (itr->name == Value().SetString(oldKey.c_str(), oldKey.length(), allocator)) {
                        Value newKeyName(newKey.c_str(), newKey.length(), allocator);
                        object.AddMember(newKeyName, itr->value, allocator);
                        object.RemoveMember(itr->name);
                        break; // Exit the loop after updating the key
                    } else {
                        updateAllKeys(itr->value,oldKey,newKey,allocator);
                    }
                }
            } else if (value.IsArray()) {
                for (SizeType i = 0; i < value.Size(); ++i) {
                    updateAllKeys(value[i],oldKey,newKey,allocator);
                }
            }
        }
        void updateSingleKey(Value& doc, const string& oldKey, const string& newKey, Document::AllocatorType& allocator){
            const char* jsonPath;
            jsonPath= buildJsonPath();

            try{
                Value *object = Pointer(jsonPath).Get(doc);
                if(object){
                    if(object->IsObject()){
                        Value::MemberIterator itr = object->FindMember(oldKey.c_str());
                        if (itr != object->MemberEnd()) {
                            Value newKeyValue(itr->value, allocator);
                            object->RemoveMember(itr);
                            object->AddMember(Value(newKey.c_str(), allocator).Move(), newKeyValue.Move(), allocator);
                        }
                    }
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                delete []jsonPath;
                return; 
            }
            delete []jsonPath;
        }
        void addNewKeyAllObjects(Value& value, const string& key, Document::AllocatorType& allocator){
            if (value.IsObject()) {
                value.AddMember(Value(key.c_str(), key.length(), allocator).Move(),
                                Value().Move(), allocator);

                for (auto& member : value.GetObject()) {
                    addNewKeyAllObjects(member.value, key, allocator);
                }
            } else if (value.IsArray()) {
                for (auto& element : value.GetArray()) {
                    addNewKeyAllObjects(element, key, allocator);
                }
            }
        }
        void addNewKVPtoObject(Value &doc, const string& key, const string& value,Document::AllocatorType& allocator){
            const char* jsonPath;
            jsonPath= buildJsonPath();
            
            try{
                Value *object = Pointer(jsonPath).Get(doc);
                if (object){
                    if(object->IsObject()){
                        object->AddMember(Value(key.c_str(), key.length(), allocator).Move(),
                                        Value(value.c_str(), value.length(), allocator).Move(), allocator);
                    }
                }else throw invalid_argument("JsonPath is either incorrect or does not exist in file");
            }catch(invalid_argument &error){
                cerr<<error.what()<<endl;
                delete []jsonPath;
                return; 
            }
            delete []jsonPath;
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