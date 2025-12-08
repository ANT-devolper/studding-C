#include <stdio.h>
#include <string.h>

int main (void) {

	char message[] = "Hello my friends!";
	char my[] = "my";

	char *stack = strstr(message, my);
	printf("stack is: %s\n", stack);

	return 0;
}
