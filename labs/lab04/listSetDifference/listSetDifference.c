
#include "list.h"

List listSetDifference(List l1, List l2) {
	
	List diffList = newList();

	Node curr1 = l1->head;
	Node curr2 = l2->head;

	while (curr1 != NULL) {
		curr2 = l2->head;
		while (curr2 != NULL) {
			if (curr1->value == curr2->value) {
				break;	
			}
			else if ((curr1->value != curr2->value) && (curr2->next == NULL)) {
				Node n = newNode(curr1->value);
				if (diffList->head == NULL) {	// first insertion into diffList
					diffList->head = n;
				}
				else {
					n->next = diffList->head;
					diffList->head = n;
				}
			}
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}

	return diffList;
}

