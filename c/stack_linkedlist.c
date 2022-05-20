#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define STACK_LENGTH 10
#define EMPTY (-1)

int stack[STACK_LENGTH];
int top = EMPTY;

typedef struct node {
	int data;
	struct node *next;
} node;

node* head = NULL;

bool push(int value) {
	node *newNode = (node*)malloc(sizeof(node));

	if (newNode == NULL) {
		return false;
	}

	newNode->data = value;
	newNode->next = head;
	head = newNode;

	return true;
}

int pop() {
	if (head == EMPTY) {
		return INT_MIN;
	}

	int result = head->data;
	node* temp = head;
	head = head->next;
	free(temp);
	return result;

	int value = stack[top];
	top--;
	return value;
}

int main() {

	push(56);
	push(78);
	push(90);
	push(12);
	push(34);

	int t;
	while ((t = pop()) != INT_MIN) {
		printf("%d\n", t);
	}

	return 0;
}
