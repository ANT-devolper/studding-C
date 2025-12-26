#include <stdio.h>
#include <string.h>

int main (void) {

	char message[] = "Hello my friends!";
	char my[] = "";

	char *stack = strstr(message, my);

	if (stack == NULL){
		printf("my = null");
	}
	else {
		printf("stack is: %s\n", stack);

	return 0;
}
