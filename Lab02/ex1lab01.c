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
	printf("Insira o nome do arquivo de entrada: ");									//SYSCALL 1
	scanf("%s", nomeArquivo);												//SYSCALL 2
	
	// Abrimos o arquivo desejado passando o nome fornecido pelo usuario.
	FILE *arquivo = fopen(nomeArquivo, "r");                                                                                //SYSCALL 3
	
	if(arquivo == NULL){ // Se fopen nos retornar null...
		printf("\nO arquivo nao foi encontrado.");									//SYSCALL 4
		return -1;                                                                                                      //SYSCALL 5
	} else { // Caso tenha um arquivo com o nome fornecido...
		printf("\nConteudo do arquivo '%s':\n\n", nomeArquivo);								//SYSCALL 6
		
		while(true){
			char linha[100]; // criamos um vetor de caracteres para armazenar o conteudo das linhas do arquivo
			// efetuamos a leitura de linha a linha do arquivo
			// caso a leitura chegue ate o final do arquivo, ele retorna um ponteiro NULL
			char *ptr = fgets(linha, 100, arquivo);                                                                 //SYSCALL 7
			// se o ponteiro apontar para NULL, encerra o while
			if(ptr == NULL)
				break;
			printf("%s", linha); // imprimimos a linha								//SYSCALL 8
		}
		
		printf("\n\nFim da leitura do arquivo '%s'.", nomeArquivo);                                                     //SYSCALL 9
	}
	
	// Fechamos o arquivo que foi aberto
	fclose(arquivo);                                                                                                        //SYSCALL 10
	
	return 0;                                                                                                               //SYSCALL 11
}
