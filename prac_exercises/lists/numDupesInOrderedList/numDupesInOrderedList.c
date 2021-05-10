
#include "list.h"

int numDupesInOrderedList(List l) {
	
	int dupes = 0;
	Node curr = l->head;

	if (curr == NULL || curr->next == NULL) {
		return 0;
	}

	while (curr->next != NULL) {
		if (curr->value == curr->next->value) {
			dupes++;
		}
		curr = curr->next;
	}

	return dupes;
}

