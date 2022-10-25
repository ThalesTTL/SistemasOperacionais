/*
  Thales Torres Lopes ----------------- TIA: 32135513

  Luiz Gabriel Profirio Mendes -------- TIA: 42082293

  Victor Silva Fernandes -------------- TIA: 32163967

  ------------------- References --------------------
  https://www.modernescpp.com/index.php/race-condition-versus-data-race
  https://hpc-tutorials.llnl.gov/posix/
*/

#define _GNU_SOURCE
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// 64kB stack
#define FIBER_STACK 1024 * 64

// defines 100 threads to work 
#define NUM_THREADS 100

int thread_count;

struct c {
  int balance;
};

typedef struct c account;
account from, to;
int value, aux, count = 0;

// the thread will execute this function
void *transfer(void *arg) {
  if (from.balance >= value) {
    from.balance -= value;
    to.balance += value;
    value = rand() % 20;
  }
  printf("Transfer done successfully!\n");
  printf("Money in c1: %d\n", from.balance);
  printf("Money in c2: %d\n", to.balance);
}

// exchanges 'to' and 'from'
void exchange(c1,c2) {
  aux = from.balance;
  from.balance = to.balance;
  to.balance = aux;
  count += 1;
}

// checks if order is correct
bool check() {
  if ((count % 2) > 0) {
    return false;
  } else {
    return true;
  }
}
//---------------//---------------//---------------//---------------//---------------//---------------//
int main(int argc, char* argv[]) {
  void *stack;
  pid_t pid;
  int i, rc;
  long t;
  //pthread_t* thread_handles; 
  pthread_t threads[NUM_THREADS];
  
  /*
  Get number of threads from command line 
  thread_count = strtol(argv[1], NULL, 10);      
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  */
  
  srand(time(NULL)); // inicializes the seed for rand as NULL for different results in different runs

  // all accounts start with 100 currency
  from.balance = 100;
  to.balance = 100;
  
  value = rand() % 20; // aleatory number between 0 and 20 that signifies the transfer value 
  printf("Transfering %d\n", value); 

  for (t = 0; t<thread_count; t++){
    rc = pthread_create(&threads[t], NULL, transfer, (void *)t);
    if(rc){
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  // free the malloc
  printf("Transfers done and memory freed.\n");
  pthread_exit(NULL);
  return 0;
}
