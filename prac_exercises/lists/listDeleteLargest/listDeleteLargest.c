
#include "list.h"

int maxNum(List l) {
	
	int bigNum = 0;
	Node curr = l->head;

	if (curr->next == NULL) {
		bigNum = curr->value;
		return bigNum;
	}

	while (curr != NULL) {
		if (curr->next == NULL) {	// at the last node
			if (curr->value > bigNum) {
				bigNum = curr->value;	
			} 
			break;
		}
		if (curr->value > bigNum) {
			bigNum = curr->value;
		}
		curr = curr->next;
	}
	return bigNum;
}

int listDeleteLargest(List l) {
	
	Node curr = l->head;
	int num = maxNum(l);
	Node prev = NULL;

	if (curr->value == num) {	// only one node
		l->head = curr->next;
		free(curr);
		return num;
	} else {
		while (curr != NULL) {
			if (curr->next == NULL) {	// at the last node
				if (curr->value == num) {	// biggest number is last node
					prev->next = NULL;
					free(curr);
					break;
				} 
			} else {	// somewhere in the middle
				if (curr->next->value == num) {
					Node temp = curr->next;
					curr->next = temp->next;
					free(temp);
					break;
				}
			}
		prev = curr;
		curr = curr->next;
		}
	}
	return num;
}

