#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

/* git copilot is unbelievable*/

typedef struct {
	char name[MAX_NAME];
	int age;
} person;

person * hash_table[TABLE_SIZE];

void init_hash_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

unsigned int hash(char *name) {
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;

	for (int i=0; i < length; i++) {
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}

	return hash_value;
}

void print_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] != NULL) {
			printf("%d: %s\n", i, hash_table[i]->name);
		}
	}
}

bool hash_table_insert(person *p) {
	if (p == NULL) {
		return false;
	}

	int index = hash(p->name);
	if (hash_table[index] != NULL) {
		return false;
	}

	hash_table[index] = p;
	return true;
}

person *hash_table_search(char *name) {
	int index = hash(name);
	if (hash_table[index] == NULL) {
		return NULL;
	}

	if (strncmp(hash_table[index]->name, name, MAX_NAME) == 0) {
		return hash_table[index];
	}

	return NULL;
}

person * hash_table_delete(char *name) {
	int index = hash(name);
	if (hash_table[index] == NULL) {
		return NULL;
	}

	if (strncmp(hash_table[index]->name, name, MAX_NAME) == 0) {
		person *p = hash_table[index];
		hash_table[index] = NULL;
		return p;
	}

	return NULL;
}


int main() {
	init_hash_table();
	print_table();

	person john = {.name="John", .age=20};
	person tom = {.name="Tom", .age=30};
	person jane = {.name="Jane", .age=40};
	person peter = {.name="Peter", .age=50};
	person isaac = {.name="Isaac", .age=60};

	hash_table_insert(&john);
	hash_table_insert(&tom);
	hash_table_insert(&jane);
	hash_table_insert(&peter);
	hash_table_insert(&isaac);

	print_table();

	person *found = hash_table_search("John");
	if (found != NULL) {
		printf("Found %s\n", found->name);
	} else {
		printf("Not found\n");
	}

	if (hash_table_delete("John") != NULL) {
		printf("Deleted John\n");
	}
	return 0;
}
