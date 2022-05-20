#include <stdlib.h>
#include <stdio.h>

struct node {
	int value;
	struct node *next;
};

typedef struct node node_t;

void printlist(node_t *head) {
	node_t *current = head;
	while (current != NULL) {
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("\n");
}

node_t *create_node(int value) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}


node_t *insert_at_head(node_t **head, node_t * node_to_insert) {
	node_to_insert->next = *head;
	*head = node_to_insert;
	return node_to_insert;
}

node_t *find_node(node_t *head, int value) {
	node_t *current = head;
	while (current != NULL) {
		if (current->value == value) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

node_t *insert_after_node(node_t *node_to_insert_after, node_t *new_node) {
	new_node->next = node_to_insert_after->next;
	node_to_insert_after->next = new_node;
	return new_node;
}

int main() {
	node_t *head = NULL;
	node_t *tmp;

	for (int i = 0; i < 10; i++) {
		tmp = create_node(i);
		head = insert_at_head(&head, tmp);
	}

	tmp = find_node(head, 5);
	insert_after_node(tmp, create_node(100));
	printf("Found node with value %d\n", tmp->value);

	printlist(head);

	return 0;
}
