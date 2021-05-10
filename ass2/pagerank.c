#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "DLList.h"
#include "Graph.h"
#include "readData.h"

typedef struct Result {
  	char url[100];
  	double weight;
} Result_t;


// calculate the weight of a link(v, u) based on the number of inlinks of page u
// and the number of inlinks of all reference pages of page v 
double weight_in(char* v, char* u, Graph g) {
  	double u_in = inDegrees(g, u, getCollection());
    double v_in = inRefDegrees(g, v, getCollection());
    if (v_in == 0) {
        v_in = 0.5;
  	}
  	return u_in / v_in;
}

// calculate the weight of a link(v, u) based on the number of outlinks of page u
// and the number of outlinks of all reference pages of page v 
double weight_out(char* v, char* u, Graph g) {
  	double u_out = outDegrees(g, u, getCollection());
  	if (u_out == 0) {
      	u_out = 0.5;
  	}
    double v_out = outRefDegrees(g, v, getCollection());
	if (v_out == 0) {
        v_out = 0.5;
  	}
  	return u_out / v_out;
}

int compare(const void* l, const void* r) {
  	return ((Result_t*)l)->weight < ((Result_t*)r)->weight;
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
    i = 0;

    while (iteration < maxIterations && diff >= diffPR) {
		diff = 0;
        for (int i = 0; i < N; i++) {
            DLListMoveTo (url_list2, 1);    // reset url list 2 position
            double sum = 0;
            pi = DLListCurrent(url_list1);
            if (pi == NULL) break;
            printf("LOOP1: %s\n", pi);
            for (int j = 0; j < N; j++) {
                pj = DLListCurrent(url_list2);
                printf("%s\n", pj);
                if (isConnected(g, pj, pi, getCollection())) {
					printf("w_in = %f, w_out = %f\n", weight_in(pj, pi, g), weight_out(pj, pi, g)); 
                    sum += PR[j] * weight_in(pj, pi, g) * weight_out(pj, pi, g); 
                }
                DLListMove(url_list2, 1);
            }
            PR_next[i] = (double) (1.0 - d) / N + (d * sum);
            diff += fabs(PR_next[i] - PR[i]);
            DLListMove(url_list1, 1);
        }
        iteration++;
    }

    Result_t *results = malloc(N * sizeof(Result_t));
    char *url;
    DLList urls = getCollection();

  	for (int i = 0; i < N; i++) {
        url = DLListCurrent(urls);
        strcpy(results[i].url, url);
		results[i].weight = PR_next[i];
        DLListMove(urls, 1);
  	}

    qsort(results, N, sizeof(Result_t), compare);
  	FILE *out = fopen("mypagerankList.txt", "w");
  	
  	for (int i = 0; i < N; i++) {
		fprintf(out, "%s, %d, %.7lf\n", results[i].url, outDegrees(g, results[i].url, getCollection()), results[i].weight);
  	}	
    fclose(out);
    free(PR);
  	free(PR_next);
  	free(results);
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
    showGraph(g, urls);
    calculatePageRank(g, d, diffPR, maxIterations);
    
    return 0;
}