#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PageRank {
    char url[100];
    double weight;
} PageRank_t;

typedef struct Result {
    char *url;
    double weight;
} Result_t;

// function that compares a given url string to a list of pages
// returns the position of the url if it is found, and -1 otherwise
int findPages(PageRank_t *pages, int numPages, char *url) {
	for (int i = 0; i < numPages; i++) {
		if (strcmp(pages[i].url, url) == 0) {
			return i;
		}
	}
	return -1;
}

// helper function that opens and reads the pagerankList.txt file to create a list of pages
// containing its url and pagerank, returns the list of pages (using PageRank_t ADT)
PageRank_t *readPages(int *num) {

    FILE *fp = fopen("pagerankList.txt", "r");
    char buffer[100];
    PageRank_t *pages = NULL;
    *num = 0;
    while (fscanf(fp, " %[^,],", buffer) != EOF) {	// avoid reading commas
		pages = realloc(pages, (*num + 1) * sizeof(PageRank_t));
		strcpy(pages[*num].url, buffer);	// insert url into pages struct
		fscanf(fp, "%[^,],", buffer);		// read out links but don't do anything with it
		fscanf(fp, "%s", buffer);			// read pagerank
		pages[*num].weight = atof(buffer);	// insert pagerank into pages struct
		*num += 1;
    }
	fclose(fp);
    return pages;
}

// display by descending pagerank (for quicksort function)
int compare (const void *l, const void *r) {
	return ((Result_t *)l)->weight < ((Result_t *)r)->weight;
}

// search function that takes in number of query words, a list of the query words, 
// a list of pages with elements containing url and pagerank and an index number
void search(int numWords, char *words[], PageRank_t *pages, int num) {

	Result_t *results = NULL;
	int n = 0;

	FILE *fp = fopen("invertedIndex.txt", "r");
    char buffer[100];
    char line[1000];

    while (fgets(line, 1000, fp)) {     // keep reading current line (e.g. "and url11")
    	sscanf(line, "%s", buffer);     // scan word into buffer (e.g. "and")
        int found = 0;
        for (int i = 0; i < numWords; i++) {
            if (strcmp(buffer, words[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
      		continue;
    	}
        char *urls = line;	
        urls = urls + strlen(buffer);	// urls is the string of urls listed after the key words in txt file

		while (urls && sscanf(urls, "%s", buffer) != EOF) {
			urls = urls + strlen(buffer);
			int index = findPages(pages, num, buffer);	// look for the current url in the page list
			if (index == -1) continue;
			found = 0;
			for (int i = 0; i < n; i++) {	// look through urls in results and compare to the 
				if (results[i].url == pages[index].url) {
					found = 1;
					break;
				}
			}
			if (!found) {	
				results = realloc(results, (n + 1) * sizeof (Result_t));
				results[n].url = pages[index].url;
				results[n].weight = pages[index].weight;
				n++;
			}
		}
    }
	qsort(results, n, sizeof(Result_t), compare);
	for (int i = 0; i < n && i < 30; i++) {
		printf("%s\n", results[i].url);
	}
	fclose(fp);
	free(results);
}

int main(int argc, char *argv[]) 
{
    int num = 0;
    PageRank_t *pages = readPages(&num);
	search(argc - 1, argv + 1, pages, num);
	free(pages);
    return 0;
}