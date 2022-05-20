#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFF)

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
	printf("START HASH TABLE\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hash_table[i] == NULL) {
			printf("\t%i\t---\n", i);
		} else if (hash_table[i] == DELETED_NODE) {
			printf("\t%i\t-<deleted>-\n", i);
		} else {
			printf("\t%i\t%s\t%i\n", i, hash_table[i]->name, hash_table[i]->age);
		}
	}
}

bool hash_table_insert(person *p) {
	if (p == NULL) {
		return false;
	}

	int index = hash(p->name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
			hash_table[try] = p;
			return true;
		}
	}
	return false;
}

person *hash_table_search(char *name) {
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;

		if (hash_table[try] == NULL) {
			return NULL;
		}

		if (hash_table[try] == DELETED_NODE) {
			continue;
		}

		if (strncmp(hash_table[try]->name, name, MAX_NAME) == 0) {
			return hash_table[try];
		}
	}

	return NULL;
}

person * hash_table_delete(char *name) {
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;

		if (hash_table[try] == NULL) {
			return NULL;
		}

		if (hash_table[try] == DELETED_NODE) {
			continue;
		}

		if (strncmp(hash_table[try]->name, name, MAX_NAME) == 0) {
			person* p = hash_table[try];
			hash_table[try] = DELETED_NODE;
			return p;
		}
	}
	return NULL;
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
