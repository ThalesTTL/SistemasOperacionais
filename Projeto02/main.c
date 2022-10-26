/*
  Thales Torres Lopes ----------------- TIA: 32135513

  Luiz Gabriel Profirio Mendes -------- TIA: 42082293

  Victor Silva Fernandes -------------- TIA: 32163967

  ------------------- References --------------------
  https://www.modernescpp.com/index.php/race-condition-versus-data-race
  https://hpc-tutorials.llnl.gov/posix/
*/

//---------------//---------------//---------------//---------------//---------------//---------------//
// Defines, Includes and creation of variables.                                                       //
//---------------//---------------//---------------//---------------//---------------//---------------//

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
#define NUM_THREADS 5

int thread_count;

struct c {
  int balance;
};

typedef struct c account;
account from, to, prints;
int value, aux, count = 0;
long tid[NUM_THREADS];

//---------------//---------------//---------------//---------------//---------------//---------------//
// Functions that are used in the main.                                                               //
//---------------//---------------//---------------//---------------//---------------//---------------//

// function for printing the balance in both accounts
void print_balance(){
  printf("|--------------------------------------|\n");
  printf("|Transfer done successfully!           |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n");
  }
  
// the threads will execute this function
void *transfer(void *arg) {
  if (from.balance >= value) {
    from.balance -= value;
    to.balance += value;
    value = rand() % 20;
  }
  print_balance();
  return 0;
}
  
// exchanges 'to' and 'from'
void exchange() {
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
// Main function.                                                                                     //
//---------------//---------------//---------------//---------------//---------------//---------------//

int main(int argc, char* argv[]) {
  void *stack;
  pid_t pid;
  int i, rc;
  long t;
  pthread_t threads[NUM_THREADS];
  
  srand(time(NULL)); // inicializes the seed for rand as NULL for different results in different runs

  // all accounts start with 100 currency
  from.balance = 100;
  to.balance = 100;


  
  value = rand() % 20; // aleatory number between 0 and 20 that signifies the transfer value 
  printf("Transfering %d...\n", value); 
  for (t = 0; t<thread_count; t++){
    tid[t] = t;
    rc = pthread_create(&threads[t], NULL, transfer, (void *) tid[t]);
    if(rc){
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  // stop the threads
  printf("Transfers done and memory freed!\n");
  pthread_exit(NULL);
  return 0;
}
