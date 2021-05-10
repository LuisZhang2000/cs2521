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
int checkFileList (InvertedIndexBST IIBST, char *filename);
TfIdfList newTfIdfList (void);
//static struct TfIdfNode *newTfIdfNode (char *filename);
InvertedIndexBST searchTree(InvertedIndexBST t, char *searchWord);

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

// check if a filename is already in a filelist
// return 1 if it is, return 0 if not
int checkFileList (InvertedIndexBST IIBST, char *filename) {

	FileList temp = IIBST->fileList;

	if (IIBST == NULL || temp == NULL) return 0;

	while (temp != NULL) {
		if (strcmp(filename, temp->filename) == 0) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

TfIdfList newTfIdfList (void) {
	return NULL;
}
/*
static struct TfIdfNode *newTfIdfNode (char *filename) {
	struct TfIdfNode *n = malloc(sizeof(*n));
	if (n == NULL) err (EX_OSERR, "couldn't allocate TfIdf node");
	
	n->filename = malloc(sizeof(char) * strlen(filename) + 1);
	strcpy(n->filename, filename);
	n->tfIdfSum = 0;
	n->next = NULL;
	return n;
}
*/


// function to calculate relative term frequency
// d = number of words in document
/*
double calc_tf(char *term, int D) {
	int freq = findFrequency(term);
	return freq / D;
}
*/

char * normaliseWord(char *str) {
	
	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ' && str[i] != '\t') {
			j = i;
		}
	}	
	str[j + 1] = '\0';

	// lowercase
	i = 0;
	while (str[i]) {
		str[i] = tolower(str[i]);
		i++;
	}

	// punctuation marks

	int len;
    len = strlen(str);// Get length of string
    if (str[len - 1] == '.' || str[len - 1] == ',' || str[len - 1] == ';' || str[len - 1] == '?') {
		str[len - 1] = '\0'; // Set next to last char to null
	}
	return str;
}

// helper function to insert new node into BST
InvertedIndexBST insertNode(InvertedIndexBST n, char *word, char *filename) 
{
	if (n == NULL) {	// if BST is empty, initialise the BST and all its elements
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
		else {	// c = 0
			if (checkFileList(n, filename) == 1) { 	// check if word is in the same file, if so then break
				return n;
			} else if (strcmp(filename, n->fileList->filename) < 0) {	// insert at front of list
				FileList fileCurr = newFileListNode(filename);
				fileCurr->next = n->fileList;
				n->fileList = fileCurr;
			} else if (strcmp(filename, n->fileList->filename) > 0) { // insert somewhere in middle
				FileList fileCurr = n->fileList;
				FileList temp = newFileListNode(filename);
				while (fileCurr->next != NULL) {
					if (strcmp(filename, fileCurr->filename) > 0 && strcmp(filename, fileCurr->next->filename) < 0) {
						temp->next = fileCurr->next;
						fileCurr->next = temp;
						break;
					}
					fileCurr = fileCurr->next;
				}
				if (fileCurr->next == NULL) {	// insert at end of list
						fileCurr->next = temp;
				}
			}
		}
	}
    return n;
}

/** This function needs to read a given file with collection of file names, 
    read each of these files, generate inverted index as discussed in 
    the specs and return the inverted index. Do not modify invertedIndex.h file.
*/
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {

	InvertedIndexBST invertedIndex = newInvertedIndexBST();
	char *filename = collectionFilename;

    FILE *fp1 = fopen(filename, "r");
	if (fp1 == NULL) {
		perror("Error while opening file.\n");
		exit(EXIT_FAILURE);
	}

	char str[101];
	int i = 0;
	char files[10][100];	// an array containing names of files in collection.txt

	while (fscanf(fp1, "%s", str) == 1) {	// read the file names in collection.txt and store in files array
		strcpy(files[i], str);
		i++;
	}
	fclose(fp1);		// close collection.txt

	// read each file inside collection.txt and generate inverted index
	int fileCount = i;
	i = 0;
	char *word = malloc(sizeof(char) * 101);

	while (i < fileCount) {
		fp1 = fopen(files[i], "r");
		if (fp1 == NULL) {
			perror("Error while opening file.\n");
			exit(EXIT_FAILURE);
		}
		while (fscanf(fp1, "%s", word) == 1) {	// open every file, calculate tf for every word and insert into BST
			word = normaliseWord(word);
			invertedIndex = insertNode(invertedIndex, word, files[i]);
		}
		i++;
		fclose(fp1);
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

// helper function to search for a word in a given tree
// returns the node if word is found, NULL otherwise
InvertedIndexBST searchTree(InvertedIndexBST t, char *searchWord) {
	if (t == NULL) {
		return NULL;
	} else if (strcmp(searchWord, t->word) == 0) {
		return t;
	} else if (strcmp(searchWord, t->word) < 0) {
		return searchTree(t->left, searchWord); 
	} else {
		return searchTree(t->right, searchWord);
	}
}

/**
 * Returns  an  ordered list where each node contains a filename and the 
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
	/*
	TfIdfList tfidf = newTfIdfList();


	InvertedIndexBST node = searchTree(tree, searchWord);
	if (node == NULL) {
		return NULL;
	} else {	// searchWord exists within the tree
		tfidf = newTfIdfNode(node->fileList->filename);
	}
	*/
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


