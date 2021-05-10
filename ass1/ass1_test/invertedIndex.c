#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "invertedIndex.h"

char * normaliseWord(char *str) {
	// TRIM OPERATION
	char rtrim[100] = "\0";
	int i = strlen(str) - 1;

	while (i >= 0) {
		if (str[i] == ' '|| str[i] == '\t') {
			rtrim[i] = '\0';
		}
		if (str[i] != ' ' && str[i] != '\t') {
			break;
		}
		i--; 
	}

	while (i >= 0) {
		rtrim[i] = str[i];
		i--; 
	}

	char ltrim[30] = "\0";
	int j = 0, k = 0;
	
	while (rtrim[j] != '\0') {
		if (rtrim[j] != ' ' && rtrim[j] != '\t') {
			break;
		}
		j++;
	}

	while (rtrim[j] != '\0') {
		ltrim[k] = rtrim[j];
		j++;
		k++; 
	}

	
	// LOWERCASE CONVERSION
	int l = 0;
	while ( ltrim[l] ) {
		ltrim[l] = tolower(ltrim[l]);
		l++;
	}

	// GETTING RID OF PUNCTUATION MARKS (IF IT IS THE LAST CHAR)
	int length;
    length = strlen(ltrim);// Get length of string
    if (ltrim[length - 1] == '.' || ltrim[length - 1] == ',' || ltrim[length - 1] == ';' || ltrim[length - 1] == '?') {
		ltrim[length - 1] = '\0'; // Set next to last char to null
	}
	
	strcpy (str, ltrim);
	return str;
}

/** This function needs to read a given file with collection of file names, 
    read each of these files, generate inverted index as discussed in 
    the specs and return the inverted index. Do not modify invertedIndex.h file.
*/
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {

	FILE *fp;
	char *filename = collectionFilename;
	
	printf("-------- List all files in %s --------\n", filename);

    fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}

	return NULL;
	
}

/**
 * Outputs  the  given inverted index to a file named invertedIndex.txt.
 * The output should contain one line per word, with the  words  ordered
 * alphabetically  in ascending order. Each list of filenames for a word
 * should be ordered alphabetically in ascending order.
*/
void printInvertedIndex(InvertedIndexBST tree) {
	return;
}

// Functions for Part-2

/**
 * Returns  an  ordered list where each node contains a filename and the 
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
	return NULL;
}

/**
 * Returns  an  ordered list where each node contains a filename and the
 * summation of tf-idf values of all the matching search words for  that
 * file.  You only need to include documents (files) that contain one or
 * more of the given search words. The list must be in descending  order
 * of summation of tf-idf values (tfIdfSum). If there are multiple files
 * with  the  same tf-idf sum, order them by their filename in ascending
 * order.
 */
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
	return NULL;
}
