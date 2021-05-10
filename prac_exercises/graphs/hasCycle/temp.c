
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

int dfsCycleCheck(Graph g, Vertex v, Vertex prev);
int *visited;

bool hasCycle(Graph g) {
	
	visited = calloc(GraphNumVertices(g), sizeof(int));
	if (dfsCycleCheck(g, 0, 0)) 
		return true;

	free(visited);
	return false;
}

int dfsCycleCheck(Graph g, Vertex v, Vertex prev) {

	visited[v] = 1;
	for (Vertex w = 0; w < GraphNumVertices(g); w++) {
		if (!GraphIsAdjacent(g, v, w)) continue;
		if (!visited[w]) 
			return dfsCycleCheck(g, w, v);
		if (w != prev) 
			return 1;
	}
	return 0;
}