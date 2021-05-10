#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Get query words from arguments
matched_url_list = findMatchedUrls("invertedIndex.txt", queryWords)
matched_url_list_with_PR = findPagerank("pagerankList.txt", matched_url_list)
*/

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
        //printf("buf: %s\n", buffer);
		pages = realloc(pages, (*num + 1) * sizeof(PageRank_t));
		strcpy(pages[*num].url, buffer);	// insert url into pages struct
		fscanf(fp, "%[^,],", buffer);		// read out links but don't do anything with it
		//printf("buff: %s\n", buffer);
		fscanf(fp, "%s", buffer);			// read pagerank
    	//printf("buffer: %s\n", buffer);	
		pages[*num].weight = atof(buffer);	// insert pagerank into pages struct
		*num += 1;
    }
	fclose(fp);
    return pages;
}

// search function that takes in number of query words, a list of the query words, 
// a list of pages with elements containing url and pagerank and an index number
void search(int numWords, char *words[], PageRank_t *pages, int num) {

	//Result_t *results = NULL;

	FILE *fp = fopen("invertedIndex.txt", "r");
    char buffer[100];
    char line[1000];

    while (fgets(line, 1000, fp)) {     // keep reading current line (e.g. "and url11")
        //printf("line: %s\n", line);
    	sscanf(line, "%s", buffer);     // scan word into buffer (e.g. "and")
        //printf("buffer: %s\n", buffer);
        int foundWord = 0;
        for (int i = 0; i < numWords; i++) {
            if (strcmp(buffer, words[i]) == 0) {
                //printf("found\n");
                foundWord = 1;
                break;
            }
        }
        if (foundWord == 0) {
      		continue;
    	}
        char *urls = line;	
        urls = urls + strlen(buffer);	// urls is the string of urls listed after the key words in txt file
		printf("line: %s\n", line);
		printf("urls: %s\n", urls);
		// int n = 0;
		// while (urls && sscanf(urls, "%s", buffer) != EOF) {
		// 	int index = findPages(pages, num, buffer);	// look for the current url in the page list
		// 	if (index == -1) continue;
		// 	//printf("buffer: %s\n", buffer);
		// 	//int in = 0;
		// 	for (int i = 0; i < n; i++) {
		// 		printf("loop %d\n", i);
		// 	}
		// }
    }
}


int main(int argc, char *argv[]) {

    int num = 0;
    PageRank_t *pages = readPages(&num);
    (void) *pages;
	search(argc - 1, argv + 1, pages, num);

    return 0;
}