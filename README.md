# 🕸️ Social Network Graph Analyzer

![C](https://img.shields.io/badge/C-99%25-blue?style=flat-square&logo=c)
![Data Structures](https://img.shields.io/badge/Data_Structures-Graphs-orange?style=flat-square)
![Algorithms](https://img.shields.io/badge/Algorithms-Tarjan_%26_BFS-red?style=flat-square)

A robust Command Line Interface (CLI) tool written in C to parse, manage, and analyze directed networks representing social connections using Adjacency Lists.

This project focuses on dynamic memory management, graph theory, and First-Class Abstract Data Types.

---

## 🚀 Technical Highlights
- **Community Detection:** Implements **Tarjan's Algorithm** utilizing Depth-First Search (DFS) and low-link values to identify Strongly Connected Components (isolated network bubbles).
- **Recommendation Engine:** Uses Triadic Closure logic to suggest new friend connections based on the number of mutual followers.
- **Degrees of Separation:** Implements Breadth-First Search (BFS) using a custom opaque FIFO Queue to find the shortest path between any two users in the network.
- **Memory Safety:** Completely memory-leak free, strictly managing pointer allocations and opaque structures.

---

## 💻 Usage & Compilation

Compile the project using CMake or standard GCC:

```bash
# Compile the source code
gcc -Wall -Wextra -o social_analyzer main.c Graph.c queue.c

# Run the executable with the provided network file
./social_analyzer input.txt
```

---

## 📊 Example Output

```console
$ ./social_analyzer input.txt
Loading Social Network from input.txt...
Graph loaded successfully!

--- INFLUENCER ANALYSIS ---
The most followed user on the social media is 2

--- DEGREES OF SEPARATION (BFS) ---
The minimum distance from 0 to 4 is 3
The minimum distance from 1 to 0 is 2

--- RECOMMENDATION ENGINE ---
 -> We recommend user 3 to user 0 (2 mutual connections)
 -> We recommend user 3 to user 6 (1 mutual connections)

--- COMMUNITY DETECTION (Tarjan's SCC) ---
 -> Community 1: [ 1 5 4 3 2 0 ]
 -> Community 2: [ 6 ]

Memory freed. Program completed successfully.
```
