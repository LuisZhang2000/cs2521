
#include "list.h"

List listSetIntersection(List s1, List s2) {
	
	List newSet = newList();
	Node curr1 = s1->head;

	while (curr1 != NULL) {
		Node curr2 = s2->head;
		while (curr2 != NULL) {
			if (curr1->value == curr2->value) {
				Node temp = newNode(curr1->value);
				temp->next = newSet->head;
				newSet->head = temp;
			}
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}
	return newSet;
}

