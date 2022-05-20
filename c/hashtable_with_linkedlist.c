#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person{
	char name[MAX_NAME];
	int age;

	struct person *next;
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
	printf("START HASH TABLE\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			printf("\t%i\t---\n", i);
		} else {
			printf("\t%i\t ", i);
			person *current = hash_table[i];
			while (current != NULL) {
				printf("%s - ", current->name);
				current = current->next;
			}
			printf("\n");
		}
	}
	printf("END HASH TABLE\n");
}

bool hash_table_insert(person *p) {
	if (p == NULL) {
		return false;
	}

	int index = hash(p->name);
	p->next = hash_table[index];
	hash_table[index] = p;
	return true;
}

person *hash_table_search(char *name) {
	int index = hash(name);
	person *tmp = hash_table[index];

	while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
		tmp = tmp->next;
	}
	return tmp;
}

person * hash_table_delete(char *name) {
	int index = hash(name);

	person *tmp = hash_table[index];
	person *prev = NULL;

	while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
		prev = tmp;
		tmp = tmp->next;
	}

	if (tmp == NULL) {
		return NULL;
	}

	if (prev == NULL) {
		hash_table[index] = tmp->next;
	} else {
		prev->next = tmp->next;
	}

	return tmp;
}


int main() {
	init_hash_table();

	person john = {.name="John", .age=20};
	person test = {.name="Jhon", .age=20};
	person tom = {.name="Tom", .age=30};
	person jane = {.name="Jane", .age=40};
	person peter = {.name="Peter", .age=50};
	person isaac = {.name="Isaac", .age=60};

	hash_table_insert(&john);
	hash_table_insert(&test);
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
	print_table();
	return 0;
}
