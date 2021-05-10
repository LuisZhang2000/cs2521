#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "DLList.h"
#include "Graph.h"
#include "readData.h"

double weight_in(char* v, char* u, Graph g) {
  	double u_in = inDegrees(g, u, getCollection());
 	if (u_in == 0) {
		u_in = 0.5;
  	}
  	return u_in / inRefDegrees(g, v, getCollection());
}

// calculate the weight of a link(v, u) based on the number of outlinks of page u
// and the number of outlinks of all reference pages of page v 
double weight_out(char* v, char* u, Graph g) {
  	double u_out = outDegrees(g, u, getCollection());
  	if (u_out == 0) {
    	u_out = 0.5;
  	}
  	return u_out / outRefDegrees(g, v, getCollection());
}

void calculatePageRank(Graph g, double d, double diffPR, int maxIterations) {

    int i = 0;
    int N = num_vertices(g);
    double *PR = malloc(sizeof(double) * N);
    double *PR_next = malloc(sizeof(double) * N);

    for (i = 0; i < N; i++) {
        PR[i] = 1.0 / N;
        PR_next[i] = 0;
    }

    char *pi;
    char *pj;
    DLList url_list1 = getCollection();
    DLList url_list2 = getCollection();

    int iteration = 0;
    double diff = diffPR;
    double sum = 0;
    i = 0;
    int j = 0;

    while (iteration < maxIterations && diff >= diffPR) {
        while (DLListCurrent(url_list1) != NULL) {
            DLListMoveTo (url_list2, 1);    // reset url list 2 position
            pi = DLListCurrent(url_list1);
            printf("LOOP1: %s\n", pi);
            while (DLListCurrent(url_list2) != NULL) {
                pj = DLListCurrent(url_list2);
                printf("%s\n", pj);
                if (isConnected(g, pj, pi, getCollection())) {
                    printf("w_in = %f, w_out = %f\n", weight_in(pj, pi, g), weight_out(pj, pi, g));
                    sum += PR[j] * weight_in(pj, pi, g) * weight_out(pj, pi, g); 
                    printf("sum = %f\n", sum);
                }
                j++;
                DLListMove(url_list2, 1);
            }
            DLListMove(url_list1, 1);
        }
        PR_next[i] = (1.0 - d) / N + d * sum;
        //printf("PR: %f\n", PR_next[i]);
        //diff += fabs(PR_next[i] - PR[i]);
        //i++;
        iteration++;
    }
    return;
}

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        fprintf(stderr, "Wrong number of arguments\n");
        return -1;
    }

    double d = atof(argv[1]);	        // damping factor
  	double diffPR = atof(argv[2]);	    // difference in PageRank sum
  	int maxIterations = atoi(argv[3]);	// max iterations

    DLList urls = getCollection();
    assert(DLListCurrent(urls) != NULL);

    Graph g = getGraph(urls);
    assert(DLListCurrent(urls) != NULL);
    //showGraph(g, urls);
    calculatePageRank(g, d, diffPR, maxIterations);
    
    return 0;
}