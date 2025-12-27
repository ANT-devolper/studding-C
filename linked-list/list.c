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
Node *delete_tail(Node *head);
int legth(Node *head);

int main(){
	Node *list_head = NULL;

	list_head = insert_head(list_head, 3);
	list_head = insert_head(list_head, 6);
	list_head = insert_head(list_head, 5);
	list_head = insert_head(list_head, 1);
	

	list_head = delete_tail(list_head);
	
	print_list(list_head);

	printf("legth: %d\n", legth(list_head));
	return 0;
}


int legth(Node *head){
	int leg = 0;
	Node *current = head;
	while(current != NULL){
		leg++;
		current = current->next;
	}
	return leg;
}

Node *delete_tail(Node *head){
	if(head == NULL) return NULL; //Primeira verificação se não tiver node
	else if(head->next == NULL){
		// Segunda verificação se o node é o unico da lista
		head = head->next;
		free(head);
		return NULL;
	} else{
		// Busca o ultimo node e salva o valor anterior para apontar como NULL
		Node *current = head;
		Node *prev = NULL;
		while(current->next != NULL){
			prev = current;
			current = current->next;
		}
		prev->next = NULL;
		free(current);
		return head;
	}
}


Node *delete_head(Node *head){
	if(head == NULL) return NULL;
	else{
		Node *to_return = head->next;
		free(head);
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