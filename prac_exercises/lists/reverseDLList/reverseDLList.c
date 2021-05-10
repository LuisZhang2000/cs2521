
#include "list.h"

void reverseDLList(List l) {


	if (l->size == 0 || l->size == 1) {
		return;
	}

	Node temp = l->first;
	l->first = l->last;
	l->last = temp;
	Node curr = l->first;

	while (curr != NULL) {
		temp = curr->next;
		curr->next = curr->prev;
		curr->prev = temp;
		curr = curr->next;
	}
}

