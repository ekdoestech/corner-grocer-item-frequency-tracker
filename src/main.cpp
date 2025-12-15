#include <iostream>
#include <limits>
#include <string>

#include "GroceryTracker.h"

// Display user menu
void DisplayMenu() {
    std::cout << "\n===== Corner Grocer Menu =====\n"
              << "1. Search for an item\n"
              << "2. Display all item frequencies\n"
              << "3. Display histogram and insights\n"
              << "4. Exit\n"
              << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");

    if (!tracker.IsDataReady()) {
        std::cerr << "Fatal error: Data could not be loaded.\n";
        return 1;
    }

    char colorChoice;
    std::cout << "Enable color-coded output? (Y/N): ";
    std::cin >> colorChoice;
    tracker.SetUseColor(colorChoice == 'Y' || colorChoice == 'y');

    tracker.PrintDataLoadSummary();

    int choice = 0;
    std::string lastSearch;

    do {
        DisplayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

        case 1: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!lastSearch.empty()) {
                std::cout << "Last searched item: " << lastSearch << "\n";
            }

            std::string item;
            std::cout << "Enter item name to search: ";
            std::getline(std::cin, item);

            int count = tracker.GetItemFrequency(item);
            if (count > 0) {
                std::cout << item << " was purchased "
                          << count << " times.\n";
                lastSearch = item;
            } else {
                std::cout << "Item not found.\n";
            }
            break;
        }

        case 2:
            tracker.PrintAllFrequencies();
            break;

        case 3: // Histogram + insights
            tracker.PrintHistogram();

            // Explicit business insight section (exceeds base requirements)
            std::cout << "\n===== Business Insights =====\n";
            tracker.PrintTopMovers();
            tracker.PrintInventoryHealth();
            tracker.PrintRestockSummary();
            break;

        case 4:
            std::cout << "\nExiting program...\n";
            break;

        default:
            std::cout << "Invalid menu option.\n";
        }

    } while (choice != 4);

    std::cout << "\n===== Session Summary =====\n";
    std::cout << "Items requiring restock: "
              << tracker.GetRestockItemCount() << "\n";
    std::cout << "Inventory health score:  "
              << tracker.GetHealthScorePercent() << "%\n";
    std::cout << "Thank you for using Corner Grocer.\n";

    // Final business recommendation based on demand analysis
    if (tracker.GetRestockItemCount() > 0) {
        std::cout << "Recommendation: Prioritize restocking and prominent "
                << "placement of HIGH-demand items to prevent stockouts. "
                << "Consider reducing shelf space for LOW-demand items.\n";
    } else {
        std::cout << "Recommendation: Demand levels are balanced. "
                << "Maintain current restocking strategy and layout.\n";
    }


    return 0;
}
