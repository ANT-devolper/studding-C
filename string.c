#include <stdio.h>
#include <string.h>

int main(void) {
	char str1[] = "hello world!";
	char str2[] = "hello world!";

	if (strcmp(str1, str2) == 0) (printf("String iguais\n"));
	else (printf("string nao igual\n"));
}
