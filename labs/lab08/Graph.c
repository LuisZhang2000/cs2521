// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);

	int *visited = calloc(g->nV, sizeof(int));
	int found = 0;
	Queue q = newQueue();
	QueueJoin(q, src);	

	// initialise visited array to -1
	for (int i = 0; i < g->nV; i++) {
		visited[i] = -1;
	}

	if (src == dest) {	// special case, no need to search
		path[0] = src;
		return 1;
	}

	while(!QueueIsEmpty(q)) {
		Vertex x = QueueLeave(q);
		if (x == dest) {
			found = 1;
			//printf("found dest\n");
			break;
		}
		for (Vertex y = 0; y < g->nV; y++) {
			if (g->edges[x][y] <= 0 || g->edges[x][y] > max)	// skip if x isnt adjacent to y or if too big
				continue;
			if (visited[y] == -1) {	// enqueue neighbours if unvisited
				QueueJoin(q, y);
				visited[y] = x;
			}
		}
	}

	int steps = 0;
	int *reversePath = calloc(g->nV, sizeof(int));

	// work backwards from the visited array to update path array
	if (found == 1) {
		//printf("%d\n", steps);
		for (Vertex v = dest; v != src; v = visited[v]) {	// keep updating v to be the predecessor of itself
			reversePath[steps] = v;	
			steps++;	// record number of steps took from dest to src
		}
		reversePath[steps] = src;
		steps++;
	}

	for (int j = 0; j < steps; j++) {
		path[j] = reversePath[steps - j - 1];
	}

	dropQueue(q);
	free(reversePath);
	free(visited);

	return steps; 
}
