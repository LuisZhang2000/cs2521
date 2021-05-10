
#include "list.h"

// copy s1 to s2
List copy(List s1) {

	List s2 = newList();

	Node curr1 = s1->head;
	Node curr2 = s2->head;

	if (curr1 == NULL) {	// empty list	
		//printf("empty list, return NULL\n");
		return NULL;
	} else if (curr1->next == NULL) {	// only one node
		//printf("copying only one node\n");
		Node n = newNode(curr1->value);
		s2->head = n;
		curr2 = n;
		curr2->next = NULL;
		//printList(s2);
		return s2;
	}
	while (curr1 != NULL) {
		if (curr2 == NULL) {	//s2 is empty
			Node n = newNode(curr1->value);
			s2->head = n;
			curr2 = n;
			curr2->next = NULL;
		} else {
			Node n = newNode(curr1->value);
			curr2->next = n;
			curr2 = curr2->next;
			curr2->next = NULL;
		}
		curr1 = curr1->next;
	}
	return s2;

}

List listSetUnion(List s1, List s2) {
	

	if ((s1->head == NULL) && (s2->head == NULL)) {
		return newList();
	} 
	else if (s1->head == NULL && s2->head != NULL) {
		return copy(s2);
	}

	List setUnion = copy(s1);

	Node newCurr = setUnion->head;
	Node curr2 = s2->head;

	while (curr2 != NULL) {
		newCurr = setUnion->head;
		while (newCurr != NULL) {
			if (curr2->value == newCurr->value) {	// number is already in new list
				break;
			} else if (newCurr->next == NULL && newCurr->value != curr2->value) {	// add curr->value to newList
				Node temp = newNode(curr2->value);
				newCurr->next = temp;
				temp->next = NULL;
				break;
			}
			newCurr = newCurr->next;
		}
		curr2 = curr2->next;
	}

	return setUnion;
}

