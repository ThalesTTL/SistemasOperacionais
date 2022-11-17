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
// Defines, Includes and creation of variables. //
//---------------//---------------//---------------//---------------//---------------//---------------//

#define _GNU_SOURCE
#include <malloc.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

// defines 100 threads to work.
#define NUM_THREADS 100

struct c {
  int balance;
};

typedef struct c account;
account from, to;
int value;
long tid[NUM_THREADS];

//---------------//---------------//---------------//---------------//---------------//---------------//
// Functions that are used in the main. //
//---------------//---------------//---------------//---------------//---------------//---------------//

// function for printing the balance in both accounts when transfer success.
void print_success() {
  printf("|--------------------------------------|\n");
  printf("|Transfer done successfully!           |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
}

// function for printing the balance in both accounts when transfer fails.
void print_fail() {
  printf("|--------------------------------------|\n");
  printf("|Transfer failed!                      |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
}

// exchanges 'to' and 'from'
void *transfer1(void *arg) {
  int i, countT1 = 0;
  while (1) {
    printf("Account 1 -> Account 2\n");
    printf("Transfering %d...\n", value);
    if (from.balance >= value) {
      from.balance -= value;
      to.balance += value;
      print_success();
    
      value = (rand() % 20) + 1; // recalculates the value from 1 to 20.
      break;
    } else if (countT1 > rand() % 5) {
      printf("Insuficient funds! Transfer aborted.\n");
      break;
    }
    countT1++;
    usleep(1000);
  }
  return 0;
}

void *transfer2(void *arg) {
  int i, countT2 = 0;
  while (1) {
    printf("Account 2 -> Account 1\n");
    printf("Transfering %d...\n", value);
    if (to.balance >= value) {
      to.balance -= value;
      from.balance += value;
      print_success();
        
      value = (rand() % 20) + 1; // recalculates the value from 1 to 20.
      break;
    } else if (countT2 > rand() % 5) {
      printf("Insuficient funds! Transfer aborted.\n");
      countT2++;
      break;
    }
    countT2++;
    usleep(10000);
  }
  return 0;
}

//---------------//---------------//---------------//---------------//---------------//---------------//
// Main function.                                                                                     //
//---------------//---------------//---------------//---------------//---------------//---------------//

int main(int argc, char *argv[]) {
  pid_t pid;
  int i, rc;
  void *status;
  long t;
  pthread_t threads[NUM_THREADS];


  srand(time(NULL)); // inicializes the seed for rand as NULL for different.
                     // results in different runs.

  // all accounts start with 300 currency.
  from.balance = 300;
  to.balance = 300;

  value = (rand() % 20) + 1; // aleatory number between 1 and 20 that signifies the transfer value.
  for (t = 0; t < NUM_THREADS; t++) {
    tid[t] = t;
  }

  for (t = 0; t < NUM_THREADS; t++) {
    if (t%2 == 1) { // divide the threads 50/50.
      pthread_create(&threads[t], NULL, transfer1, (void *)tid[t]);
    } else {
      pthread_create(&threads[t], NULL, transfer2, (void *)tid[t]);
    }
  }
  // iniciates the threads.
  for (t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], &status);
  }

  printf("\n\n\nFinal Results:\n");
  printf("|--------------------------------------|\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n");
  // stop the threads.
  pthread_exit(NULL);
  printf("Transfers done and memory freed!\n");

  return 0;
}
