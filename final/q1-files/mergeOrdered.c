// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// helper function to create a copy of a given list
// had to make this because when there was an empty list i got a double free error when returning any of the given lists 
List copy(List l1) {

	List l2 = newList();

	Node *curr1 = l1->first;
	Node *curr2 = l2->first;

	if (curr1 == NULL) {	// empty list	
		return NULL;
	} else if (curr1->next == NULL) {	// only one node
		Node *n = newNode(curr1->value);
		l2->first = n;
		curr2 = n;
		return l2;
	}
	while (curr1 != NULL) {
		if (curr2 == NULL) {	// l2 is empty
			Node *n = newNode(curr1->value);
			l2->first = n;
			curr2 = n;
			curr2->next = NULL;
		} else {
			Node *n = newNode(curr1->value);
			curr2->next = n;
			curr2 = curr2->next;
			curr2->next = NULL;
		}
		curr1 = curr1->next;
	}
	return l2;
}

List mergeOrdered(List list1, List list2) {
    
    // check if there are any empty lists
    if (list1->first == NULL && list2->first == NULL) {
        return NULL;
    } else if (list1->first == NULL) {
        List l = copy(list2);
        return l;
    } else if (list2->first == NULL) {
        List l = copy(list1);
        return l;
    }

    List sorted = newList();
	Node *sortedCurr = sorted->first;

    Node *curr1 = list1->first;
	Node *curr2 = list2->first;

    while (curr1 != NULL && curr2 != NULL) {
		if (curr1->value <= curr2->value) {
			Node *n = newNode(curr1->value);
			if (sortedCurr == NULL) {
				sorted->first = n;
				sortedCurr = n;
			} else {
				sortedCurr->next = n;
				sortedCurr = sortedCurr->next;
			}
			if (curr1->next == NULL) break;
			curr1 = curr1->next;
    } else {
			Node *n = newNode(curr2->value);
			if (sortedCurr == NULL) {
				sorted->first = n;
				sortedCurr = n;
			} else {
				sortedCurr->next = n;
				sortedCurr = sortedCurr->next;
			}
			if (curr2->next == NULL) break;
			curr2 = curr2->next;
		}
	}
    // if list 1 still has remaining values, append them 
    if (curr1->next != NULL) {	
		while (curr1 != NULL) {
			Node *n = newNode(curr1->value);
			sortedCurr->next = n;
			sortedCurr = sortedCurr->next;
			if (curr1->next == NULL) break;
			curr1 = curr1->next;
		}
	} else {
        // if list 2 still has remaining values, append them 
		while (curr2 != NULL) {
			Node *n = newNode(curr2->value);
			sortedCurr->next = n;
			sortedCurr = sortedCurr->next;
			if (curr2->next == NULL) break;
			curr2 = curr2->next;
		}
	}
    return sorted;
}

