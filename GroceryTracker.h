#ifndef GROCERYTRACKER_H
#define GROCERYTRACKER_H

#include <map>
#include <string>

class GroceryTracker {
    private:
        std::map<std::string, int> itemFrequency;
        bool _isDataReady;   
    
    public:
        // Constructor to initialize the tracker with data from a file
        GroceryTracker(const std::string& inputFileName);
        // Function to check if the data file was loaded successfully
        bool isDataReady() const { return isDataReady; }
};
#endif // GROCERYTRACKER_H