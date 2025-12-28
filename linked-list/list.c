#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
int recursive_legth(Node *node);
bool check_value(Node *head, int value);
int count_value(Node *node, int value);
void replace_matches(Node *node, int value, int replace_value);
Node *delete_first_match(Node *head, int value, bool *deleted);
Node *delete_all_matches(Node *head, int value, int *delete_count);

int main(){
	Node *list_head = NULL;

	list_head = insert_head(list_head, 3);
	list_head = insert_head(list_head, 1);
	list_head = insert_head(list_head, 5);
	list_head = insert_head(list_head, 3);
	list_head = insert_head(list_head, 3);
	list_head = insert_head(list_head, 1);
	printf("Antes da exclusão\n");
	print_list(list_head);
	
	int num_deleted;
	printf("depois das exclusões\n");
	list_head = delete_all_matches(list_head, 3, &num_deleted);
	print_list(list_head);
	return 0;
}

Node *delete_all_matches(Node *head, int value, int *delete_count){
	Node *current = head;
	bool deleted = false;
	*delete_count = 0;

	do{
		current = delete_first_match(current, value, &deleted);
		if(deleted) *delete_count = *delete_count + 1;
	}while(deleted);

	return current;
}

Node *delete_first_match(Node *head, int value, bool *deleted){
	if(head == NULL){
		*deleted = false;
		return NULL;
	}
	if(head->value == value){
		Node *temp = head->next;
		free(head);
		*deleted = true;
		return temp;
	}

	Node *current = head->next;
	Node *prev= head;

	while (current != NULL){
		if(current->value == value){
			prev->next = current->next;
			free(current);
			*deleted = true;
			return head;
		}

		prev = current;
		current = current->next;
	}
	
	*deleted = false;
	return head;

}

void replace_matches(Node *node, int value, int replace_value){
	if(node != NULL){
		if(node->value == value)node->value = replace_value;
		replace_matches(node->next, value, replace_value);
	}
}

int count_value(Node *node, int value){
	if (node == NULL) return 0;
	else if(node->value == value) return 1 + count_value(node->next, value);
	else count_value(node->next, value);
}

bool check_value(Node *node, int value){
	if(node == NULL) return false;
	else if(node->value == value) return true;
	else return check_value(node->next, value);
}

int recursive_legth(Node *node){
	if(node == NULL) return 0;
	else return 1 + recursive_legth(node->next);
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