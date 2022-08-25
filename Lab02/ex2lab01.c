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
	
	printf("Insira o nome do arquivo de entrada: ");
	scanf("%s", nomeArquivoEntrada);
	
	printf("Insira o nome do arquivo de saida: ");
	scanf("%s", nomeArquivoSaida);
	
	// Abrimos o arquivo de entrada
	FILE *entrada = fopen(nomeArquivoEntrada, "r");
	if(entrada == NULL){
		printf("Arquivo nao encontrado.");
		return -1;
	}
	
	// Criamos um arquivo de saida, do tipo 'w', para poder receber o conteudo lido do arquivo de entrada
	FILE *saida = fopen(nomeArquivoSaida, "w");
	if(saida == NULL){
		printf("Erro ao criar o arquivo");
		return -1;
	}
	
	while(true){
		char linha[100];
		
		// Lemos cada linha do arquivo de entrada
		int k = fscanf(entrada, "%s", &linha);
		// Se nao ler nada, encerra o loop
		if(k < 1)
			break;
			
		// Imprimimos cada linha no arquivo de saida.
		fprintf(saida, "%s\n", linha);
		
	}
	printf("\n'%s' foi copiado em um novo arquivo chamado '%s'", nomeArquivoEntrada, nomeArquivoSaida);
	
	// Fechamos os dois arquivos
	fclose(entrada);
	fclose(saida);
		
	
}
