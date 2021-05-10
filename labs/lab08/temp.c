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
	assert (g != NULL && validV(g, src) && validV(g, dest));
	
	//printf("max length: %d\n", max);
	//printf("path: %d\n", path);
		
	Queue q = newQueue();	// initialise queue for breadth-first search
	Vertex *visited = calloc(g->nV, sizeof(int));
	QueueJoin(q, src);
	Vertex *vpath = malloc(g->nV * sizeof(Vertex));
	
	int isFound = 0;
	while (!QueueIsEmpty(q) && !isFound) { 		// while queue is empty, remove FIFO elemnt from queue and visit
		Vertex y, x = QueueLeave(q);
		
		// if destination has been found
		if (x == dest) {
			isFound = 1;
			break;
		}
		for (y = 0; y < g->nV; y++) {	// while y is less than number of vertices of g
			if (!(g->edges[x][y] > 0 && g->edges[x][y] < max)) {	// if edges weight is negative or greater than max	
				continue;											// ignore and iterate to next vertex
			}
			if (!visited[y]) {	// add neighbours to queue if not visited 
				vpath[y] = x; 
				QueueJoin(q, y);
				visited[y] = 1;
			}
		}
	}
	
	
	Vertex *reverse_path = malloc(g->nV * sizeof(Vertex));
	int points = 0;
	
	if (isFound == 1) {	
		Vertex v;
		for (v = dest; v != src; v = vpath[v]) {	// go in reverse, start from destination and until v is source
			reverse_path[points] = v;
			points++;
		}
		reverse_path[points] = src;
		points++;
	}
	
	int j = 0;
	
	for (j = 0; j < points; j++) {
		path[points - (j + 1)] = reverse_path[j];
	}
	
	// free memory
	free(visited);
	free(vpath);
	free(reverse_path);
	dropQueue(q);
	
	if (points == 0) {	// if unsuccessful (no hops)
		return 0;
	}
	
	printf("points = %d\n", points);  
	return points;
}


	/*
	int i;
	for (i = 0; i < 35; i++) {
		route[i] = newQueue();	// initialise 
	}
	if (src == dest) {		// special case, no search needed
		path[0] = src;
		return 1;
	}
	
	QueueJoin(route[0], src);
	QueueJoin(q, 0);
	
	//while(!QueueEmpty(q)) {
		printf("current breadth-first search queue: ");
		showQueue(q);
	//}
	return 0;
	*/
