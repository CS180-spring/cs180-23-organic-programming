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
string readJson(string);

int main() {
    updateJson();
    return 0;
}
void updateJson(){
    double updatedNumVal;
    string jsonPath,fileName,json_str,updatedStringVal;
    const char* rapidJsonPath;

    cout<< "Enter the JSON file to Search: ";
    cin >> fileName;
    json_str = readJson(fileName);
    
    //Create Document Object (DOM) to Parse
    Document jsonFile;
    jsonFile.Parse(json_str.c_str());

    //Prompt User to enter JSONPath Query
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

    ofstream outFile(fileName); //Edit this to pass a variable rather than hard code
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

    delete []rapidJsonPath;
}
string readJson(string file){
    //Open and Check nput file
    ifstream infile(file);
    if (!infile.is_open()) {
        cerr<< "Error: Failed to open JSON file" << endl;
        exit(1);
    }
    //Read Contents of the JSON file into a string using a string object
    string json_str((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

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