#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main() {
    std::ifstream inputFile("CS210_Project_Three_Input_File.txt");

    if (!inputFile.is_open()) {
        std::cout << "Error: Could not open input file." << std::endl;
        return 1;
    }

    std::map<std::string, int> itemFrequency;
    std::string item;

    while (std::getline(inputFile, item)) {
        itemFrequency[item]++;
    }

    inputFile.close();

    std::cout << "Item Frequencies:" << std::endl;

    for (const auto& pair : itemFrequency) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    return 0;
}
