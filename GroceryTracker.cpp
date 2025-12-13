#include "GroceryTracker.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cerrno>

GroceryTracker::GroceryTracker(const std::string& inputFileName) {
    _isDataReady = false;
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << inputFileName
                  << " (" << std::strerror(errno) << ")" << std::endl;
        return;
    }

    std::string item;
    while (std::getline(inputFile, item)) {
        itemFrequency[item]++;
    }

    inputFile.close();

    std::ofstream outFile("frequency.dat");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file: frequency.dat"
                  << " (" << std::strerror(errno) << ")" << std::endl;
        return;
    }       
    for (const auto& pair : itemFrequency) {
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
    _isDataReady = true;

    std::cout << "Data file loaded and frequency.dat created successfully." << std::endl;
}

bool GroceryTracker::isDataReady() const {
    return _isDataReady;
}
