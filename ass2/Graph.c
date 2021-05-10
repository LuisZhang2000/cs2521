// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"
#include "DLList.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

//int vertexID (char *str, DLList url_names);

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

/*
// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}
*/

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if ((g->edges[v][w] != 0 && g->edges[w][v] != 0) || v == w)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = 1;
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
/*
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
*/

void showGraph (Graph g, DLList url_names)
{
	DLList curr1 = url_names;
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		DLListMoveTo(curr1, v+1);
		printf ("%d %s\n", v, DLListCurrent(curr1));
		for (w = 0; w < g->nV; w++) {
			DLListMoveTo(curr1, w+1);
			if (g->edges[v][w]) {
				printf ("\t%s\n", DLListCurrent(curr1));
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

// return number of vertices in a graph
int num_vertices (Graph g) {
	assert (g != NULL);
	return g->nV;
}

int outDegrees (Graph g, char *src, DLList url_names) {
	int v = vertexID (src, url_names);
  	int degrees = 0;
	for (int j = 0; j < g->nV; j++) {
    	if (g->edges[v][j] == 1) {
      		degrees += 1;
    	}
  	}
  	return degrees;
}

int inDegrees (Graph g, char *dest, DLList url_names) {
	int d = vertexID (dest, url_names);
  	int degrees = 0;
	for (int j = 0; j < g->nV; j++) {
    	if (g->edges[j][d] == 1) {
      		degrees += 1;
    	}
  	}
  	return degrees;
}

double inRefDegrees (Graph g, char *src, DLList url_names) {
	int v = vertexID (src, url_names);
  	double in_ref = 0;
  	for (int i = 0; i < g->nV; i++) {
    	int degrees = 0;
    	if (g->edges[v][i] == 1) {
      		for (int j = 0; j < g->nV; j++) {
        		if (g->edges[j][i] == 1) {
          			degrees += 1;
				}
      		}
      		in_ref += degrees;
      		// if (degrees == 0) {
        	// 	in_ref += 0.5;
      		// }
		}
  	}
  	return in_ref;
}

double outRefDegrees (Graph g, char* src, DLList url_names) {
	int v = vertexID (src, url_names);
  	double out_ref = 0;
  	for (int i = 0; i < g->nV; i++) {
    	int degrees = 0;
		if (g->edges[v][i] == 1) {
      		for (int j = 0; j < g->nV; j++) {
       			if (g->edges[i][j] == 1) {
          			degrees += 1;
        		}
      		}
      		out_ref += degrees;
      		if (degrees == 0) {
        		out_ref += 0.5;
      		}
    	}
  	}
  	return out_ref;
}

bool isConnected (Graph g, char *src, char *dest, DLList url_names)
{
	assert (g != NULL);
	int v = vertexID (src, url_names);
	int w = vertexID (dest, url_names);
	if (v < 0 || w < 0)
		return 0;
	return g->edges[v][w] == 1;
}