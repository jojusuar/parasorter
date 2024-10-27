//Code adapted from @Leyxargon
// Original source: https://github.com/Leyxargon/c-linked-list

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int n;              /* data field(s) */
	/* float b;
	 * char c;
	 * ... etc.
	 */
	struct node *next;  /* pointer to next element */
}Node;

typedef struct list { /* Implemented by José Julio Suárez */
	Node *head;
	Node *tail;
	int length;
}List;

List *newList(); /* Implemented by José Julio Suárez */

Node *newNode(int ); /* physically creates a new node */
/* N.B. this function is called by other functions because does not take care
 * of inserting the Node in the list, but delegates this operation to other
 * functions, such as *Insert functions */

void headInsert(List *, int ); /* Implemented by José Julio Suárez */

void tailInsert(List *, int ); /* Implemented by José Julio Suárez */

Node *findNode(Node *, int ); /* find a node in the list */

Node *deleteNode(Node *, int ); /* deletes a node corresponding to the inserted key */

int pop(List *, int ); /* Implemented by José Julio Suárez */

Node *extractNode(List * , int ); /* Implemented by José Julio Suárez */

void appendNode(List * , Node * ); /* Implemented by José Julio Suárez */

void appendList(List * , List * ); /* Implemented by José Julio Suárez */

Node *deleteList(Node *); /* deletes a list */

void printList(List *); /* Implemented by José Julio Suárez */

void printNodes(Node *); /* prints all the nodes in the list */

void Split(List *, List **); /* split the nodes of the list into two sublists */ /* Modified by José Julio Suárez */