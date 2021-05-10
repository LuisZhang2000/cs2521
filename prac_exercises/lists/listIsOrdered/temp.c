#include "list.h"

bool listIsOrdered(List l) {
	
	Node curr = l->head;

	if (curr == NULL) {
		return true;
	}

	if (curr->next == NULL) {
		return true;
	}
	
	while (curr != NULL) {
		if (curr->value > curr->next->value) {
			return false;
		}
		curr = curr->next;
	}

	return true;
}

