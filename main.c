#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define GRAY "\e[47m"
#define BLACK "\e[0;100m"
#define WHITE "\e[0;107m"
#define RESET "\e[0m"

#define INF 999999

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

int cnt = INF;

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

    }
}

void GRAPHoutput(GRAPH G) {
    COORD coord;
    coord.X = 55, coord.Y = 0;
    for (int i = 0; i < G->V; ++i) {
        if (i > cnt + 1)
            break;
        for (link a = G->adj[i]; a != NULL; a = a->next) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if (a->c == 1)
                cnt = i;
            printf("%s ", colors[a->c]);
            for (int j = 0; j < coord.Y; ++j)
                printf("%s ", colors[a->c]);
            for (int j = coord.Y; j > 0; --j)
                printf("%s ", colors[a->c]);
            printf(RESET);
            coord.X--, coord.Y++;
            Sleep(50);
        }
    }
}

int main(void) {
    system("cls");
    GRAPH G = GRAPHinit(10);
    int k = 0;
    int c = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = k; j < 45; ++j, ++c) {
            if (c == i)
                break;
            GRAPHinsertArc(G, i, j);
            printf("%d - %d\n", i, j);
            k = j + 1;
        }
        c = 0;
    }
    GRAPHdfs(G);
    cnt = INF;
    GRAPHoutput(G);
    puts("");
    getchar();
    return 0;
}