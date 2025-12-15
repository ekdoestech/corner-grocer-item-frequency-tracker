#include "GroceryTracker.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>

// ---------- Utility Helpers ----------

std::string GroceryTracker::NormalizeItem(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());

    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });

    return s;
}

GroceryTracker::DemandLevel GroceryTracker::ClassifyDemand(int frequency) {
    if (frequency <= 3) return DemandLevel::LOW;
    if (frequency <= 5) return DemandLevel::MED;
    return DemandLevel::HIGH;
}

const char* GroceryTracker::DemandLabel(DemandLevel level) {
    switch (level) {
        case DemandLevel::LOW:  return "[LOW]";
        case DemandLevel::MED:  return "[MED]";
        case DemandLevel::HIGH: return "[HIGH]";
        default: return "";
    }
}

const char* GroceryTracker::DemandColorCode(DemandLevel level) {
    switch (level) {
        case DemandLevel::LOW:  return "\033[31m";
        case DemandLevel::MED:  return "\033[33m";
        case DemandLevel::HIGH: return "\033[32m";
        default: return "\033[0m";
    }
}

void GroceryTracker::PrintHeader(const std::string& title) {
    std::cout << "\n" << title << "\n"
              << std::string(title.length(), '-') << "\n";
}

// ---------- Constructor ----------

GroceryTracker::GroceryTracker(const std::string& inputFileName)
    : m_dataReady(false), m_useColor(false)
{
    std::ifstream inFile(inputFileName);
    if (!inFile) {
        std::cerr << "Error: Could not open input file: "
                  << inputFileName << "\n";
        return;
    }

    std::string item;
    while (inFile >> item) {
        itemFrequency[NormalizeItem(item)]++;
    }
    inFile.close();

    std::ofstream outFile(BACKUP_FILE_NAME);
    if (!outFile) {
        std::cerr << "Error: Could not create backup file ("
                  << BACKUP_FILE_NAME
                  << "). Check file permissions or disk space.\n";
        return;
    }

    for (const auto& entry : itemFrequency) {
        outFile << entry.first << " " << entry.second << "\n";
    }

    outFile.flush();
    if (!outFile.good()) {
        std::cerr << "Error: Failed while writing to backup file ("
                  << BACKUP_FILE_NAME << ").\n";
        return;
    }

    outFile.close();
    m_dataReady = true;
}

// ---------- Menu Functions ----------

int GroceryTracker::GetItemFrequency(const std::string& item) const {
    auto it = itemFrequency.find(NormalizeItem(item));
    return (it != itemFrequency.end()) ? it->second : 0;
}

void GroceryTracker::PrintAllFrequencies() const {
    PrintHeader("All Item Frequencies");
    for (const auto& pair : itemFrequency) {
        std::cout << std::left << std::setw(14)
                  << pair.first << pair.second << "\n";
    }
}

void GroceryTracker::PrintHistogram() const {
    PrintHeader("Purchase Frequency Histogram");

    for (const auto& pair : itemFrequency) {
        DemandLevel level = ClassifyDemand(pair.second);

        if (m_useColor) std::cout << DemandColorCode(level);

        std::cout << std::left << std::setw(14) << pair.first
                  << std::string(pair.second, '*') << " "
                  << DemandLabel(level);

        if (m_useColor) std::cout << "\033[0m";
        std::cout << "\n";
    }
}

// ---------- Insight Features ----------

void GroceryTracker::PrintDataLoadSummary() const {
    PrintHeader("Data Load Summary");
    std::cout << "Transactions processed: "
              << GetTotalTransactions() << "\n";
    std::cout << "Unique items tracked:   "
              << GetUniqueItemCount() << "\n";
    std::cout << "Backup file created:    "
              << BACKUP_FILE_NAME << "\n";
}

void GroceryTracker::PrintTopMovers() const {
    if (itemFrequency.empty()) return;

    auto minIt = itemFrequency.begin();
    auto maxIt = itemFrequency.begin();

    for (const auto& pair : itemFrequency) {
        if (pair.second < minIt->second) minIt = itemFrequency.find(pair.first);
        if (pair.second > maxIt->second) maxIt = itemFrequency.find(pair.first);
    }

    PrintHeader("Top Movers");
    std::cout << "Most Purchased:  " << maxIt->first
              << " (" << maxIt->second << ")\n";
    std::cout << "Least Purchased: " << minIt->first
              << " (" << minIt->second << ")\n";
}

void GroceryTracker::PrintDemandClassification() const {
    PrintHeader("Demand Classification");
    for (DemandLevel level : {DemandLevel::HIGH, DemandLevel::MED, DemandLevel::LOW}) {
        std::cout << DemandLabel(level) << " demand:\n";
        for (const auto& pair : itemFrequency) {
            if (ClassifyDemand(pair.second) == level) {
                std::cout << " - " << pair.first << "\n";
            }
        }
    }
}

void GroceryTracker::PrintInventoryHealth() const {
    PrintHeader("Inventory Health");
    int score = GetHealthScorePercent();
    std::cout << "Inventory Health Score: "
              << score << "% ";

    if (score >= 80) std::cout << "(Good)\n";
    else if (score >= 50) std::cout << "(Moderate)\n";
    else std::cout << "(Critical)\n";
}

void GroceryTracker::PrintRestockSummary() const {
    PrintHeader("Restock Recommendations");
    bool needsAction = false;

    for (const auto& pair : itemFrequency) {
        if (ClassifyDemand(pair.second) == DemandLevel::LOW) {
            std::cout << "- " << pair.first << " (LOW stock)\n";
            needsAction = true;
        }
    }

    if (!needsAction) {
        std::cout << "All items are sufficiently stocked.\n";
    }
}

// ---------- Metrics ----------

int GroceryTracker::GetRestockItemCount() const {
    int count = 0;
    for (const auto& pair : itemFrequency) {
        if (ClassifyDemand(pair.second) == DemandLevel::LOW) count++;
    }
    return count;
}

int GroceryTracker::GetTotalTransactions() const {
    int total = 0;
    for (const auto& pair : itemFrequency) total += pair.second;
    return total;
}

int GroceryTracker::GetUniqueItemCount() const {
    return static_cast<int>(itemFrequency.size());
}

int GroceryTracker::GetHealthScorePercent() const {
    if (itemFrequency.empty()) return 0;
    int healthy = 0;
    for (const auto& pair : itemFrequency) {
        if (pair.second > 3) healthy++;
    }
    return static_cast<int>(
        (static_cast<double>(healthy) / itemFrequency.size()) * 100
    );
}
