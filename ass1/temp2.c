#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <sysexits.h>
#include <err.h>

#include "invertedIndex.h"

InvertedIndexBST newInvertedIndexBST (void);
static struct InvertedIndexNode *newInvertedIndexNode (char *w, FileList filename);
static struct FileListNode *newFileListNode (char *w);

// create a new empty InvertedIndexBST
InvertedIndexBST newInvertedIndexBST (void)
{
	return NULL;
}

// make a new inverted index node containing a word and filelist of file names
static struct InvertedIndexNode *newInvertedIndexNode (char *w, FileList filename)
{
	struct InvertedIndexNode *new = malloc(sizeof(*new));
	if (new == NULL) err (EX_OSERR, "couldn't allocate BST node");
	new->word = malloc(sizeof(char) * 101);
	new->word = w;
	strcpy(new->word, w);
	new->fileList = filename;
	new->left = new->right = NULL;
	return new;
}

// create a new FileListNode with file name filename
// modified code from IntList.c (lab 01)
static struct FileListNode *newFileListNode (char *filename) 
{
	struct FileListNode *n = malloc(sizeof(*n));
	if (n == NULL) err (EX_OSERR, "couldn't allocate FileList node");
	
	n->filename = malloc(sizeof(char) * strlen(filename) + 1);
	strcpy(n->filename, filename);
	n->tf = 0;
	n->next = NULL;
	return n;
}

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

// helper function to insert new node into BST
InvertedIndexBST insertNode(InvertedIndexBST n, char *word, char *filename) 
{
	// if BST is empty, initialise the BST and all its elements
	if (n == NULL) {
		FileList f = newFileListNode(filename);
		n = newInvertedIndexNode(word, f);

    } else {
		int c = strcmp(word, n->word);
		if (c < 0) {
			n->left = insertNode(n->left, word, filename);
		}
		else if (c > 0) {
			n->right = insertNode(n->right, word, filename);
		}
		/*
		else {	// c = 0
			// check if word is in the same file, if so then break
			// use strcmp for alphabetical order
			// have different cases for inserting in beginning, middle, end (hint: lab 1)

			if (strcmp(filename, n->fileList->filename) == 0) 
				return NULL;

			if (n->fileList == NULL) {
				// fileList is currently empty
				struct FileListNode *new = newFileListNode (filename);
				n->fileList = new;
			}

			else if (strcmp(filename, n->fileList->filename) < 0) {
				// insert at beginning of list (before current node)
				FileList fileCurr = newFileListNode(filename);
				fileCurr->next = n->fileList;
				n->fileList = fileCurr;
			}
			else if (strcmp(filename, n->fileList->filename) > 0) {
				// insert in middle/end
				FileList fileCurr = n->fileList;
				FileList temp = newFileListNode(filename);
				while (fileCurr != NULL) {
					if (n->fileList->next != NULL) {
						if (strcmp(filename, n->fileList->filename) > 0 && strcmp(filename, n->fileList->next->filename) < 0) {
							temp->next = fileCurr->next;
							fileCurr->next = temp;
						}

					}
					fileCurr = fileCurr->next;
				}
			}
		}
		*/
	}
    return n;
}

/** This function needs to read a given file with collection of file names, 
    read each of these files, generate inverted index as discussed in 
    the specs and return the inverted index. Do not modify invertedIndex.h file.
*/
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {

	InvertedIndexBST invertedIndex = newInvertedIndexBST();
	FILE *fp;
	char *filename = collectionFilename;
	
	printf("\n List of all files in %s:\n", filename);

    fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}

	// read the file names in collection.txt and store in files array
	char str[101];
	int i = 0;
	char files[10][100];	// an array containing names of files in collection.txt


	while (fscanf(fp, "%s", str) == 1) {
		strcpy(files[i], str);
		printf("%s\n", files[i]);
		i++;
	}

	fclose(fp);		// close collection.txt

	// read each file inside collection.txt and generate inverted index
	int fileCount = i;
	i = 0;
	char word[101];

	while (i < fileCount) {
		fp = fopen(files[i], "r");
		if (fp == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
		}

		// open every file, calculate tf for every word and insert into BST
		while (fscanf(fp, "%s", word) == 1) {
			//printf("inserting word %s into the BST, %s , %s\n", word, normaliseWord(word), files[i]) ;
			invertedIndex = insertNode(invertedIndex, normaliseWord(word), files[i]);
		}
		i++;
		fclose(fp);
	}

	return invertedIndex;
	
}

// helper function for printInvertedIndex
void printInvertedIndexHelper(FILE *fp, InvertedIndexBST tree) {
	if (tree == NULL) {
		return;
	}
	printInvertedIndexHelper(fp, tree->left);
	fprintf(fp, "%s ", tree->word);
	while (tree->fileList != NULL) {
		fprintf(fp, "%s ", tree->fileList->filename);
		tree->fileList = tree->fileList->next;
	}
	fprintf(fp, "\n");
	printInvertedIndexHelper(fp, tree->right);
}


/**
 * Outputs  the  given inverted index to a file named invertedIndex.txt.
 * The output should contain one line per word, with the  words  ordered
 * alphabetically  in ascending order. Each list of filenames for a word
 * should be ordered alphabetically in ascending order.
*/
void printInvertedIndex(InvertedIndexBST tree) {
	if (tree == NULL) {
		return;
	}
	FILE *fp = fopen("invertedIndex.txt", "w+");
	printInvertedIndexHelper(fp, tree);
	fclose(fp);
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


