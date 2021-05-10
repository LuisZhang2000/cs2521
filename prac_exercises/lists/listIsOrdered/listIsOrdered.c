#include "list.h"

bool listIsOrdered(List l) {


	Node curr = l->head;
	if (curr == NULL || curr->next == NULL) {	// empty list/single node
		return true;
	}

	int order = 0;	// 0 for descending, 1 for ascending
	while (curr->next != NULL) {
		if (curr->value < curr->next->value) {
			order = 1;	// supposedly ascending order
			break;
		}
		curr = curr->next;
	}

	curr = l->head;

	while (curr->next != NULL) {
		if ((order == 1 && curr->value > curr->next->value) || (order == 0 && curr->value < curr->next->value))  {
			return false;
		}
		curr = curr->next;
	}
	return true;
}