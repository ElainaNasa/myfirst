# Student Grade Management System

A modular C program for managing student grades with comprehensive functionality.

## Features

1. **Student Record Management**
   - Add new student records
   - Search students by name or ID
   - Modify existing student information
   - Delete student records

2. **Grade Calculations**
   - Calculate total and average scores for each student
   - Calculate average scores for each course

3. **Sorting and Analysis**
   - Sort students by course scores (descending order)
   - Statistical analysis with grade distribution (Excellent, Good, Medium, Pass, Fail)

4. **File Operations**
   - Save/load data to/from text files
   - Save/load data to/from binary files

## Project Structure

```
lab4/
├── student.h          # Structure definitions and global variables
├── student.c          # Student data initialization
├── fileop.h          # File operation function declarations
├── fileop.c          # Text and binary file I/O implementation
├── sort.h            # Sorting function declarations
├── sort.c            # Sorting algorithms implementation
├── print.h           # Printing function declarations
├── print.c           # Display functions implementation
├── calculate.h       # Calculation function declarations
├── calculate.c       # Score calculation functions
├── analysis.h        # Analysis function declarations
├── analysis.c        # Statistical analysis functions
├── search.h          # Search function declarations
├── search.c          # Search algorithms implementation
├── main.c           # Main program with menu system
├── Makefile         # Build configuration
└── README.md        # This file
```

## Compilation

### Method 1: Compile all source files together
```bash
make all
```

### Method 2: Compile object files separately (as required)
```bash
make build_with_objects
```

### Method 3: Manual compilation
```bash
# Compile all source files
gcc -Wall -Wextra -std=c99 -g -o grade_management *.c

# Or compile object files separately
gcc -Wall -Wextra -std=c99 -g -c student.c
gcc -Wall -Wextra -std=c99 -g -c fileop.c
gcc -Wall -Wextra -std=c99 -g -c sort.c
gcc -Wall -Wextra -std=c99 -g -c print.c
gcc -Wall -Wextra -std=c99 -g -c calculate.c
gcc -Wall -Wextra -std=c99 -g -c analysis.c
gcc -Wall -Wextra -std=c99 -g -c search.c
gcc -Wall -Wextra -std=c99 -g -o grade_management main.c student.o fileop.o sort.o print.o calculate.o analysis.o search.o
```

## Usage

1. Run the program:
```bash
./grade_management
```

2. Follow the menu prompts:
   - 1: Add student records
   - 2: Search by name
   - 3: Search by ID
   - 4: Modify student by ID
   - 5: Delete student by ID
   - 6: Calculate student totals and averages
   - 7: Calculate course averages
   - 8: Sort by course scores
   - 9: Statistical analysis
   - 10: Save to text file
   - 11: Load from text file
   - 12: Save to binary file
   - 13: Load from binary file
   - 0: Exit

## File Formats

### Text File Format
```
ID                   name       iCS     PDP      DS      DL
2021111007           wang7      97.5    90.0    88.9    70.0
2021111008           wang8      98.5    80.0    89.9    91.0
```

### Binary File Format
- First 4 bytes: number of student records (int)
- Subsequent data: STUDENT structures

## Error Handling

The program includes comprehensive error handling using `errno` and `strerror()` to provide meaningful error messages for file operations and other potential failures.

## Requirements Met

- ✅ Modular design with separate .h and .c files
- ✅ File operation module (fileop.h/c)
- ✅ Sorting module (sort.h/c)
- ✅ Separate modules for printing, calculation, analysis, and search
- ✅ Main program calling all modules
- ✅ Two compilation methods supported
- ✅ Comprehensive error handling
- ✅ Support for text and binary file formats
- ✅ All required functionality implemented
