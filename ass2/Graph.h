// MODIFIED FROM LAB 8

// Graph.h ... interface to Graph ADT
// Written by John Shepherd, March 2013

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "DLList.h"

// graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
typedef int Vertex;
int validV (Graph, Vertex); // validity check

// edges are pairs of vertices (end-points)
typedef struct {
	Vertex v;
	Vertex w;
} Edge;
void insertEdge (Graph, Vertex, Vertex);
void removeEdge (Graph, Vertex, Vertex);

// operations on graphs
Graph newGraph (int nV);
void dropGraph (Graph);
Graph makeGraph (int, int **);
void showGraph(Graph, DLList);
int findPath (Graph, Vertex, Vertex, int, int *);

// my own functions
int num_vertices(Graph);
int vertexID(char *, DLList);
int outDegrees (Graph, char *, DLList);
int inDegrees (Graph, char *, DLList);
double inRefDegrees (Graph g, char *src, DLList url_names);
double outRefDegrees (Graph g, char* src, DLList url_names);
bool isConnected (Graph g, char *src, char *dest, DLList url_names);


#endif
