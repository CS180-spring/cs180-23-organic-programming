#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace rapidjson;

int main() {
    // Open the input stream and parse the JSON
    std::ifstream input("mangaCollection.json");
    IStreamWrapper isw(input);
    Document document;
    document.ParseStream(isw);

    // Prompt the user to enter values for each key
    std::string manga_name, volume_number, mangaka_name, publisher_name, print_edition, extra_comments;
    std::cout << "Enter manga name: ";
    std::getline(std::cin, manga_name);
    std::cout << "Enter volume number: ";
    std::getline(std::cin, volume_number);
    std::cout << "Enter mangaka name: ";
    std::getline(std::cin, mangaka_name);
    std::cout << "Enter publisher name: ";
    std::getline(std::cin, publisher_name);
    std::cout << "Enter print edition: ";
    std::getline(std::cin, print_edition);
    std::cout << "Enter extra comments: ";
    std::getline(std::cin, extra_comments);

    // Iterate over the objects in the array
    for (Value::ConstValueIterator itr = document.Begin(); itr != document.End(); ++itr) {
        const Value& obj = *itr;
        // Check if the object matches the user's input
        if (obj["manga_name"].IsString() && obj["manga_name"].GetString() == manga_name &&
            obj["volume_number"].IsString() && obj["volume_number"].GetString() == volume_number &&
            obj["mangaka_name"].IsString() && obj["mangaka_name"].GetString() == mangaka_name &&
            obj["publisher_name"].IsString() && obj["publisher_name"].GetString() == publisher_name &&
            obj["print_edition"].IsString() && obj["print_edition"].GetString() == print_edition &&
            obj["extra_comments"].IsString() && obj["extra_comments"].GetString() == extra_comments) {
            // If it does, print the object
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            obj.Accept(writer);
            std::cout << buffer.GetString() << std::endl;
        }
    }

    return 0;
}
