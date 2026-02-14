#include <stdio.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <network_file.txt>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    printf("Loading Social Network from %s...\n", argv[1]);
    G myGraph = GRAPHload(fp);
    fclose(fp);

    if (myGraph == NULL) {
        printf("Error: Failed to load the graph structure.\n");
        return 1;
    }
    printf("Graph loaded successfully!\n");

    printf("\n--- INFLUENCER ANALYSIS ---");
    GRAPHmost_followed_influencer(myGraph);

    printf("\n--- DEGREES OF SEPARATION (BFS) ---");
    GRAPHfind_path(myGraph, 0, 4); // Percorso: 0 -> 2 -> 3 -> 4 (Distanza: 3)
    GRAPHfind_path(myGraph, 6, 5); // Percorso: 6 -> 2 -> 3 -> 4 -> 5 (Distanza: 4)
    GRAPHfind_path(myGraph, 1, 0); // Percorso: 1 -> 5 -> 0 (Distanza: 2)
    GRAPHfind_path(myGraph, 4, 6); // Ritornerà che non c'è percorso (il 6 non ha frecce in entrata)

    GRAPHfree(myGraph);
    printf("\nMemory freed. Program completed successfully.\n");

    return 0;
}