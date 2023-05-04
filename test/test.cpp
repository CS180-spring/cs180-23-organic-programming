#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class JSONDatabase {
public:
    JSONDatabase(const std::string& path) : m_path(path) {}

    bool insert(const std::string& key, const json& value) {
        std::ofstream file(m_path + "/" + key + ".json");
        if (!file.is_open()) {
            return false;
        }
        file << value.dump();
        file.close();
        
        return true;
    }

    json select(const std::string& key) {
        std::ifstream file(m_path + "/" + key + ".json");
        if (!file.is_open()) {
            return json::object();
        }
        json value;
        file >> value;
        file.close();
        return value;
    }

    bool remove(const std::string& key) {
        return std::remove((m_path + "/" + key + ".json").c_str()) == 0;
    }

private:
    std::string m_path;
};

int main() {
    JSONDatabase db("database");

    // Insert data into the database
    json john = {{"name", "John"}, {"age", 30}, {"city", "New York"}};
    db.insert("john", john);

    // Retrieve data from the database
    json jane = db.select("jane");
    std::cout << jane << std::endl;

    // Remove data from the database
    db.remove("john");

    return 0;
}
