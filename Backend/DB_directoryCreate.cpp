#include <iostream>
#include <cstdlib>
#include <filesystem>
//using namespace std;
namespace fs = std::filesystem;

//Function prototypes
void dbDirectoryCreate();

int main(){
    dbDirectoryCreate();
    return 0;
}

void dbDirectoryCreate(){
    //Create the root DB directory
    fs::path dbDirectory= "../CS180_DBproject";
    fs::create_directory(dbDirectory);
    
    //Create the example sub directories
    fs::create_directory(dbDirectory / "Collection1");
    fs::create_directory(dbDirectory / "Collection2");
    fs::create_directory(dbDirectory / "Collection3");

    fs::current_path(dbDirectory);
    std::cout<<"The Current Path = " << fs::current_path() <<std::endl;
}