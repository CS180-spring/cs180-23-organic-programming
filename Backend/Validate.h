#ifndef VALIDATE_H
#define VALIDATE_H
#include <iostream>
#include <fstream>
#include <string>

class Validate
{
public:
    Validate(){}

    void checkInputChar(std::string &userInput)
    {   
        do{
            if((userInput != "y" && userInput != "Y" && userInput != "n" && userInput != "N" )|| userInput.size() > 1 || userInput == " ") {validInput = false;} else {validInput = true;}
            if (validInput == false) 
            {
                std::cout << "Invalid Input! Please only input Y or N: ";
                std::cin >> userInput; 
            }

        }while(validInput == false);
    }

    void checkInputInt(int &userInput)
    {   
        /*do{
            if(std::cin.fail()) {validInput = false;} else {validInput = true;}
            if (validInput == false) 
            {
                std::cout << "Invalid Input! Please only input a numerical value: ";
                std::cin >> userInput; 
            }
        }while(validInput == false);*/
        
        //if(std::cin.fail()){validInput = false;}

        /*if(userInput == )
        while(validInput = false)
        {
            std::cout << "Invalid! Please only input a numerical value greater than 0: ";
            while(std::cin.fail())
            {
                std::cin >> userInput;
            }
            validInput = true;
        }*/
    }

private:
    bool validInput = false;
};

#endif