#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int value;
  	struct node *left;
  	struct node *right;
} Node;

Node* create_node(int value) {
  	Node *node = (Node*)malloc(sizeof(Node));
  	node->value = value;
  	node->left = NULL;
  	node->right = NULL;
  	return node;
}

void add_node(Node **root, int value) {
  	if(*root == NULL) {
    		*root = create_node(value);
    		return;
  	}

  	if(value < (*root)->value) {
    		add_node(&((*root)->left), value);
  	} else if(value > (*root)->value) {
    		add_node(&((*root)->right), value);
  	} else {
    		fprintf(stderr, "Error: Taki wierzchołek już istnieje.\n");
  	}
}

void remove_node(Node **root, int value) {
  	if(*root == NULL) {
    		fprintf(stderr, "Error: Nie ma takiego wierzchołka.\n");
    		return;
  	}

  	if(value < (*root)->value) remove_node(&((*root)->left), value);
  	else if(value > (*root)->value) remove_node(&((*root)->right), value);
  	else {
   		if((*root)->left == NULL && (*root)->right == NULL) {
      			free(*root);
      			*root = NULL;
    		} else if((*root)->left == NULL) {
      			Node *temp = *root;
      			*root = (*root)->right;
      			free(temp);
    		} else if((*root)->right == NULL) {
      			Node *temp = *root;
      			*root = (*root)->left;
      			free(temp);
    		} else {
      			Node *temp = *root;
      			Node *succ = (*root)->right;
      			while(succ->left != NULL) {
        			temp = succ;
        			succ = succ->left;
      			}
      			(*root)->value = succ->value;
      			if(temp == *root) temp->right = succ->right;
      			else temp->left = succ->right;

      			free(succ);
    		}
  	}
}

int find_min(Node *root) {
  	if(root == NULL) {
    		fprintf(stderr, "Error: W pustym drzewie to i Salomon wierzchołka nie znajdzie.\n");
    		return 0;
  	}
  	
	Node *current = root;
  	while(current->left != NULL) current = current->left;

  	return current->value;
}

int find_max(Node *root) {
  	if(root == NULL) {
    		fprintf(stderr, "Error: W pustym drzewie to i Salomon wierzchołka nie znajdzie.\n");
    		return 0;
  	}
  	
	Node *current = root;
  	while(current->right != NULL) current = current->right;

  	return current->value;
}

int search(Node *root, int value) {
  	if(root == NULL) return 0;
  	if(root->value == value) return 1;
  	if(value < root->value) return search(root->left, value); 
	else return search(root->right, value);
}

void remove_less(Node **root, int value) {
  	if(*root == NULL) return;
  	if((*root)->value < value) {
    		Node *temp = *root;
    		*root = (*root)->right;
    		free(temp);
    		remove_less(root, value);
  	} else remove_less(&((*root)->left), value);
}

void remove_greater(Node **root, int value) {
  	if(*root == NULL) return;
  	if((*root)->value > value) {
    		Node *temp = *root;
    		*root = (*root)->left;
    		free(temp);
    		remove_greater(root, value);
  	} else remove_greater(&((*root)->right), value);
}

void print_tree(Node *root, int depth) {
  	if(root == NULL) return;
  	print_tree(root->right, depth + 1);
  	for(int i = 0; i < depth; i++) printf("\t");
  	printf("%d\n", root->value);
  	print_tree(root->left, depth + 1);
}

int main() {
  	Node *root = NULL;
  	int value;
  	char command[10];
  	while(1) {
    		printf("> ");
    		scanf("%s", command);
    		if(*command == 'i') {
      			scanf("%d", &value);
      			add_node(&root, value);
    		} else if(*command == 'd') {
      			scanf("%d", &value);
      			remove_node(&root, value);
    		} else if(*command == 's') {
      			scanf("%d", &value);
      			if(search(root, value)) printf("YES\n");
      			else printf("NO\n");
    		} else if(*command == 'm' && *(command + 1) == 'i') {
      			printf("%d\n", find_min(root));
    		} else if(*command == 'm' && *(command + 1) == 'a') {
      			printf("%d\n", find_max(root));
    		} else if(*command == 'r' && *(command + 1) == 'm') {
      			scanf("%d", &value);
      			if(*(command + 2) == 'l') remove_less(&root, value);
      			else if(*(command + 3) == 'g') remove_greater(&root, value);
    		} else if(*command == 'p') {
      			print_tree(root, 0);
    		} else if(*command == 'q') break;
   	 	else fprintf(stderr, "Error: To nie windows, komendy trzeba znać!.\n");
  	}
  	return 0;
}
