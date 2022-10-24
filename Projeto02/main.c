/*
  Thales Torres Lopes ----------------- TIA: 32135513

  Luiz Gabriel Profirio Mendes -------- TIA: 42082293

  Victor Silva Fernandes -------------- TIA: 32163967

  ------------------- References --------------------
  https://www.modernescpp.com/index.php/race-condition-versus-data-race
*/

#define _GNU_SOURCE
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 64kB stack
#define FIBER_STACK 1024 * 64

int thread_count;

struct c {
  int balance;
};

typedef struct c account;
account from, to;
int value, aux, count = 0;

// The child thread will execute this function
int transfer(void *arg) {
  if (from.balance >= value) {
    from.balance -= value;
    to.balance += value;
    value = rand() % 20;
  }
  printf("Transfer done successfully!\n");
  printf("Money in c1: %d\n", from.balance);
  printf("Money in c2: %d\n", to.balance);
  return 0;
}

// Exchanges 'to' and 'from'
void exchange() {
  aux = from.balance;
  from.balance = to.balance;
  to.balance = aux;
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
//---------------//---------------//---------------//---------------//---------------//
int main(int argc, char* argv[]) {
  void *stack;
  pid_t pid;
  int i;
  long thread;
  pthread_t* thread_handles;
  // Get number of threads from command line 
  thread_count = strtol(argv[1], NULL, 10);      
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  
  // Allocate the stack
  //stack = malloc(FIBER_STACK);

  srand(time(NULL)); // inicializes the seed for rand as NULL for different results in different runs

  if (stack == 0) {
    perror("malloc: could not allocate stack");
    exit(1);
  }
  // All accounts start with 100 dollars
  from.balance = 100;
  to.balance = 100;
  
  value = rand() % 20; // Aleatory number between 0 and 20 that signifies the transfer value 
  printf("Transfering %d to account c2\n", value);  

  /*for (i = 0; i < 100; i++) {
    // Call the clone system call to create the child thread
    pid = clone(&transfer, (char *)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if (pid == -1) {
      perror("clone");
      exit(2);
    }
  }
  */ 
  // Free the stack
  //printf("Transfers done and memory freed.\n");
  //free(stack);
  return 0;
}
