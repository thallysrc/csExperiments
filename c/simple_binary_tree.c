#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
	int data;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;


tree_node * create_node(int data) {
	tree_node *new_node = malloc(sizeof(tree_node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

void printtabs(int tabs) {
	for (int i = 0; i < tabs; i++) {
		printf("\t");
	}
}

void printtree_rec(tree_node *root, int level) {
	if (root == NULL) {
		printtabs(level);
		printf("Empty tree\n");
		return;
	}

	printtabs(level);
	printf("data = %d\n", root->data);
	printtabs(level);
	printf("left\n");
	printtree_rec(root->left, level + 1);
	printtabs(level);
	printf("right\n");
	printtree_rec(root->right, level + 1);
}

void printtree(tree_node *root) {
	printtree_rec(root, 0);
}

int main() {
	tree_node *n1 = create_node(15);
	tree_node *n2 = create_node(22);
	tree_node *n3 = create_node(33);
	tree_node *n4 = create_node(44);
	tree_node *n5 = create_node(51);

	n1->left = n2;
	n1->right = n3;

	n3->left = n4;
	n3->right = n5;

	printtree(n1);

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);

	return 0;
}
