#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define vertex int
#define color char
#define WHT "\e[0;107m"
#define GRY "\e[47m"
#define BLK "\e[40m"
#define RST "\x1b[0m"

#if defined LINUX
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

typedef struct node *link;

struct graph {
    int V;
    int A;
    link *adj;
};

typedef struct graph *Graph;

struct node {
    vertex w;
    color c[10];
    link next;
};

void dfsR(Graph G);
void PRINTcolor(Graph G);

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    vertex v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof (link));
    for (v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void GRAPHdfs(Graph G) {
    link a;
    for (size_t i = 0; i < G->V; ++i)
        for (a = G->adj[i]; a != NULL; a = a->next)
            strcpy(a->c, WHT);
    PRINTcolor(G);
    dfsR(G);
}

void dfsR(Graph G) {
    bool end;
    for (size_t i = 0; i < G->V; ++i) {
        end = true;
        for (link a = G->adj[i]; a != NULL; a = a->next) {
            strcpy(a->c, GRY);
            end = false;
        }
        if (!end) {
            PRINTcolor(G);
            for (link a = G->adj[i]; a != NULL; a = a->next) {
                strcpy(a->c, BLK);
            }
        }

    }
}

void PRINTcolor(Graph G) {
    link a;
    for (size_t i = 0; i < G->V; ++i)
        for (a = G->adj[i]; a != NULL; a = a->next)
            printf("%s  "RST, a->c);
    puts("");
}

int main(void) {
    system(CLEAR);
    Graph G = GRAPHinit(6);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 1, 3);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 2, 5);
    GRAPHdfs(G);
    PRINTcolor(G);
    system("pause");
    return 0;
}