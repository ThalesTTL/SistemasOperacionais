/*
Luiz Gabriel Profirio Mendes      TIA: 42082293
Thales Torres Lopes               TIA: 32135513
Victor Silva Fernandes            TIA: 32163967
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){
	
	char nomeArquivo[100];
	printf("Insira o nome do arquivo de entrada: ");									//SYSCALL
	scanf("%s", nomeArquivo);												//SYSCALL
	
	// Abrimos o arquivo desejado passando o nome fornecido pelo usuario.
	FILE *arquivo = fopen(nomeArquivo, "r");
	
	if(arquivo == NULL){ // Se fopen nos retornar null...
		printf("\nO arquivo nao foi encontrado.");									//SYSCALL
		return -1;
	} else { // Caso tenha um arquivo com o nome fornecido...
		printf("\nConteudo do arquivo '%s':\n\n", nomeArquivo);								//SYSCALL
		
		while(true){
			char linha[100]; // criamos um vetor de caracteres para armazenar o conteudo das linhas do arquivo
			// efetuamos a leitura de linha a linha do arquivo
			// caso a leitura chegue ate o final do arquivo, ele retorna um ponteiro NULL
			char *ptr = fgets(linha, 100, arquivo);
			// se o ponteiro apontar para NULL, encerra o while
			if(ptr == NULL)
				break;
			printf("%s", linha); // imprimimos a linha								//SYSCALL
		}
		
		printf("\n\nFim da leitura do arquivo '%s'.", nomeArquivo);                                                     //SYSCALL
	}
	
	// Fechamos o arquivo que foi aberto
	fclose(arquivo);
	
	return 0;
}
