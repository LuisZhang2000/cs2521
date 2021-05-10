
#include "list.h"

void listReverse(List l) {
	
	Node prev = NULL;
	Node curr = l->head;
	Node next = NULL;

	if (curr == NULL || curr->next == NULL) {
		return;
	}

	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	l->head = prev;
}

