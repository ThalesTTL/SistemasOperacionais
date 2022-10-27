/*
  Thales Torres Lopes ----------------- TIA: 32135513

  Luiz Gabriel Profirio Mendes -------- TIA: 42082293

  Victor Silva Fernandes -------------- TIA: 32163967

  ------------------- References --------------------
  https://www.modernescpp.com/index.php/race-condition-versus-data-race
  https://hpc-tutorials.llnl.gov/posix/
  https://alvinalexander.com/programming/printf-format-cheat-sheet/
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

// defines 100 threads to work 
#define NUM_THREADS 2

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

// function for printing the balance in both accounts when transfer succeds
void print_balance1(){
  printf("|--------------------------------------|\n");
  printf("|Transfer done successfully!           |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
  printf("Transfering %d...\n", value);
  }

// function for printing the balance in both accounts when transfer fails
void print_balance2(){
  printf("|--------------------------------------|\n");
  printf("|Transfer failed!                      |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
  printf("Transfering %d...\n", value);
  }
  
// exchanges 'to' and 'from'
void *transfer1(void *arg) {
  while(1){
    if (from.balance >= value) {
      from.balance -= value;
      to.balance += value;
        
      value = (rand() % 19)+ 1; // recalculates the value from 1 to 20
      print_balance1();
    } 
    else {
      value = (rand() % 19)+ 1; // recalculates the value from 1 to 20
      print_balance2();
    }
  }
  return 0;
}

void *transfer2(void *arg) {
  while(1){
    if (to.balance >= value) {
      to.balance -= value;
      from.balance += value;
        
      value = (rand() % 19)+ 1; // recalculates the value from 1 to 20
      print_balance1();
    } 
    else {
      value = (rand() % 19)+ 1; // recalculates the value from 1 to 20
      print_balance2();
    }
  }
  return 0;
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
  pid_t pid;
  int i, rc, value;
  void *status;
  long t;
  pthread_t threads[NUM_THREADS];
  
  srand(time(NULL)); // inicializes the seed for rand as NULL for different results in different runs

  // all accounts start with 100 currency
  from.balance = 100;
  to.balance = 100;

  value = (rand() % 20) + 1; // aleatory number between 1 and 20 that signifies the transfer value  
  printf("Transfering %d...\n", value);
  for (t = 0; t < NUM_THREADS; t++){
    tid[t] = t;
    if (t % 2 > 0){ // divide the threads 50/50
      pthread_create(&threads[t], NULL, transfer1, (void *) tid[t]);
    }
    else {
      pthread_create(&threads[t], NULL, transfer2, (void *) tid[t]);
    }
    
    pthread_join(threads[t], &status);  
    }
    if(rc){
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  // stop the threads
  printf("Transfers done and memory freed!\n");
  pthread_exit(NULL);
  return 0;
}
