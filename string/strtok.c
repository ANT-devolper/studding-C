#include <stdio.h>
#include <string.h>

int main(void) {

	char s[] = "Então, o povo começou a queixar�se das suas dificuldades aos ouvidos do Senhor . Quando ele os ouviu, a sua ira se acendeu, e fogo da parte do Senhor queimou entre eles e consumiu algumas extremidades do acampamento.";
	char d[] = " ";

	char *stringtok = strtok(s, d);
	while(stringtok != NULL){
		printf("%s\n", stringtok);
		stringtok = strtok(NULL, d);
	}
	
	
	
	return 0;
}
