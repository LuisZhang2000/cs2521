#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct Rank {
  	char **urls;
  	int nurl;
} Rank_t;


void read_rank(Rank_t *rank, const char *filename) {
  	FILE *fp = fopen(filename, "r");
 	char line[1024];
  	rank->urls = NULL;
	rank->nurl = 0;
	while (fscanf(fp, "%s", line) != EOF) {
    	rank->urls = realloc(rank->urls, (rank->nurl + 1) * sizeof(char*));
    	rank->urls[rank->nurl] = malloc((strlen(line) + 1) * sizeof(char));
    	strcpy(rank->urls[rank->nurl], line);
    	rank->nurl += 1;
  	}
  	fclose(fp);
}

Rank_t union_rank(Rank_t *ranks, int nranks) {
  	Rank_t c_rank;
  	c_rank.urls = NULL;
  	c_rank.nurl = 0;
  	for (int i = 0; i < nranks; ++i) {
    	for (int j = 0; j < ranks[i].nurl; ++j) {
      		int in = 0;
      		for (int k = 0; k < c_rank.nurl; ++k) {
        		if (strcmp(ranks[i].urls[j], c_rank.urls[k]) == 0) {
          			in = 1;
          		break;
        		}
      		}
      		if (in == 0) {
        		c_rank.urls = realloc(c_rank.urls, (c_rank.nurl + 1) * sizeof(char*));
        		c_rank.urls[c_rank.nurl] = malloc((strlen(ranks[i].urls[j]) + 1) * sizeof(char));
        		strcpy(c_rank.urls[c_rank.nurl], ranks[i].urls[j]);
        		c_rank.nurl += 1;
      		}
		}
  	}
  	return c_rank;
}

double calWcp(Rank_t *ranks, int nranks, Rank_t c_rank,  int pos[], int npos) {
  	double w = 0.0;
  	for (int i = 0; i < nranks; ++i) {
    	Rank_t rank = ranks[i];
    	for (int j = 0; j < npos; ++j) {
      		int p = pos[j];
      		char *url = c_rank.urls[j];
      		int in_p = -1;
      		for (int k = 0; k < rank.nurl; ++k) {
        		if (strcmp(rank.urls[k], url) == 0) {
          			in_p = k;
          			break;
        		}
      		}
      		if (in_p == -1) {
        		continue;
      		}
      		w += fabs(1.0 * (in_p + 1) / rank.nurl - 1.0 * p / npos);
		}
  	}
  	return w;
}

void scaledFootrule(Rank_t *ranks, int nranks, Rank_t c_rank,  int pos[], int npos, int best_pos[], double *best) {
  	if (npos == c_rank.nurl) {
    	double wcp = calWcp(ranks, nranks, c_rank, pos, npos);
    	if (wcp < *best || *best < 0) {
      		*best = wcp;
      		for (int i = 0; i < npos; ++i) {
        		best_pos[i] = pos[i];
      		}
    	}
    	return;
  	}
  	for (int i = 1; i <= c_rank.nurl; ++i) {
    	int in = 0;
    	for (int j = 0; j < npos; ++j) {
      		if (pos[j] == i) {
        		in = 1;
      		}
    	}
    	if (in) {
      		continue;
    	}
    	pos[npos] = i;
    	scaledFootrule(ranks, nranks, c_rank, pos, npos + 1, best_pos, best);
  	}
}


int main(int argc, char *argv[])
{
  	if (argc < 2) {
    	return EXIT_FAILURE;
  	}
  	int nranks = argc - 1;
  	Rank_t *ranks = malloc(nranks * sizeof(Rank_t));
  	for (int i = 0; i < nranks; ++i) {
    	read_rank(ranks + i, argv[i + 1]);
  	}
  	Rank_t c_rank = union_rank(ranks, nranks);
  	int *pos = malloc(c_rank.nurl * sizeof(int));
  	int *best_pos = malloc(c_rank.nurl * sizeof(int));
  	double best = -1;
  	scaledFootrule(ranks, nranks, c_rank, pos, 0, best_pos, &best);
  	printf("%.6lf\n", best);
  	for (int i = 0; i < c_rank.nurl; ++i) {
    	printf("%s\n", c_rank.urls[best_pos[i] - 1]);
  	}
  	for (int i = 0; i < nranks; ++i) {
    	for (int j = 0; j < ranks[i].nurl; ++j) {
      		free(ranks[i].urls[j]);
    	}
    free(ranks[i].urls);
  	}
  	free(ranks);
  	for (int i = 0; i < c_rank.nurl; ++i) {
    	free(c_rank.urls[i]);
  	}
  	free(c_rank.urls);
  	free(pos);
  	free(best_pos);
  	return 0;
}