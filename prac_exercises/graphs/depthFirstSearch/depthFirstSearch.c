
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void depthFirstSearch(Graph g, int src) {
	
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	for (int i = 0; i < GraphNumVertices(g); i++) {
		visited[i] = 0;
	}

	// set src vertex to visited
	visited[src] = 1;	

	for (int i = 0; i < GraphNumVertices(g); i++) {
		// if the src is adjacent to the current vertex i
		// and if it hasn't been visited
		if (GraphIsAdjacent(g, src, i) && visited[i] == 0) {
			// set it to visited
			//printf("%d ", i);
			visited[i] = 1;
			depthFirstSearch(g, i);
		}
	}
}	

