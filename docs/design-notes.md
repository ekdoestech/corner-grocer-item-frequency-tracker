# Design Notes – Corner Grocer Frequency Tracker

## Problem

The Corner Grocer needs a way to analyze daily grocery transaction records in order to understand how frequently items are purchased. This information supports decisions related to produce layout optimization and inventory restocking.

The challenge is not just counting items, but presenting the data in a way that is reliable, readable, and actionable for users.

---

## Development Environment (VS Code)

This project was developed using Visual Studio Code as the primary IDE.

- Source files were organized into separate header (.h) and implementation (.cpp) files to support clean builds and maintainability.
- VS Code’s integrated terminal was used to compile and run the application, enabling quick iteration and debugging.
- IntelliSense and compiler diagnostics helped identify syntax errors, missing includes, and type mismatches early in development.
- The project structure mirrors common industry layouts, making it easy to navigate and extend.
Using VS Code reinforced best practices for managing multi-file C++ projects in a modern development environment.

---

## Approach

- Used a `std::map` to efficiently track item frequencies while ensuring unique keys and ordered output
- Applied separation of concerns by isolating data processing logic (GroceryTracker) from user interaction (main.cpp)
- Normalized item input to support case-insensitive and user-friendly searches
- Processed all transaction data once at program startup to ensure consistent and fast menu operations

This approach results in a maintainable design that balances efficiency with clarity.

---

## Key Design Decisions

- **Use of `std::map` for frequency tracking**  
  Chosen for its ability to associate item names with counts while maintaining alphabetical order, improving output readability and consistency across reports.

- **File-based input and output**  
  Simulates real-world data ingestion and persistence. The program reads raw transaction data from a text file and creates a backup file (frequency.dat) to store processed results.

- **Menu-driven interface**  
  Provides a clear and intuitive user experience, allowing users to interact with the data without needing to understand the internal implementation.

- **Constructor-based dependency injection**  
  The input file name is passed into the GroceryTracker constructor, improving flexibility and decoupling data sources from processing logic.

---

## Lessons Learned

- Managing multi-file C++ projects requires careful coordination between header and implementation files
- Centralizing configuration values and file paths improves maintainability and reduces errors
- Defensive programming practices such as input validation and file state checks significantly improve program reliability
- Clear project organization and descriptive naming conventions make debugging and future enhancements easier
- Using an IDE with strong diagnostics (such as VS Code) improves development efficiency and code quality

---

## Design Outcome

The final solution transforms raw transaction logs into actionable inventory insights. By combining efficient data structures, robust file handling, and a user-centered interface, the application meets all functional requirements while demonstrating industry-aligned coding practices within a modern development environment.
