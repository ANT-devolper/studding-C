#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
} Node;

void print_list(Node *head);
Node *insert_head(Node *head, int new_value);
Node *insert_tail(Node *head, int new_value);
Node *delete_head(Node *head);

int main(){
	Node *list_head = NULL;

	list_head = insert_head(list_head, 3);
	list_head = insert_head(list_head, 4);
	list_head = insert_tail(list_head, 5);

	list_head = delete_head(list_head);
	
	print_list(list_head);
	return 0;
}


Node *delete_head(Node *head){
	if(head == NULL) return NULL;
	else{
		Node *to_return = head->next;
		return to_return;
	}
}

Node *insert_tail(Node *head, int new_value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	Node *current;
	current = head;
	if(head == NULL) return new_node;
	else{
		while(current->next != NULL) current = current->next;
		current->next = new_node;
		return head;
		
	}
}

// aqui é uma função para colocar um valor como head do node;
// Onde se passa o valor da variavel Node e depois um valor inteiro;
Node *insert_head(Node *head, int new_value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	if (head == NULL) return new_node;
	else{
		new_node->next = head;
		return new_node;
	}
}


void print_list(Node *head){
	Node *current;
	current = head;
	int i = 0;
	while(current != NULL){
		printf("valor do node %d: %d\n", i, current->value);
		i++;
		current = current->next;
	}
}