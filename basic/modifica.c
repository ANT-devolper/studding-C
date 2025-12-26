#include <stdio.h>

void muda(int* ptr) {
	*ptr = 99;
}

int main(){
	int x = 10;
	muda(&x);

	printf("valor de x depois da funcao: %d\n", x);

	return 0;
}
