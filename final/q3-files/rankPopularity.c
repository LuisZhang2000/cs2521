// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

double *visited;

double outDegrees (Graph g, int src) {
  	double degrees = 0;
	for (int i = 0; i < g->nV; i++) {
    	if (g->edges[src][i] == 1) {
      		degrees += 1;
    	}
  	}
  	return degrees;
}

double inDegrees (Graph g, int dest) {
  	double degrees = 0;
	for (int i = 0; i < g->nV; i++) {
    	if (g->edges[i][dest] == 1) {
      		degrees += 1;
    	}
  	}
  	return degrees;
}

void depthFirstSearch(Graph g, int src) {

	for (int i = 0; i < g->nV; i++) {
		// if the src is adjacent to the current vertex i
		// and if it hasn't been visited
		if (adjacent(g, src, i) && g->edges[src][i] && visited[i] == -1) {
			// set it to visited
			//printf("node: %d\n", i);
            if (outDegrees(g, i) == 0) {
                visited[i] = inDegrees(g, i) / 0.5;
                //printf("visited[%d]: %lf\n", i, visited[i]);
            } else {
			    visited[i] = inDegrees(g, i) / outDegrees(g, i);
                //printf("visited[%d]: %lf\n", i, visited[i]);
            }
			depthFirstSearch(g, i);
		}
	}
}	

void rankPopularity(Graph g, int src, double *mnV) {
	
    assert (g != NULL);

    visited = calloc(g->nV, sizeof(double));
	for (int i = 0; i < g->nV; i++) {
		visited[i] = -1;
	}   

    //printf("in: %d   out: %d\n", inDegrees(g, src), outDegrees(g, src));
    if (outDegrees(g, src) == 0) {
        visited[src] = inDegrees(g, src) / 0.5;
    } else if (inDegrees(g, src) == 0) {
        visited[src] = 0.5 / outDegrees(g, src);
    } else {
        visited[src] = inDegrees(g, src) / outDegrees(g, src);
    }
    
    //printf("node: %d\n", src);
    depthFirstSearch(g, src);

    for (int i = 0; i < g->nV; i++) {
		mnV[i] = visited[i];
	}   
    free(visited);
    return;
}