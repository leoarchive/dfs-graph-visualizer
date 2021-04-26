#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

//#define WHT "\e[0;107m"
#define GRY "\e[47m"
#define BLK "\e[100m"
#define RST "\e[0m"
#define vertex int
#define color char

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

void dfsR(Graph G);
void print_color(Graph G);
char *get_color(int i);

void GRAPHdfs(Graph G) {
    link a;
    char *c;
    for (int i = 0; i < G->V; ++i) {
        c = get_color(i);
        for (a = G->adj[i]; a != NULL; a = a->next)
            strcpy(a->c, c);
    }
    print_color(G);
    dfsR(G);
}

int cnt = 1000;

void dfsR(Graph G) {
    bool end;
    for (int i = 0; i < G->V; ++i) {
        end = true;
        for (link a = G->adj[i]; a != NULL; a = a->next) {
            strcpy(a->c, GRY);
            end = false;
        }
        if (!end) {
            cnt = i;
            print_color(G);
            for (link a = G->adj[i]; a != NULL; a = a->next) {
                strcpy(a->c, BLK);
            }
        }

    }
}
void print_color(Graph G) {
    COORD coord;
    coord.X = 50, coord.Y = 0;
    link a;
    for (size_t i = 0; i < G->V; ++i) {
        if (i > cnt + 1)
            break;
        Beep(1 + (i * 100), 100);
        for (a = G->adj[i]; a != NULL; a = a->next) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            printf("%s \a"RST, a->c);
            for (int j = 0; j < coord.Y; ++j)
                printf("%s "RST, a->c);
            for (int j = coord.Y; j > 0; --j)
                printf("%s "RST, a->c);
            coord.Y++;
            coord.X--;
            Sleep(50);
        }
    }

}

char *get_color(int i) {
    switch (i) {
        case 0:
            return "\e[0;101m";
        case 1:
            return "\e[41m";
        case 2:
            return "\e[0;102m";
        case 3:
            return "\e[42m";
        case 4:
            return "\e[0;103m";
        case 5:
            return "\e[43m";
        case 6:
            return "\e[0;104m";
        case 7:
            return "\e[44m";
        case 8:
            return "\e[0;105m";
        case 9:
            return "\e[45m";
        case 10:
            return "\e[0;106m";
        case 11:
            return "\e[46m";
    }
}

int main(void) {
    system(CLEAR);
    Graph G = GRAPHinit(30);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 1, 3);

    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 2, 5);
    GRAPHinsertArc(G, 2, 6);

    GRAPHinsertArc(G, 3, 7);
    GRAPHinsertArc(G, 3, 8);
    GRAPHinsertArc(G, 3, 9);
    GRAPHinsertArc(G, 3, 10);

    GRAPHinsertArc(G, 4, 11);
    GRAPHinsertArc(G, 4, 12);
    GRAPHinsertArc(G, 4, 13);
    GRAPHinsertArc(G, 4, 14);
    GRAPHinsertArc(G, 4, 15);

    GRAPHinsertArc(G, 5, 16);
    GRAPHinsertArc(G, 5, 17);
    GRAPHinsertArc(G, 5, 18);
    GRAPHinsertArc(G, 5, 19);
    GRAPHinsertArc(G, 5, 20);
    GRAPHinsertArc(G, 5, 21);

    GRAPHinsertArc(G, 6, 22);
    GRAPHinsertArc(G, 6, 23);
    GRAPHinsertArc(G, 6, 24);
    GRAPHinsertArc(G, 6, 25);
    GRAPHinsertArc(G, 6, 26);
    GRAPHinsertArc(G, 6, 27);
    GRAPHinsertArc(G, 6, 28);

    GRAPHinsertArc(G, 7, 29);
    GRAPHinsertArc(G, 7, 30);
    GRAPHinsertArc(G, 7, 31);
    GRAPHinsertArc(G, 7, 32);
    GRAPHinsertArc(G, 7, 33);
    GRAPHinsertArc(G, 7, 34);
    GRAPHinsertArc(G, 7, 35);
    GRAPHinsertArc(G, 7, 36);

    GRAPHinsertArc(G, 8, 37);
    GRAPHinsertArc(G, 8, 38);
    GRAPHinsertArc(G, 8, 39);
    GRAPHinsertArc(G, 8, 40);
    GRAPHinsertArc(G, 8, 41);
    GRAPHinsertArc(G, 8, 42);
    GRAPHinsertArc(G, 8, 43);
    GRAPHinsertArc(G, 8, 44);
    GRAPHinsertArc(G, 8, 45);
    GRAPHdfs(G);
    cnt = 100;
    print_color(G);
    puts("");
    system("pause");
    return 0;
}