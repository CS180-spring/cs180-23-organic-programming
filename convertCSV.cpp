#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

using JSON = nlohmann::json;
using namespace std;

//Function Prototypes
bool whiteSpaceCheck(unsigned char);
vector<string> split(string, char);
void convertCSV();

//Main
int main(int argc, char *arg[]){
    //Function Call 
    convertCSV();
    //Exit Program
    return 0;
}

//Fucntion Prototype Implementation
bool whiteSpaceCheck(unsigned char c){
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

void convertCSV(){
    std::string input_file, output_file,extension;

    std::cout<< "Enter your Input Filename: ";
    std::cin >> input_file;

    ///////
    //string input_file = "usernames.csv";
    //string output_file ="usernames.json";

    //Open Input file and check if open
    ifstream inFile(input_file);
    if (!inFile.is_open()) {
        cout << "Error: Failed to open input file " << input_file << endl;
        //cerr<< "Error: Failed to open input file" << endl;
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
    
    //Open Output file and check if open
    ofstream outFile(output_file);
    if (!outFile.is_open()) {
        cout << "Error: Failed to open Output file " << output_file << endl;
        //cerr<< "Error: Failed to open Output file" << endl;
        return;
    }

    //Create the Json Object and Dump the data to JSON
    JSON jsonData = data; 
    cout<< jsonData.dump(4)<<endl;
    outFile << jsonData.dump(4)<<endl;

    //Close the input.outputs files
    inFile.close();
    outFile.close();
}