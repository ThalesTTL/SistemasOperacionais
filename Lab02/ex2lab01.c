/*
Luiz Gabriel Profirio Mendes      TIA: 42082293
Thales Torres Lopes               TIA: 32135513
Victor Silva Fernandes            TIA: 32163967
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){
	
	char nomeArquivoEntrada [100];
	char nomeArquivoSaida [100];
	
	printf("Insira o nome do arquivo de entrada: ");								//SYSCALL 1
	scanf("%s", nomeArquivoEntrada);										//SYSCALL 2
	
	printf("Insira o nome do arquivo de saida: ");									//SYSCALL 3
	scanf("%s", nomeArquivoSaida);											//SYSCALL 4
	
	// Abrimos o arquivo de entrada
	FILE *entrada = fopen(nomeArquivoEntrada, "r");                                                                 //SYSCALL 5
	if(entrada == NULL){
		printf("Arquivo nao encontrado.");									//SYSCALL 6
		return -1;                                                                                              //SYSCALL 7
	}
	
	// Criamos um arquivo de saida, do tipo 'w', para poder receber e escrever o conteudo lido do arquivo de entrada.
	FILE *saida = fopen(nomeArquivoSaida, "w");                                                                     //SYSCALL 8
	if(saida == NULL){
		printf("Erro ao criar o arquivo");									//SYSCALL 9
		return -1;                                                                                              //SYSCALL 10
	}
	
	while(true){
		char linha[100]; // criamos um vetor de caracteres para armazenar o conteudo das linhas do arquivo
		
		// efetuamos a leitura de linha a linha do arquivo
		// caso a leitura chegue ate o final do arquivo, ele retorna um ponteiro NULL
		char *ptr = fgets(linha, 100, entrada);                                                                 //SYSCALL 11
		// se o ponteiro apontar para NULL, encerra o while
		if(ptr == NULL)
			break;

		// imprimimos a linha no arquivo de saida.
		fprintf(saida, "%s", linha);										//SYSCALL 12
		
	}
	printf("\n'%s' foi copiado em um novo arquivo chamado '%s'", nomeArquivoEntrada, nomeArquivoSaida);		//SYSCALL 13
	
	// Fechamos os dois arquivos
	fclose(entrada);                                                                                                //SYSCALL 14
	fclose(saida);	                                                                                                //SYSCALL 15
	
}
