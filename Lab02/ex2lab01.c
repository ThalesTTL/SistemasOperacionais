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
	
	printf("Insira o nome do arquivo de entrada: ");								//SYSCALL
	scanf("%s", nomeArquivoEntrada);										//SYSCALL
	
	printf("Insira o nome do arquivo de saida: ");									//SYSCALL
	scanf("%s", nomeArquivoSaida);											//SYSCALL
	
	// Abrimos o arquivo de entrada
	FILE *entrada = fopen(nomeArquivoEntrada, "r");
	if(entrada == NULL){
		printf("Arquivo nao encontrado.");									//SYSCALL
		return -1;
	}
	
	// Criamos um arquivo de saida, do tipo 'w', para poder receber e escrever o conteudo lido do arquivo de entrada.
	FILE *saida = fopen(nomeArquivoSaida, "w");
	if(saida == NULL){
		printf("Erro ao criar o arquivo");									//SYSCALL
		return -1;
	}
	
	while(true){
		char linha[100]; // criamos um vetor de caracteres para armazenar o conteudo das linhas do arquivo
		
		// efetuamos a leitura de linha a linha do arquivo
		// caso a leitura chegue ate o final do arquivo, ele retorna um ponteiro NULL
		char *ptr = fgets(linha, 100, entrada);
		// se o ponteiro apontar para NULL, encerra o while
		if(ptr == NULL)
			break;

		// imprimimos a linha no arquivo de saida.
		fprintf(saida, "%s", linha);										//SYSCALL
		
	}
	printf("\n'%s' foi copiado em um novo arquivo chamado '%s'", nomeArquivoEntrada, nomeArquivoSaida);		//SYSCALL
	
	// Fechamos os dois arquivos
	fclose(entrada);
	fclose(saida);	
	
}
