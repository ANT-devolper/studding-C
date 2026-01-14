/**
 * Linked lsit library
 * @file llist.h
 * @author Antonio
 * @date 13th january 2026
 */
#include <stdbool.h>

/**
 * A node in linked list
 */
typedef struct node {
	int value;/**<value stored in the node */
	struct node *next; /**<pointer to the next node */
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
Node *insert_after(Node *head, int new_value, int value);
Node *insert_before(Node *head, int new_value, int value);
Node *delete_list(Node *node);
void sum_value(Node *node1, Node *node2);