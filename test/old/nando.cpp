#include <iostream>
#include <fstream>
#include "output/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    std::ifstream i("mangaCollection.json");
    json j;
    i >> j;

    std::vector<std::string> keys;
    for (auto& element : j[0].items()) {
        keys.push_back(element.key());
    }

    std::map<std::string, std::string> user_input;
    for (auto& key : keys) {
        std::cout << "Enter value for " << key << ": ";
        std::string value;
        std::cin >> value;
        user_input[key] = value;
    }

    //check if element from j = user input value, if match = true , pushback element into filtered_json
    json filtered_json;
    for (auto& element : j) {
        bool match = true;
        for (auto& [key, value] : user_input) {
            if (element[key] != value) {
                match = false;
                break;
            }
        }
        if (match) {
            filtered_json.push_back(element);
        }
    }

    std::cout << filtered_json.dump(4) << std::endl;

    return 0;
}