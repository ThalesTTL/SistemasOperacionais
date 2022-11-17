#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

// Quantidade de threads que existem no programa.
#define NUM_THREADS 100

// Representa as contas bancárias do nosso sistema.
typedef struct c{
    int saldo;
} conta; 

// Contas bancárias
conta c1, c2;
// Valor que será transferido entre as contas durante uma transação.
int valorTransferencia;
long tid[NUM_THREADS];

// Declaração de Funções

// Imprime o saldo bancário de ambas as contas quando a transferência for bem-sucedida.
void print_sucesso();
// Efetua uma transferência bancária da conta c1 para a conta c2.
void *transferencia1(void *arg);
// Efetua uma transferência bancária da conta c2 para a conta c1.
void *transferencia2(void *arg);

int main(int argc, char *argv[]){

    pthread_t threads[NUM_THREADS];

    // Inicializa o gerador de números aleatório com o valor da função time(NULL).
    // Dessa forma, a cada execução o valor da semente de geração será diferente.
    srand(time(NULL));

    // O saldo inicial das contas é de R$300,00.
    c1.saldo = 300;
    c2.saldo = 300;

    // A transferência será um valor entre 1 e 20.
    valorTransferencia = (rand() % 21);

    for(long t = 0; t < NUM_THREADS; t++){
        tid[t] = t;
    }

    // Criamos 100 Threads
    // 50 threads executarão a função 'transferencia1()'
    // 50 threads executarão a função 'transferencia2()'
    for(long t = 0; t < NUM_THREADS; t++){
        if(t % 2 == 1)
            pthread_create(&threads[t], NULL, transferencia1, (void *)tid[t]);
        else
            pthread_create(&threads[t], NULL, transferencia2, (void *)tid[t]);
    }
    
    // Executamos as 100 threads
    for(long t = 0; t < NUM_THREADS;  t++){
        pthread_join(threads[t], NULL);
    }

    printf("\n\n\nResultado final:\n");
    printf("|--------------------------------------|\n");
    printf("|Saldo de c1: %-5d                    |\n", c1.saldo);
    printf("|Saldo de c2: %-5d                    |\n", c2.saldo);
    printf("|--------------------------------------|\n");

    return 0;

}

void *transferencia1(void *arg){
    // Quantidade de vezes que a thread tentou realizar uma transferência
    int tentativas = 0;

    while(true){
        printf("Conta 1 -> Conta 2\n");
        printf("Transferindo %d...\n", valorTransferencia);
        
        if(c1.saldo >= valorTransferencia){
            // Efetue a transferência bancária...
            c1.saldo -= valorTransferencia;
            c2.saldo += valorTransferencia;
            // Imprima o novo saldo das duas contas...
            print_sucesso();

            // Recalcule o valor da transferência modificando o valor da variável global...
            valorTransferencia = (rand() % 21);
            break;
        } else if(tentativas > rand() % 5){
            printf("Saldo insuficiente! Transferencia cancelada.");
            break;
        }
        tentativas++;
        // A thread espera por 1s
        sleep(1);
    }
}

void *transferencia2(void *arg){
    // Quantidade de vezes que a thread tentou realizar uma transferência
    int tentativas = 0;

    while(true){
        printf("Conta 2 -> Conta 1\n");
        printf("Transferindo %d...\n", valorTransferencia);
        
        if(c2.saldo >= valorTransferencia){
            // Efetue a transferência bancária...
            c2.saldo -= valorTransferencia;
            c1.saldo += valorTransferencia;
            // Imprima o novo saldo das duas contas...
            print_sucesso();

            // Recalcule o valor da transferência modificando o valor da variável global...
            valorTransferencia = (rand() % 21);
            break;
        } else if(tentativas > rand() % 5){
            printf("Saldo insuficiente! Transferencia cancelada.");
            break;
        }
        tentativas++;
        // A thread espera por 1s
        sleep(1);
    }
}

void print_sucesso(){
    printf("|--------------------------------------|\n");
    printf("|Transferencia concluida com sucesso!  |\n");
    printf("|Saldo de c1: %-5d                    |\n", c1.saldo);
    printf("|Saldo de c2: %-5d                    |\n", c2.saldo);
    printf("|--------------------------------------|\n\n\n");
}
