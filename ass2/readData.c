#include <string.h>
#include <assert.h>

#include "DLList.h"
#include "Graph.h"
#include "readData.h"
/*
// function that creates an array containing all url names
char **getArray() {
    
    char **array = malloc(sizeof(*array) * 10);

    FILE *fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}   

    int i = 0;
    char buffer[100];
       
    while (fscanf(fp, "%s", buffer)) {
        array[i] = malloc(sizeof(char) * 101);
        strcpy(array[i], buffer);
        i++;
    }
    fclose(fp);         
    return array;
}
*/

// Opens a singular url txt file and reads it
// Adds edges between the opened url and the other listed urls in section 1
void read_url_file(char *url, Graph g) {

    char filename[100];
    strcpy(filename, url);	
  	strcat(filename, ".txt");

    FILE *fp = fopen(filename, "r");
    //printf("filename is %s\n", filename);
    if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}
    
    DLList url_list = getCollection();  // list of urls
    int url_vertex = vertexID(url, url_list);   // vertex number of opened url (to pass into insertEdge)
    //printf("url id is %d: \n", url_vertex);
    int buffer_vertex;  // vertex number of current url inside opened url 
    char buffer[100];
    
    while (fscanf(fp, "%s", buffer) != EOF) {
        if (strcmp(buffer, "#start") == 0 || strcmp(buffer, "Section-1") == 0) {
            continue;
        }
        else if (strcmp(buffer, "#end") == 0) {
            break;
        }
        //printf("buffer: %s\n", buffer);
        buffer_vertex = vertexID(buffer, url_list);
        //printf("url vertex: %d buffer vertex: %d, no. vertcies: %d\n", url_vertex, buffer_vertex, num_vertices(g));
        insertEdge(g, url_vertex, buffer_vertex);   // insert edge between opened url and current url within the opened url
    }
    fclose(fp);
    
}

// Create a list of urls to process by reading data from "collection.txt"
DLList getCollection() {

    DLList url_list = newDLList();
    
    FILE *fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}
    char buffer[100];
    while (fscanf(fp, "%s", buffer) != EOF) {
        //printf("buffer: %s\n", buffer);
        //printf("list length: %ld\n", DLListLength(url_list));
    	//DLListMoveTo(url_list, 1);
        DLListBefore(url_list, buffer);
    }

    fclose(fp);
    return url_list;
}

// Create empty graph (using graph ADT in Graph.h and Graph.c) 
// For each url in the above list
// read <url>.txt file, and update graph by adding node and outgoing links
Graph getGraph(DLList url_list) {

    int vertices = DLListLength(url_list);
    Graph g = newGraph(vertices);

    char *url;

    while (DLListCurrent(url_list) != NULL) {
        url = DLListCurrent(url_list);
        read_url_file(url, g);
        DLListMove(url_list, 1);
    }
    DLListMoveTo (url_list, 1);
    return g;
}
