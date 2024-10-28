//Code adapted from @Leyxargon
// Original source: https://github.com/Leyxargon/c-linked-list


#include "list.h"

List *newList() { /* Implementado por José Julio Suárez*/
	List *list = (List *)malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	return list;
}

Node *newNode(int x) {
	Node *pnt = (Node *) malloc (sizeof(Node)); /* allocates physical memory for the node */
	pnt -> n = x;                               /* inserts the information received as input in the field(s) in the list */
	/* entering additional information if necessary...
	 * pnt -> b = y;
	 * pnt -> c = z;
	 * ... and so on
	 */
	pnt -> next = NULL;                         /* initialize the pointer */
	/* an insert function will take care of properly setting the next variable */
	return pnt;
}

void headInsert(List *list, int x){ /* Implemented by José Julio Suárez */
	Node *node = newNode(x);
	if(list->head != NULL){
		node->next = list->head;
	}
	list->head = node;
	if(list->length == 0){
		list->tail = node;
	}
	list->length++;
}

void tailInsert(List *list, int x){ /* Implemented by José Julio Suárez */
	Node *node = newNode(x);
	if(list->tail != NULL){
		list->tail->next = node;
	}
	list->tail = node;
	if(list->length == 0){
		list->head = node;
	}
	list->length++;
}

Node *findNode(Node *top, int k) {
	if (top == NULL || top -> n == k)
		return top;							/* returns the found node (NULL if it was not found) */
	else
		return findNode(top -> next, k);	/* scrolls the list to search for the item */
}

Node *deleteNode(Node *top, int k) {
	Node *tmp;					/* temporary node */
	if (top != NULL) {
		if (top -> n == k) {	/* if the element was found, it is deleted */
			tmp = top -> next;	/* set the temporary node to the next element (in order not to "lose" the list) */
			free(top);			/* frees the physical memory associated with the node to be deleted */
			top = tmp;			/* set the pointer to the next node */
		}
		else
			top -> next = deleteNode(top -> next, k);	/* scrolls the list in order to search the item to be deleted */
	}
	return top;
}

int pop(List *list, int index){ /* Implemented by José Julio Suárez */
	Node *extracted = extractNode(list, index);
	if(extracted != NULL){
		int value = extracted->n;
		free(extracted);
		return value;
	}
}

Node *extractNode(List *list, int index){ /* Implemented by José Julio Suárez */
	if(list == NULL || list->length == 0 || index >= list->length){
		return NULL;
	}
	Node *previous = NULL;
	Node *toRemove = list->head;
	if(index == 0){
		list->head = list->head->next;
	}
	else{
		for(int i = 1; i <= index && i < list->length; i++){
			previous = toRemove;
			toRemove = toRemove -> next;
		}
	}
	if(toRemove != NULL){
		if(previous != NULL){
			previous->next = toRemove->next;
		}
		else{
			list->head = toRemove->next;
		}
		list->length--;
		toRemove->next = NULL;
		return toRemove;
	}
}

void appendNode(List *list, Node *node){ /* Implemented by José Julio Suárez */
	if(list == NULL || node == NULL){
		return;
	}
	if(list->length == 0){
		list->head = node;
		list->tail = node;
	}
	else{
		list->tail->next = node;
		list->tail = node;
	}
	list->length++;
}

void appendList(List *target, List *source){ /* Implemented by José Julio Suárez */
	if (target == NULL || source == NULL) {
        return;
    }
    if (source->length == 0) {
        free(source);
        return;
    }
    if (target->length == 0) {
        target->head = source->head;
        target->tail = source->tail;
        target->length = source->length;
        free(source);
        return;
    }
    target->tail->next = source->head;
    target->tail = source->tail;
    target->length += source->length;
    free(source);
}

Node *deleteList(Node *top) {
	if (top != NULL) {				/* if not reached end of the list... */
		deleteList(top -> next);	/* ...move on */
		free(top);					/* delete the node */
	}
	else
		return NULL;
}

void printNodes(Node *top) {
	if (top != NULL) {
		printf("%d,", top -> n);
		printNodes(top -> next);
	}
}

void printList(List *list){ /* Implemented by José Julio Suárez */
	printf("[");
	Node *current = list->head;
    while(current != NULL){
        printf("%d,", current->n);
        current = current->next;
    }
    printf("]\n");
}

void Split(List *list, List **list2) { /* Modified by José Julio Suárez */
	Node *top = list->head;
	Node* fast = top -> next;
	Node* slow = top;
	Node* previous;
	int slowcount = 1;
    /* fast pointer advances two nodes, slow pointer advances one node */
	while (fast != NULL) {
		previous = fast;
		fast = fast -> next;		/* "fast" moves on first time */
		if (fast != NULL) { 
			slow = slow -> next;	/* "slow" moves on first time */
			fast = fast -> next;	/* "fast" moves on second time */
			slowcount++;
        }
    }
	List *half = newList();
    /* "slow" is before the middle in the list, so split it in two at that point */
	Node *oldTail = list->tail;
	list->tail = slow;
	half->head = slow->next;
	half->tail = oldTail;
	list->tail->next = NULL;
	half->length = list->length - slowcount;
	list->length = slowcount;
	*list2 = half;
}