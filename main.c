#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAY "\e[47m"
#define BLACK "\e[0;100m"
#define WHITE "\e[0;107m"
#define RESET "\e[0m"

#if defined LINUX
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

#define vertex int
#define color int

char *colors[] = {WHITE,GRAY,BLACK};

typedef struct node *link;

struct GRAPH {
    int V;
    int A;
    link *adj;
};

typedef struct GRAPH *GRAPH;

struct node {
    vertex w;
    color c;
    link next;
};

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

GRAPH GRAPHinit(int V) {
    vertex v;
    GRAPH G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(GRAPH G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void dfsR(GRAPH G);
void GRAPHoutput(GRAPH G);

void GRAPHdfs(GRAPH G) {
    link a;
    for (int i = 0; i < G->V; ++i)
        for (a = G->adj[i]; a != NULL; a = a->next)
            a->c = 0;
    GRAPHoutput(G);
    dfsR(G);
}

void dfsR(GRAPH G) {
    bool end;
    for (int i = 0; i < G->V; ++i) {
        end = true;
        for (link a = G->adj[i]; a != NULL; a = a->next)
            a->c = 1, end = false;
        if (!end) {
            GRAPHoutput(G);
            for (link a = G->adj[i]; a != NULL; a = a->next)
                a->c = 2;
        }
        system(CLEAR);
    }
}

int inp[100];

void GRAPHoutput(GRAPH G) {
    int s = 55;
    int w = 1;
    int p = 0;
    int cnt = 0;
    for (int i = 0; i < G->V; ++i) {
        for (link a = G->adj[i]; a != NULL; a = a->next) {
            printf("%d -- %d", inp[p], inp[p+1]);
            p+=2;
            if (cnt++ == 10)
                s--;
            for (int j = 0; j < s; ++j)
                printf(" ");
            for (int j = 0; j < w; ++j)
                printf("%s ", colors[a->c]);
            printf(RESET);
            w += 2, s--;
            _sleep(50);
            puts("");
        }
    }
}

int main(void) {
    system(CLEAR);
    GRAPH G = GRAPHinit(10);
    int k = 0;
    int c = 0;
    int cnt = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = k; j < 45; ++j, ++c) {
            if (c == i)
                break;
            GRAPHinsertArc(G, i, j);
            inp[cnt++] = i, inp[cnt++] = j;
            k = j + 1;
        }
        c = 0;
    }
    GRAPHdfs(G);
    GRAPHoutput(G);
    puts("");
    getchar();
    return 0;
}
