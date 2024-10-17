# Overview

This project contains implementations of six data structures and six sorting algorithms, located in the `/DS` and `/Algorithms` directories respectively, each one fully unit tested using the Catch2 framework.

I may continue working on this project, as there are plenty of additional things I could do to improve the project, such as adding more algorithms/DS, benchmark testing the computational efficiency of algorithms, or adding error handling, which would allow me to implement proper bounds checking and flesh out the unit tests even more.

**Data structure implementations:**
- Array (static and dynamic)
- Stack
- Queue (circular buffer)
- Linked List (singly)
- Hashmap (Linear Probing Collision Handling)
- BST (w/ AVL self-balancing)

**Sorting algorithm implementations:**
- Bubble sort
- Insertion sort
- Selection sort
- Shell sort
- Merge sort
- Quick sort

## Dependencies
- CMake 3.26.3 or higher
- Make
- gcc

## Build, Execution, Usage

Within the folder of a given implementation lies the `/src` directory containing the source code along with a `test.cpp`, and a `/build` directory that is empty by default.

To build an implementation, enter its `/build` directory and run `cmake ..`. Once CMake finishes generating the build files, run `make`. From there you can run the binary `./tests` to execute the unit tests. Run `./tests -s` for verbose output if you want to see the individual unit tests passing.

Ex:
```bash

# Enter build directory of BST implementation
cd DS/BST/build

# Generate build files
cmake ..

# Generate executable
make

# Run Unit Tests
./tests
```

Feel free to view the `test.cpp` and other source files of any DS/algorithm to better understand its interface, functionality, and implementation!
