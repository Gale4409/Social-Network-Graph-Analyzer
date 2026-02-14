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
    GRAPHfind_path(myGraph, 0, 4);
    GRAPHfind_path(myGraph, 6, 5);
    GRAPHfind_path(myGraph, 1, 0);
    GRAPHfind_path(myGraph, 4, 6);

    printf("\n--- INFLUENCER ANALYSIS ---\n");
    GRAPHmost_followed_influencer(myGraph);

    printf("\n--- DEGREES OF SEPARATION (BFS) ---\n");
    GRAPHfind_path(myGraph, 0, 4);
    GRAPHfind_path(myGraph, 1, 0);

    printf("\n--- RECOMMENDATION ENGINE ---\n");
    GRAPHrecommend_friends(myGraph, 0); // Cerchiamo amici da suggerire all'utente 0
    GRAPHrecommend_friends(myGraph, 6); // Cerchiamo amici da suggerire all'utente 6

    printf("\n--- COMMUNITY DETECTION (Tarjan's SCC) ---\n");
    GRAPHfind_SCCs(myGraph);

    GRAPHfree(myGraph);
    printf("\nMemory freed. Program completed successfully.\n");

    return 0;
}