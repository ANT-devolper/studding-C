#include <stdio.h>
#include <string.h>

int main(void) {
	char src[10] = "123456789";

	char str1[50];
	strcpy(str1, src);	
	printf("string1: %s\n", str1);

	// char str2[5];
	// strcpy(str2, src);
	// printf("string2: %s\n", str2);

	char str3[50];
	strncpy(str3, src, 10);
	printf("string3: %s\n", str3);

	char str4[50];
	strncpy(str4, src, 5);
	printf("string4: %s\n", str4);
}
