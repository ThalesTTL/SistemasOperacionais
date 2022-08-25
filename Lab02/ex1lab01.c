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
	printf("Insira o nome do arquivo: ");
	scanf("%s", nomeArquivo);
	
	// Abrimos o arquivo desejado passando o nome fornecido pelo usuario.
	FILE *arquivo = fopen(nomeArquivo, "r");
	
	if(arquivo == NULL){ // Se fopen nos retornar null...
		printf("O arquivo nao foi encontrado.");
		return -1;
	} else { // Caso tenha um arquivo com o nome fornecido...
		printf("Conteudo do arquivo '%s':\n", nomeArquivo);
		printf("--[INICIO]--\n");
		
		while(true){
			char linha[100]; // criamos um vetor de caracteres para armazenar o conteudo das linhas do arquivo
			int k = fscanf(arquivo, "%s", &linha);
			// fscanf sempre ira nos retornar o numero de objetos lidos, por isso, caso esse valor seja menor do que 1, significa que ele nao leu nada e chegou ao final do arquivo.
			if(k < 1)
				break;
			printf("%s\n", linha); // imprimimos a linha
		}
		
		printf("--[FIM]--");
	}
	
	// Fechamos o arquivo que foi aberto
	fclose(arquivo);
	
	return 0;
}
