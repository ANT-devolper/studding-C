#include <stdio.h>

int main() {
	int x = 300;
	int* p = &x;

	printf("Endereco armazenado em p: %p\n", (void*)p);
	printf("Valor apontado por p: %d\n", *p);
	
	char* c = (char*)&x;

	printf("Endereco armazenado em c: %p\n", (void*)c);
	printf("Primeiro byte de x interpretado como char: %d\n", *c);

    return 0;
}
