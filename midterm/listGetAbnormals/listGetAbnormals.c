
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void insert(List l, int value) {

	Node curr = l->last;
	Node n = newNode(value);

	if (l->size == 0) {		// list is empty
		curr = l->first = l->last = n;	
		l->size++;
	} 
	else {
		n->prev = curr;
		n->next = NULL;

		curr->next = n;
		l->last = n;
		curr = n;

		l->size++;
	}

}

List listGetAbnormals(List l, int threshold) {
	
	List new = newList();
	Node curr = l->first;

	while (curr != NULL) {
		
		if (curr->prev != NULL && curr->next != NULL) {
			if (abs(curr->value - curr->prev->value) >= threshold && abs(curr->value - curr->next->value) >= threshold) {
				// insert node into new list
				insert(new, curr->value);
				//printf("%d is abnormal\n", curr->value);
			}
		}
		curr = curr->next;
	}

	return new;
}

