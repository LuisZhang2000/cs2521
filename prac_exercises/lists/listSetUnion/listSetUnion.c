
#include "list.h"

List listSetUnion(List s1, List s2) {
	
	List sorted = newList();
	Node sortedCurr = sorted->head;
	
	Node curr1 = s1->head;
	Node curr2 = s2->head;

	while (curr1 != NULL && curr2 != NULL) {
		if (curr1->value <= curr2->value) {
			printf("insert node from l1\n");
			Node n = newNode(curr1->value);
			if (sortedCurr == NULL) {
				sorted->head = n;
				sortedCurr = n;
			} else {
				sortedCurr->next = n;
				sortedCurr = sortedCurr->next;
			}
			if (curr1->next == NULL) break;
			curr1 = curr1->next;
		} else {
			printf("insert node from l2\n");
			Node n = newNode(curr2->value);
			if (sortedCurr == NULL) {
				sorted->head = n;
				sortedCurr = n;
			} else {
				sortedCurr->next = n;
				sortedCurr = sortedCurr->next;
			}
			if (curr2->next == NULL) break;
			curr2 = curr2->next;
		}
	}
	
	if (curr1->next != NULL) {	// list 1 still has values
		while (curr1 != NULL) {
			Node n = newNode(curr1->value);
			printf("last node from l1\n");
			sortedCurr->next = n;
			sortedCurr = sortedCurr->next;
			if (curr1->next == NULL) break;
			curr1 = curr1->next;
		}
	} else {
		while (curr2 != NULL) {
			Node n = newNode(curr2->value);
			printf("last node from l2\n");
			sortedCurr->next = n;
			sortedCurr = sortedCurr->next;
			if (curr2->next == NULL) break;
			curr2 = curr2->next;
		}
	}

	return sorted;
}

