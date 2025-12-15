#ifndef GROCERYTRACKER_H
#define GROCERYTRACKER_H

#include <map>
#include <string>

/*
 * GroceryTracker
 * ----------------
 * Reads a daily grocery transaction file and tracks the frequency
 * of each item purchased.
 *
 * Purpose:
 * - Transforms raw transaction data into actionable inventory insights
 * - Supports layout and restocking decisions for the Corner Grocer
 *
 * Responsibilities:
 * - Load and process input data into a frequency map
 * - Create a backup file (frequency.dat)
 * - Provide reporting functions (counts, histogram)
 * - Provide insight functions (top movers, demand levels, health score)
 */
class GroceryTracker {
public:
    // Inventory classification based on purchase frequency
    enum class DemandLevel { LOW, MED, HIGH };

    /*
     * Constructor
     * ------------
     * Reads the input file, counts item frequencies,
     * and creates a backup file named frequency.dat.
     *
     * Dependency Injection:
     * - Input file name is supplied by main(), improving flexibility
     */
    GroceryTracker(const std::string& inputFileName);

    // Returns true if all data was loaded and written successfully
    bool IsDataReady() const { return m_dataReady; }

    // Enable or disable optional ANSI color output
    void SetUseColor(bool enable) { m_useColor = enable; }

    // Menu Option 1
    int GetItemFrequency(const std::string& item) const;

    // Menu Option 2
    void PrintAllFrequencies() const;

    // Menu Option 3
    void PrintHistogram() const;

    // Insight / Creative Features
    void PrintDataLoadSummary() const;
    void PrintTopMovers() const;
    void PrintDemandClassification() const;
    void PrintInventoryHealth() const;
    void PrintRestockSummary() const;

    // Summary metrics
    int GetRestockItemCount() const;
    int GetTotalTransactions() const;
    int GetUniqueItemCount() const;
    int GetHealthScorePercent() const;

private:
    // std::map is used to ensure deterministic, alphabetical output,
    // improving readability and consistency across reports
    std::map<std::string, int> itemFrequency;

    // Backup file name constant (avoids magic strings)
    static constexpr const char* BACKUP_FILE_NAME = "frequency.dat";

    // Indicates whether constructor completed successfully
    bool m_dataReady;

    // Optional ANSI color output
    bool m_useColor;

    // Utility helpers
    static std::string NormalizeItem(std::string s);
    static DemandLevel ClassifyDemand(int frequency);
    static const char* DemandLabel(DemandLevel level);
    static const char* DemandColorCode(DemandLevel level);
    static void PrintHeader(const std::string& title);
};

#endif // GROCERYTRACKER_H
