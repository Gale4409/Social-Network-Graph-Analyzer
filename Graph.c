#include "Graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

void GRAPHrecommend_friends(G graph, int user) {
    if (graph == NULL || user < 0 || user >= graph->V) return;

    int *common_friends = calloc(graph->V, sizeof(int));
    int *already_following = calloc(graph->V, sizeof(int));
    if (common_friends == NULL || already_following == NULL) return;

    link x;
    for (x = graph->ladj[user]; x != NULL; x = x->next) {
        already_following[x->v] = 1;
    }
    already_following[user] = 1;

    for (x = graph->ladj[user]; x != NULL; x = x->next) {
        int friend = x->v;
        link y;
        for (y = graph->ladj[friend]; y != NULL; y = y->next) {
            int fof = y->v; // fof = Friend of Friend
            if (!already_following[fof]) {
                common_friends[fof]++;
            }
        }
    }

    int best_recommendation = -1;
    int max_common = 0;
    int i;
    for (i = 0; i < graph->V; i++) {
        if (common_friends[i] > max_common) {
            max_common = common_friends[i];
            best_recommendation = i;
        }
    }

    if (best_recommendation != -1) {
        printf(" -> We recommend user %d to user %d (%d mutual connections)\n", best_recommendation, user, max_common);
    } else {
        printf(" -> No new recommendations for user %d at the moment.\n", user);
    }

    free(common_friends);
    free(already_following);
}

static void SCCdfs(G graph, int w, int *pre, int *low, int *stack, int *top, int *onStack, int *time, int *scc_count) {
    pre[w] = (*time)++;
    low[w] = pre[w];
    stack[++(*top)] = w;
    onStack[w] = 1;

    link x;
    for (x = graph->ladj[w]; x != NULL; x = x->next) {
        int v = x->v;
        if (pre[v] == -1) {
            SCCdfs(graph, v, pre, low, stack, top, onStack, time, scc_count);
            low[w] = MIN(low[w], low[v]);
        } else if (onStack[v]) {
            low[w] = MIN(low[w], pre[v]);
        }
    }

    if (low[w] == pre[w]) {
        (*scc_count)++;
        printf(" -> Community %d: [ ", *scc_count);
        int v;
        do {
            v = stack[(*top)--]; // Pop dallo stack
            onStack[v] = 0;
            printf("%d ", v);
        } while (v != w);
        printf("]\n");
    }
}

void GRAPHfind_SCCs(G graph) {
    if (graph == NULL) return;

    int V = graph->V;
    int *pre = malloc(V * sizeof(int));
    int *low = malloc(V * sizeof(int));
    int *stack = malloc(V * sizeof(int));
    int *onStack = calloc(V, sizeof(int));

    if (!pre || !low || !stack || !onStack) return;

    int i;
    for (i = 0; i < V; i++) {
        pre[i] = -1;
        low[i] = -1;
    }

    int top = -1;
    int time = 0;
    int scc_count = 0;

    for (i = 0; i < V; i++) {
        if (pre[i] == -1) {
            SCCdfs(graph, i, pre, low, stack, &top, onStack, &time, &scc_count);
        }
    }

    free(pre);
    free(low);
    free(stack);
    free(onStack);
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