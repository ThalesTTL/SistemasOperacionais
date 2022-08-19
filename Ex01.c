/*
Luiz Gabriel Profirio Mendes      TIA: 42082293
Thales Torres Lopes               TIA: 32135513
Victor Silva Fernandes            TIA: 32163967
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>


int main (void) {
  char arquivo[50];
  printf("Digite o nome do arquivo: "); 
  scanf("%s", arquivo);
  
  printf("%s", arquivo);
  
  
  FILE *entrada;
  entrada = fopen (arquivo, "r");
  if (entrada == NULL) {
    printf ("\nNão encontrei o arquivo!\n");
    exit (EXIT_FAILURE);
  }
  struct stat sb;
  stat(arquivo, &sb);

  char *file_contents = malloc(sb.st_size);

  while (fscanf(entrada, "%[^\n] ", file_contents) != EOF) {
    printf("> %s\n", file_contents);
  }
  
  fclose (entrada);
  return EXIT_SUCCESS;
  
}