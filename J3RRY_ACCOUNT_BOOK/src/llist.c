#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

llist * llist_create(void* new_data)
{
	struct node* new_node;

	llist* new_list = (llist*)malloc(sizeof(llist));
	*new_list = (struct node*)malloc(sizeof(struct node));

	new_node = *new_list;
	new_node->data = new_data;
	new_node->next = NULL;
	return new_list;
}

void llist_free(llist* list)
{
	struct node* curr = *list;
	struct node* next;

	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(list);
}


void llist_push(llist* list, void* data)
{
	struct node* head;
	struct node* new_node;
	if (list == NULL || *list == NULL) {
		fprintf(stderr, "llist_add_inorder: list is null\n");
	}

	head = *list;

	// Head is empty node
	if (head->data == NULL)
		head->data = data;

	// Head is not empty, add new node to front
	else {
		new_node = malloc(sizeof(struct node));
		new_node->data = data;
		new_node->next = head;
		*list = new_node;
	}
}

void* llist_pop(llist* list)
{
	void* popped_data;
	struct node* head = *list;

	if (list == NULL || head->data == NULL)
		return NULL;

	popped_data = head->data;
	*list = head->next;

	free(head);

	return popped_data;
}

void llist_print(llist* list, void (*print)(void*))
{
	struct node* curr = *list;
	while (curr != NULL) {
		print(curr->data);
		printf(" ");
		curr = curr->next;
	}
	putchar('\n');
}