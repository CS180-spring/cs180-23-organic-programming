#include <iostream>
#include "File.h"

int main()
{   
    cout<<"\n\nWelcome to the Backend"<<endl;
    bool backendTest=true;
    int choice;
    File file;
    string input;

    while(backendTest){
        cout<<"\nSelect File Operation\n"
                        "----------------------\n" 
                        "1. Create\n"
                        "2. Read\n"
                        "3. Update\n"
                        "4. Delete\n"
                        "5. Search\n"
                        "6. Convert"<<std::endl;
        
        cout<<"\nEnter Choice of Operation (or -1 to Prompt Quit): ";
        cin >> choice; 

        switch(choice){
            case 1:
                file.createFile();
                break;
            case 2:
                file.readFile();
                break;
            case 3:
                file.updateFile();
                break;
            case 4:
                file.deleteFile();
                break;
            case 5:
                file.searchFile();
                break;
            case 6:
                file.convertFile();
                break;
            default:
                cout<<"Continue Operations? (Y or N): ";
                cin >> input;
                if(input == "N" || input == "n") backendTest=false; 
                else{
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    backendTest=true;
                }
        }
    }

    return 0;
}