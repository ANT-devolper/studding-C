/**
 * Linked list library
 * @file llist.c
 * @author Antonio
 * @date 13th january 2026
 */
#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 *  Duplicates the list in an informed Node variable, exeple:\n
 *  Node list2 = duplicate_list(list1); 
 * @param node head node of the list that will be duplicated
 * @return duplicated list into Node variabel type
 */

Node *duplicate_list(Node *node){
	if(node == NULL) return NULL;

	Node *new_node = calloc(sizeof(Node), 1);
}

/**
 * Sums the values of two nodes by storing the sum in the firts parameter
 * @param node1  head node where the sum value will be stored
 * @param node2 head node that will be added whitin the firts parameter
 */
void sum_value(Node *node1, Node *node2){
	if(node1 == NULL || node2 == NULL) return ;
	node1->value = node1->value + node2->value;
	sum_value(node1->next, node2->next);
}

/**
 * Deletes all linked list values stored in the argument recursively
 * @param node head node of the list to will be delete all values
 */
Node *delete_list(Node *node){
	if(node != NULL){
		delete_list(node->next);
		free(node);
	}
	return NULL;
}

/**
 * Adds a value before a value entered in the arguments
 * @param head head node of the list will be added a value
 * @param new_value value to be added on the list before other value
 * @param value value to be searched for in the list
 */
Node *insert_before(Node *head, int new_value, int value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	if(head == NULL) return new_node;
	if(head->value == value){
		new_node->next = head;
		return new_node;
	}
	Node *current = head->next;
	Node *prev = head;
	while (current != NULL){
		if(current->value == value){
			prev->next = new_node;
			new_node->next = current;
			return head;
		}else{
			prev = current;
			current = current->next;
		}
	}
		return head;
}

/**
 * Adds a value after a value entered in the arguments
 * @param head head node of the list will be added a value
 * @param new_value value to be added on the list after other value
 * @param value value to be searched for in the list
 */
Node *insert_after(Node *head, int new_value, int value){
	Node *new_node = calloc(1, sizeof(Node));
	new_node->value = new_value;
	
	if(head == NULL) return	new_node;
	else{
		Node *current = head;
		while(current->next != NULL){
			if(current->value == value){
				new_node->next = current->next;
				current->next = new_node;
				return head;
			}
			else current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
		return head;
	}
}

/**
 * Deletes all duplicate value in the list , keeping the first one value in the list
 * @param head head node in the list will be delete duplicated value
 */
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

/**
 * sort (orderna) the values in the list from smallest to largest
 * @param head head node in the list will be sorted
 */
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
/**
 * Reverses the order of the nodes in the linke d list
 * @param head head node in the list will be reversed
 * 
 */
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

/**
 * Add the second list provided  to the end of the first lsit 
 * @param head1 head node of the list will recive second other list
 * @param head2 head node of the list will be added on firts argument
 */
Node *append_list(Node *head1, Node *head2){
	if(head1 == NULL) return head2;
	Node *current = head1;
	while(current->next != NULL) current = current->next;
	current->next = head2;
	return head1;
}

/**
 * Dele all matches value in the linked list passed on the parameters
 * @param head head node in the list will be delete matches values
 * @param value int value to be deleted in the linked list
 * @param delete_count pointer to a variable to stored qauntity of this value in the list
 */
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

/**
 * Ineficient method to delete all matches values in the linked list
 * @param head head node in the list will be delete matches values
 * @param value int value to be deleted in the linked list
 * @param delete_count pointer to a variable to stored qauntity of this value in the list
 */
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

/**
 * Replace all values to other value in the list
 * @param node head node vaue to will be replace values
 * @param value int value to be searched in the list
 * @param replace_value int value to replace in the list
 */
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
	printf("\n");
}