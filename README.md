# Industry-Oriented Library Management System (C / DSA)

A modular console application written in C to manage library operations, borrowing requests, and transactional history. This project demonstrates computer science fundamentals, modular C programming, file handling, dynamic memory management, and data structures and algorithms.

---

## Project Overview

This capstone project implements a Library Management System designed around real-world data management challenges. It replaces simple linear lookups with optimized tree traversal and uses standard linear structures for sequential request handling and action reversal.

### Key Technical Objectives
- Data Structures: Binary Search Tree (BST), Dynamic Linked Stack, FIFO Queue.
- Memory Management: Dynamic allocation and clean heap deallocation using malloc and free.
- Persistence: File storage using standard C file IO.
- Algorithmic Efficiency: Optimized logarithmic average lookup, insertion, and deletion times.

---

## Data Structures and Core Concepts Implemented

1. Binary Search Tree (BST): Used for core record storage. Allows quick search, insertion, and deletion operations indexed by unique Book IDs.
2. In-Order Traversal: Recursive tree traversal used to display all catalog records in ascending numerical order.
3. Dynamic Stack (LIFO): Tracks user actions to support operational undo functionalities.
4. Linear Queue (FIFO): Queue system to process pending book requests sequentially in order of arrival.
5. Recursion: Applied across tree search, node insertion, deletion, data serialization, and catalog reporting.
6. File Handling: Serializes memory state to sample-data/library_data.txt upon exit and reloads on system boot.

---

## Project Directory Structure

Library-Management-System/
├── src/
│   └── library.c
├── include/
│   └── library.h
├── docs/
│   └── report_notes.txt
├── report/
│   └── Capstone_Project_Report.pdf
├── presentation/
│   └── Project_Presentation.pptx
├── screenshots/
│   ├── menu_output.png
│   └── bst_search_output.png
├── sample-data/
│   └── library_data.txt
├── README.md
├── LICENSE
├── Makefile
└── main.c

---

## Getting Started

### Prerequisites
- GCC Compiler (gcc) installed.
- Make utility (make).

### Compilation
Build the project executable using the provided Makefile:

make

### Execution
Run the compiled binary:
gcc -Iinclude main.c src/library.c -o library_app

.\library_app.exe

./library_app

### Clean Up
Remove generated object files and executables:

make clean

---

## Time and Space Complexity Analysis

- Search Record (Binary Search Tree):
  - Average Time: O(log N)
  - Worst-Case Time: O(N)
  - Space Complexity: O(1)

- Insert Record (Binary Search Tree):
  - Average Time: O(log N)
  - Worst-Case Time: O(N)
  - Space Complexity: O(log N)

- Delete Record (Binary Search Tree):
  - Average Time: O(log N)
  - Worst-Case Time: O(N)
  - Space Complexity: O(log N)

- In-Order Display (Recursive BST):
  - Average Time: O(N)
  - Worst-Case Time: O(N)
  - Space Complexity: O(N)

- Queue Operations (Dynamic FIFO Queue):
  - Average Time: O(1)
  - Worst-Case Time: O(1)
  - Space Complexity: O(1)

- Undo Action (Dynamic LIFO Stack):
  - Average Time: O(1)
  - Worst-Case Time: O(1)
  - Space Complexity: O(1)

---

## Satisfied Requirements and User Stories

- US-01 and US-03 (CRUD Operations): System allows dynamic adding, updating, and deleting of book entries.
- US-02 and US-12 (BST Search): Lookup executes in logarithmic time using binary tree search algorithms.
- US-05 (Formatted Output): Catalog entries display in structured tabular format.
- US-06 (File Storage): Records automatically load from and save to disk.
- US-08 (Undo Feature): Action history maintained via a stack to reverse prior modifications.
- US-09 (Request Queue): Priority handling for student request processing follows strict FIFO rules.

---

## License

Distributed under the MIT License. See LICENSE for details.

---

## Project Members

- [Aman Kumar Choudhary] - Roll No: [2308101520005]

- [Bharat Singh Shahi] - Roll No: [2308101520016]

- [Manasvi] - Roll No: [2308101520025]
