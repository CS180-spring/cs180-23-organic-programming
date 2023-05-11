#include <iostream>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"

using namespace std;
using namespace rapidjson;

//function prototypes
void search();

int main() {
    search();
    return 0;
}

void search(){
    //Recieve Filename from User
    string fileName;
    cout<< "Enter the JSON file to Search: ";
    cin >> fileName;

    //Open and Check nput file
    ifstream infile(fileName);
    if (!infile.is_open()) {
        cerr<< "Error: Failed to open JSON file" << endl;
        return ;
    }

    //Read Contents of the JSON file into a string using a string object
    string json_str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

    //Create Document Object (DOM) to Parse
    Document jsonFile;
    jsonFile.Parse(json_str.c_str());

    //Check if Json file for root = array
    if (!jsonFile.IsArray()) {
        cerr << "Error: JSON File's root is not an array" <<endl;
        return;
    }

    //Prompt User to Enter a Key To search by
    string key,value;
    vector<pair<string,string>> filters;

    cout<<"\nEnter the Key-Value Pairs at the Same time as: <Key> <Value>. \nEnter (-1) to Stop.\n"<<endl;
    while(key != to_string(-1)){
        cin>>key;
        if(key== to_string(-1)) break;
        cin>>value;
        filters.push_back(make_pair(key,value));
    } 
    
    //Iterate Array of JSON Objects and Find Values by Key-Value matching
    int count=0;
    //Value& obj =jsonFile;
    vector<Value *> searchResults;


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


    //Print out the Search Results
    for (auto&obj : searchResults) {
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        obj->Accept(writer);
        cout << buffer.GetString() << endl;
    }
}

