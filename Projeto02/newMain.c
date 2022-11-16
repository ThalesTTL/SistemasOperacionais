#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include <malloc.h>
// #include <stdbool.h>

// A quantidade de Threads que existem no programa.
#define NUM_THREADS 100

// Essa struct representa as contas bancárias do nosso sistema.
typedef struct c{
    int saldo;
} conta; 

// Contas bancárias
conta c1, c2;
// Valor que será transferido entre contas durante uma transação.
int valorTransferencia
long tid[NUM_THREADS]

// Declaração de Funções

// Imprime o saldo bancário de ambas as contas, quando a transferência for bem sucedida.
void print_sucesso();
// Imprime o saldo bancário de ambas as contas, quando a transferência falhar.
void print_falha();
// Efetua uma transferência bancária da conta c1 para a conta c2.
void *transferencia1(void *arg);
// Efetua uma transferência bancária da conta c2 para a conta c1.
void *transferencia2(void *arg);

int main(int argc, char *argv[]){
    
}
