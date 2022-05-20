#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_LENGTH 10
#define EMPTY (-1)

int stack[STACK_LENGTH];
int top = EMPTY;

bool push(int value) {
	if (top >= STACK_LENGTH - 1) {
		printf("Stack is full\n");
		return false;
	}

	top++;
	stack[top] = value;
	return true;
}

int pop() {
	if (top == EMPTY) {
		printf("Stack is empty\n");
		return INT_MIN;
	}

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
