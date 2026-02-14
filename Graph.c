#include "Graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    int v; link next;
};

struct graph {
    int V; int E;
    link *ladj;
};

static Edge EDGEcreate (int v, int w) {
    Edge e = {v, w};
    return e;
}

static link newnode (int v, link next) {
    link x = malloc (sizeof(struct node));
    if (x == NULL) return NULL;
    x->next = next; x->v = v;
    return x;
}

void GRAPHinsertE (G graph, Edge e) {
    if (graph == NULL) return;
    //i'll insert in the head of the list:
    graph->ladj[e.v] = newnode (e.w, graph->ladj[e.v]);
    graph->E++;
}

G GRAPHinit (int V) {
    G graph = malloc (sizeof(struct graph));
    if (graph ==  NULL) return NULL;
    graph->V = V;
    graph->E = 0;
    graph->ladj = calloc (V, sizeof(link));
    if (graph->ladj == NULL) { free(graph); return NULL; }
    return graph;
}

G GRAPHload (FILE *input) {
    if (input == NULL) return NULL;
    int V;
    fscanf (input, "%d %*d", &V);
    if (V <= 0) return NULL;
    G graph = GRAPHinit(V);
    if (graph == NULL) return NULL;
    int v, w;
    while (fscanf(input, "%d %d", &v, &w) == 2) {
        GRAPHinsertE(graph, EDGEcreate(v, w)); //creation of the hedge and inserction into the graph!
    }
    return graph;
}

static int find_max (int *v, int len) { //return the position on the array where is located the max value!
    if (v == NULL || len<=0) return -1;
    int i, pos_max=0;
    for (i=1; i<len; i++) {
        if (v[i] > v[pos_max]) pos_max = i;
    }
    return pos_max;
}

void GRAPHmost_followed_influencer (G graph) { //i'll check the in_degree of each person and then find the most followed one
    if (graph == NULL) return;
    int *in_degree = calloc (graph->V, sizeof(int));
    if (in_degree == NULL) return;
    //to calculate the in_degree i will iterate in each list to update the edges from one to another
    int i;
    for (i=0; i<graph->V; i++) {
        link x;
        for (x=graph->ladj[i]; x!=NULL; x=x->next) in_degree [x->v]++;
    }
    int pos_max = find_max (in_degree, graph->V);
    printf ("\nThe most followed people on the social media is %d\n", pos_max);
    free (in_degree);
}

void GRAPHfind_path (G graph, int start, int stop) {
    if (graph == NULL || start >= graph->V || start < 0 || stop >= graph->V || stop < 0) return;
    int *dist = malloc (graph->V*sizeof(int));
    if (dist == NULL) return;
    int i;
    for (i=0; i<graph->V; i++) dist[i] = -1;
    Queue q = Qinit();
    dist[start] = 0;
    Qput(q, start);
    int find = 0;
    while (!QisEmpty(q)) {
        int w = Qget (q);
        if (find) break;
        link x;
        for (x=graph->ladj[w]; x!=NULL && !find; x=x->next) {
            if (dist[x->v] != -1) continue;
            if (x->v == stop) find = 1;
            dist[x->v] = dist[w] + 1;
            Qput (q, x->v);
        }
    }
    printf ("\nThe minimum distance from %d to %d is %d\n", start, stop, dist[stop]);
    Qfree(q);
    free(dist);
}

void GRAPHfree (G graph) {
    if (graph == NULL) return;
    //free of the ladj:
    int i;
    for (i=0; i<graph->V; i++) {
        link x = graph->ladj[i], tmp = NULL;
        while (x != NULL) {
            tmp = x->next;
            free(x);
            x = tmp;
        }
    }
    free(graph->ladj);
    free(graph);
}