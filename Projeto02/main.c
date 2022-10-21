/*
  Thales Torres Lopes ----------------- TIA: 32135513

  Luiz Gabriel Profirio Mendes -------- TIA: 42082293

  Victor Silva Fernandes -------------- TIA: 32163967

  ------------------- References --------------------
  https://www.modernescpp.com/index.php/race-condition-versus-data-race
*/

#define _GNU_SOURCE
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// 64kB stack
#define FIBER_STACK 1024 * 64

struct c {
  int saldo;
};

typedef struct c conta;
conta from, to;
int valor, aux, count = 0;

// The child thread will execute this function
int transferencia(void *arg) {
  if (from.saldo >= valor) {
    from.saldo -= valor;
    to.saldo += valor;
  }
  printf("Transfer done successfully!\n");
  printf("Money in c1: %d\n", from.saldo);
  printf("Money in c2: %d\n", to.saldo);
  return 0;
}

// Exchanges 'to' and 'from'
void exchange() {
  aux = from.saldo;
  from.saldo = to.saldo;
  to.saldo = aux;
  count += 1;
}

// Checks if order is correct
bool check() {
  if ((count % 2) > 0) {
    return false;
  } else {
    return true;
  }
}

int main(void) {
  void *stack;
  pid_t pid;
  int i;
  // Allocate the stack
  stack = malloc(FIBER_STACK);

  if (stack == 0) {
    perror("malloc: could not allocate stack");
    exit(1);
  }
  // Todas as contas começam com saldo 100
  from.saldo = 100;
  to.saldo = 100;
  for(i=0; i<5; i++){
    valor = rand() % 20; // talvez tenha que mudar
    printf("Transfering %d to account c2\n", valor);  
  }

  for (i = 0; i < 10; i++) {
    // Call the clone system call to create the child thread
    pid = clone(&transferencia, (char *)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if (pid == -1) {
      perror("clone");
      exit(2);
    }
  }
  // Free the stack
  free(stack);
  printf("Transfers done and memory freed.\n");
  return 0;
}
