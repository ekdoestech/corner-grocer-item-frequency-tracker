# Architecture Overview

The Corner Grocer Item Frequency Tracker is designed as a small, modular C++ application with a clear separation between data processing and user interaction.

## Core Components

### GroceryTracker Class

The `GroceryTracker` class encapsulates all data-related responsibilities, including:

- Reading transaction data from an input file
- Normalizing item names for case-insensitive processing
- Tracking purchase frequencies using `std::map`
- Generating summary data and backup output files

This approach centralizes business logic and keeps analytics concerns isolated from user interface code.

### Main Application Flow

`main.cpp` is responsible for:

- Displaying the menu-driven interface
- Validating user input
- Delegating analytics requests to `GroceryTracker`
- Formatting and presenting output to the console

## Design Principles

- **Separation of Concerns:** Analytics and UI logic are intentionally decoupled
- **Deterministic Output:** Ordered STL containers ensure predictable reporting
- **Defensive Programming:** Input validation and file checks reduce runtime errors
- **Extensibility:** Additional analytics or output formats can be added with minimal refactoring

## Future Extension Ideas

- Configurable input/output paths
- CSV or JSON export support
- Unit testing for analytics logic
- Performance profiling for larger datasets
