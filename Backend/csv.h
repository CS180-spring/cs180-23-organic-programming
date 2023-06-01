#ifndef CSV_H
#define CSV_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <map>
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
namespace rjson = rapidjson;

class CSV {
    private:
        //helper Functions to read in/ format CSV
        static bool whiteSpaceCheck(unsigned char c){
            bool value= isspace(c);  
            return value;
        }
        vector<string> split(string line, char delim){
            string field;
            vector<string> fields;
            stringstream ss(line);

            while(getline(ss,field,delim)){
                //remove all white spaces and push each field string to fields vector
                field.erase(remove_if(field.begin(),field.end(),whiteSpaceCheck),field.end());
                fields.push_back(field);
            }

            return fields;
        }

    public:
        //Default Constructor
        CSV(){}

        void convertCSV(Database &db,fs::path path){
            string input_file,output_file,extension;
            fs::path finalPath;

            cout<< "Enter your Input Filename: ";
            cin >> input_file;
            
            finalPath = path / db.getName()/ input_file;
            string inptfile = finalPath.string();

            //Open Input file and check if open
            ifstream inFile(inptfile.c_str());
            if (!inFile.is_open()){
                cerr<< "Error: Failed to open input file" << endl;
                return;
            }

            //Vector to Store Data from CSV as Map
            vector<map<string,string>> data;
            string line;
            
            //Read in header row of CSV
            getline(inFile,line);
            vector<string> headers = split(line, ',');

            //Read in the rest of the CSV
            while(getline(inFile,line)){
                map<string,string> item;
                vector<string> fields = split(line,','); //split each line of csv and store
                
                //Loop through headers vector store and the map/dictionary as fields
                for(int i=0; i<headers.size(); i++){
                    item[headers[i]]= fields [i];
                }

                data.push_back(item); //store all csv data to vector of maps
            }

            //Change .csv file extension to .json
            extension= ".json";
            output_file = input_file.replace(input_file.find(".csv"),5,extension);
            
            finalPath = path / db.getName()/ output_file;
            string outptfile = finalPath.string();
            
            //Open Output file and check if open
            ofstream outFile(outptfile.c_str());
            if (!outFile.is_open()) {
                cerr<< "Error: Failed to open Output file" << endl;
                return;
            }

            //Create the Json Document Object
            rjson::Document document;
            document.SetArray();
            for(const auto& row: data){
                rjson::Value object(rjson::Type::kObjectType);
                for(const auto& entry: row ){
                    rjson::Value key(entry.first.c_str(), document.GetAllocator());
                    rjson::Value value(entry.second.c_str(), document.GetAllocator());
                    object.AddMember(key,value,document.GetAllocator());
                }
                document.PushBack(object,document.GetAllocator());
            }

            //Write the JSON document to String
            rjson::StringBuffer buffer;
            rjson::PrettyWriter<rjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            outFile << buffer.GetString() << endl;

            //Close the input.outputs files
            inFile.close();
            outFile.close();
        }

};
#endif