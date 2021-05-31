#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAY	"\e[90m"
#define BLACK	"\e[30m"
#define WHITE	"\e[97m"
#define RESET	"\e[0m"

#define vertex	int
#define color	int

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
	}
}

void GRAPHoutput(GRAPH G) {
	for (int i = 0; i < G->V; ++i) {
		for (link a = G->adj[i]; a != NULL; a = a->next) {
			printf("%s%d "RESET, colors[a->c], a->w);
		}
	}
	puts("");
}

int main(void) {
	GRAPH G = GRAPHinit(10);
	GRAPHinsertArc(G, 0, 1);
	GRAPHinsertArc(G, 1, 2);
	GRAPHinsertArc(G, 2, 3);
	GRAPHinsertArc(G, 2, 4);
	GRAPHinsertArc(G, 3, 5);
	GRAPHinsertArc(G, 3, 6);
	GRAPHinsertArc(G, 3, 7);
	GRAPHinsertArc(G, 4, 8);
	GRAPHdfs(G);
	GRAPHoutput(G);
	return 0;
}
