# Fibonacci Heap Implementation

A C-based implementation of a Fibonacci Heap demonstrating core priority queue operations through an interactive, menu-driven program.

## Overview

This project implements a Fibonacci Heap using dynamically allocated nodes and circular doubly linked lists. It provides a practical demonstration of heap operations and the supporting procedures used to maintain the heap structure.

## Features

- **Insert:** Add a key to the heap.
- **Extract Minimum:** Remove and return the minimum key.
- **Decrease Key:** Lower the key of a selected node.
- **Delete Node:** Remove a node identified by its key.
- **Find Node:** Search for a node by key.
- **Display Heap:** Display the root nodes and their descendants.

## Implementation

The source code includes supporting procedures for:

- Consolidating roots of equal degree
- Linking trees
- Cutting nodes from their parents
- Performing cascading cuts

The program uses a console menu to let users select and perform operations.

## Technologies

- C
- Standard C libraries

## Repository Contents

- `fibonacci_heap.c` — Source code for the Fibonacci Heap implementation.
- `Lab_Report_CSE207.pdf` — Project report (if included in the repository).

## How to Run

1. Make sure a C compiler such as GCC is installed.
2. Compile the source file:

   ```bash
   gcc fibonacci_heap.c -o fibonacci_heap
   ```

3. Run the program:

   ```bash
   ./fibonacci_heap
   ```

   On Windows, run `fibonacci_heap.exe`.

## Academic Context

- **Course:** CSE207 — Data Structure
- **Project:** Implementation of Fibonacci Heap
- **Institution:** East West University

## Authors

- Shawna Akter
- Tabassum Nahar Yeah

---

*Academic project demonstrating the implementation and use of a Fibonacci Heap in C.*
