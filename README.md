# Corner Grocer Item Frequency Tracker

A C++ console application that analyzes daily grocery transaction records and reports item purchase frequencies along with actionable inventory insights.

Built as part of **CS-210: Programming Languages** at Southern New Hampshire University.

---

## Project Highlights

- Modular C++ application using STL containers to analyze transactional data
- Automated data backup and case-insensitive item lookup
- Business-focused insights such as inventory health and restock recommendations

---

## Overview

The Corner Grocer Item Frequency Tracker reads a text file containing grocery items purchased throughout the day and transforms raw transaction data into frequency-based summaries and inventory insights.

The program allows users to:

- Look up how often a specific item was purchased
- View all item frequencies
- Display a text-based histogram
- Review inventory health and restock recommendations
- Automatically generate a backup data file

This project demonstrates foundational and intermediate C++ concepts, including object-oriented design, file I/O, standard library containers, and defensive programming.

---

## Technologies Used

- **Language:** C++
- **Concepts:**  
  - Object-Oriented Programming  
  - File I/O  
  - STL `std::map`  
  - Input validation  
  - Data normalization (case-insensitive lookup)
- **Tools:**  
  - Visual Studio / VS Code  
  - MSVC Compiler (`cl.exe`)

---

## Program Design

The application is structured around a dedicated `GroceryTracker` class that encapsulates all data-processing and analysis logic.

### Key Design Decisions

- `std::map<std::string, int>` is used for frequency tracking to ensure unique keys and deterministic, alphabetical output
- Item names are normalized to lowercase to support user-friendly, case-insensitive searches
- Separated concerns between:
  - Data processing and analytics (`GroceryTracker`)
  - User interaction and control flow (`main.cpp`.) 
  
  This design improves readability, maintainability, and extensibility.
---

## Features

### Menu Options

1. Look up the frequency of a specific item  
2. Display all item frequencies  
3. Display a histogram and business insights  
4. Exit the program  

### Business & Usability Enhancements

- Inventory health scoring based on demand levels
- Identification of most- and least-purchased items
- Restock and shelf-space recommendations
- Automatic generation of `frequency.dat` as a backup file
- Input validation to prevent invalid menu selections

---

## File Breakdown

| File | Purpose |
|------|---------|
| `src/main.cpp` | Program entry point and menu logic |
| `src/GroceryTracker.h` | GroceryTracker class definition |
| `src/GroceryTracker.cpp` | GroceryTracker class implementation |
| `data/CS210_Project_Three_Input_File.txt` | Input transaction data |
| `output/frequency.dat` | Generated output file containing item frequencies |

---

## How to Run

### Compile (MSVC)

```bash
cl src/main.cpp src/GroceryTracker.cpp /Fe:CornerGrocer.exe
```

### Run

```bash
CornerGrocer.exe
```

---

## Example Output

```bash
===== Purchase Frequency Histogram =====
apples ******** [HIGH]
cranberries ********** [HIGH]
limes * [LOW]

===== Inventory Health =====
Inventory Health Score: 70% (Moderate)

===== Restock Recommendations =====
- limes (LOW stock)
```

*Note: Item lookup is case-insensitive for improved user experience.*

---

## Screenshots

**Program Startup and Data Load Summary**  
![Program Startup and Data Load](screenshots/Program%20Startup%20and%20Data%20Load.png)

**Histogram and Business Insights Output**  
![Histogram and Insights](screenshots/Histogram.png)

---

## Learning Outcomes

This project demonstrates:

- Professional C++ class design
- Safe and defensive file handling
- Effective use of standard library containers
- Clean separation of responsibilities
- Translating raw data into actionable business insights

---

## License

This project is provided for educational and portfolio use.

---
