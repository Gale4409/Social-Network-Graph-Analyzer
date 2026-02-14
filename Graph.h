#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct graph *G;

typedef struct {
    int v; int w;
} Edge;

G GRAPHinit (int V);
G GRAPHload (FILE *input);
void GRAPHinsertE (G graph, Edge e);
void GRAPHmost_followed_influencer (G graph); //display of the "best" influencer
void GRAPHfind_path (G graph, int start, int stop); //find the best path between two people on the social media, to see how they are connected
void GRAPHfree (G graph);

#endif