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
Node *eficient_delete_all_matches(Node *head, int value, int *delete_count);
Node *append_list(Node *head1, Node *head2);
Node *reverse_list(Node *head);
void sort_list(Node *head);
void delete_duplicates(Node *head);

int main(){
	Node *list_head1 = NULL;
	Node *list_head2 = NULL;

	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 4);
	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 5);
	list_head1 = insert_tail(list_head1, 7);
	list_head1 = insert_tail(list_head1, 8);
	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 5);
	list_head1 = insert_tail(list_head1, 8);
	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 5);
	list_head1 = insert_tail(list_head1, 1);
	list_head1 = insert_tail(list_head1, 8);


	printf("Lista normal:\n");
	print_list(list_head1);

	delete_duplicates(list_head1);
	printf("Lista ordenada:\n");
	print_list(list_head1);
	
	return 0;
}

void delete_duplicates(Node *head){
	if(head == NULL) return ;
	if(head->next == NULL) return ;

	Node *current1, *current2, *duplicate;
	current1 = head;

	while(current1 != NULL && current1->next != NULL){
		current2 = current1;
		while(current2->next != NULL){
			if(current1->value == current2->next->value){
				duplicate = current2->next;
				current2->next = current2->next->next;
				free(duplicate);
			}else current2 = current2->next;
		}
		current1 = current1->next;
	}
}

void sort_list(Node *head){
	if(head == NULL) return ;
	if(head->next == NULL) return ;

	bool swaped = false;

	do{
		swaped = false;
		Node *current = head;
		Node *prev = NULL;

		while(current->next != NULL){
			prev = current;
			current = current->next;
			if(current != NULL){
				if(current->value < prev->value){
					int temp;
					temp = prev->value;
					prev->value = current->value;
					current->value = temp;
					swaped = true;
				}
			}

		}
	}while(swaped);
}

Node *reverse_list(Node *head){
	if(head == NULL) return NULL;
	if(head->next == NULL) return head;

	Node *current = head;
	Node *next_node = head->next;

	current->next = NULL;

	while(next_node != NULL){
		Node *tmp = next_node->next;
		next_node->next = current;
		current = next_node;
		next_node = tmp;
	}
	return current;
}

Node *append_list(Node *head1, Node *head2){
	if(head1 == NULL) return head2;
	Node *current = head1;
	while(current->next != NULL) current = current->next;
	current->next = head2;
	return head1;
}

Node *eficient_delete_all_matches(Node *head, int value, int *delete_count){
	// esse é um metodo mais eficiente para excluir os nodes e buscar o valor
	// node video tem uma diferença de alguns milisegundos em uma lista de 5000 itens simples de apenas numeros
	*delete_count = 0;
	if(head == NULL) return NULL;

	Node *current, *temp, *new_head;
	current = head;
	while(current->value == value){
		temp = current;
		current = current->next;
		free(temp);
		*delete_count = *delete_count + 1;
		if(current ==  NULL) return NULL;
	}
	
	new_head = head;

	while(current->next != NULL){
		if(current->next->value == value){
			temp = current->next;
			current->next = current->next->next;
			free(temp);
			*delete_count = *delete_count + 1;
		}
		else current = current->next;
	}
	return new_head;
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