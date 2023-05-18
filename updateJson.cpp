#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

//function prototypes
void updateJson();
const char* formatJsonPath(string);
string readJson();

int main() {
    updateJson();
    return 0;
}
void updateJson(){
    string json_str = readJson();
    
    //Create Document Object (DOM) to Parse
    Document jsonFile;
    jsonFile.Parse(json_str.c_str());

    //Prompt User to enter JSONPath Query
    string jsonPath, updatedValue;
    const char* rapidJsonPath;
    cout<<"\nEnter the JsonPath: " ;
    cin >> jsonPath;
    rapidJsonPath= formatJsonPath(jsonPath);

    cout<<"\nEnter the New Value to Update Object With: ";
    cin >> updatedValue;

    //Create value pointer to query rapidJson style JsonPath Query
    Value* result = Pointer(rapidJsonPath).Get(jsonFile);

    if (result && result->IsString()){
        result->SetString(updatedValue.c_str(),updatedValue.length(),jsonFile.GetAllocator());
    }
    else cout<<"\nObject's Value Could Not be Found"<<endl;

    /*
    ofstream outFile("usernames.json");
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
    */
}
string readJson(){
    //Recieve Filename from User
    string fileName;
    cout<< "Enter the JSON file to Search: ";
    cin >> fileName;

    //Open and Check nput file
    ifstream infile(fileName);
    if (!infile.is_open()) {
        cerr<< "Error: Failed to open JSON file" << endl;
        exit(1);
    }
    //Read Contents of the JSON file into a string using a string object
    string json_str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    return json_str;
}
const char* formatJsonPath(string input){
    //Declare and init variables for string --> cstring conversion
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
