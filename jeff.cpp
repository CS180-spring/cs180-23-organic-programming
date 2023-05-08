#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;
using namespace rapidjson;

void CreateFolder(const char * folderName)
{   
    wstring wideFolderName;

    // Convert the folder name to a wide string
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, folderName, -1, NULL, 0);
    if (bufferSize == 0) {
        cerr << "Error converting folder name to wide string: " << GetLastError() << endl;
        exit(1);
    }

    wideFolderName.resize(bufferSize);
    MultiByteToWideChar(CP_UTF8, 0, folderName, -1, &wideFolderName[0], bufferSize);

    // Create the folder
    if (CreateDirectoryW(wideFolderName.c_str(), NULL)) {
        cout << "Directory created successfully." << endl;
    } else {
        cerr << "Error creating directory: " << GetLastError() << endl;
    }
}

int main() {

    CreateFolder("C:\\Users\\jeffh\\code\\myfolder");

    // Load the input.json file
    ifstream input("cars.json");
    if (!input.is_open()) {
        cerr << "Error opening input.json." << endl;
        return 1;
    }

    // Parse the input.json file into a RapidJSON document
    Document document;
    IStreamWrapper inputWrapper(input);
    document.ParseStream(inputWrapper);

    // Serialize the document to a string
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    string jsonString = buffer.GetString();

    // Write the JSON string to a file in the data folder
    ofstream output("../myfolder/output.json");
    if (!output.is_open()) {
        cerr << "Error opening output.json." << endl;
        return 1;
    }
    output << jsonString;
    output.close();

    return 0;
}
