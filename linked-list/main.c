#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"


int main(){
	Node *list_head1 = NULL;
	Node *list_head2 = NULL;

	list_head1 = insert_tail(list_head1, 2);
	list_head1 = insert_tail(list_head1, 3);
	
	list_head2 = insert_tail(list_head2, 2);
	list_head2 = insert_tail(list_head2, 2);
	list_head2 = insert_tail(list_head2, 2);
	
	
	
	


	printf("Lista 1:\n");
	print_list(list_head1);

	
	printf("Lista 2:\n");
	print_list(list_head2);
	
	sum_value(list_head1, list_head2);
	printf("Lista após sum:\n");
	print_list(list_head1);

	
	

	return 0;
}
