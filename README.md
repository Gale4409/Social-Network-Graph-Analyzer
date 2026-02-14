# Social Network Graph Analyzer

A robust Command Line Interface (CLI) tool written in standard C to analyze directed graphs representing social network connections. 

This project was built to demonstrate proficiency in raw memory management, opaque pointers (ADTs), and fundamental graph algorithms.

## 🚀 Features
- **Dynamic Memory Management:** Completely free of memory leaks (Valgrind tested).
- **Opaque Pointer ADT:** Implements a custom Queue data structure completely encapsulated and hidden from the main program to handle BFS operations cleanly.
- **Graph Representation:** Uses an Adjacency List to efficiently handle large, sparse networks without wasting RAM.
- **Influencer Detection:** Calculates the maximum in-degree node efficiently.
- **Degrees of Separation:** Uses Breadth-First Search (BFS) to find the shortest path between any two users in the network.

## 🛠️ Technical Implementation
- **Language:** C99
- **Build System:** CMake (or standard GCC)
- **Data Structures:** Adjacency Lists, Linked Lists, Custom FIFO Queue.

## 💻 How to Run
Clone the repository and compile using CMake, or simply compile via GCC:

```bash
gcc -Wall -Wextra -o social_analyzer main.c Graph.c queue.c
