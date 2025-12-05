#include <stdio.h>

int main(){
	int x = 10;
	int* p = &x;

	printf("Valor de X: %d\n", x);
	printf("Endereco de x: %p\n", (void*)&x);
	printf("Valor guardado em p (endereco): %p\n", (void*)p);
	printf("Valor apontado por p: %d\n", *p);

	return 0;
}
