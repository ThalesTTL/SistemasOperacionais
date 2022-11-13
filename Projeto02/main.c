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
#include <time.h>

// defines 100 threads to work
#define NUM_THREADS 100

// 64kB stack
#define FIBER_STACK 1024 * 64

struct c {
  int balance;
};

typedef struct c account;
account from, to, prints;
int value, aux, count = 0;
long tid[NUM_THREADS];

//---------------//---------------//---------------//---------------//---------------//---------------//
// Functions that are used in the main. //
//---------------//---------------//---------------//---------------//---------------//---------------//

// function for printing the balance in both accounts when transfer succeds
void print_success() {
  printf("|--------------------------------------|\n");
  printf("|Transfer done successfully!           |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
  printf("Transfering %d...\n", value);
}

// function for printing the balance in both accounts when transfer fails
void print_fail() {
  printf("|--------------------------------------|\n");
  printf("|Transfer failed!                      |\n");
  printf("|Balance in c1: %-5d                  |\n", from.balance);
  printf("|Balance in c2: %-5d                  |\n", to.balance);
  printf("|--------------------------------------|\n\n\n");
  printf("Transfering %d...\n", value);
}

// exchanges 'to' and 'from'
void *transfer1(void *arg) {
  int i, countT1 = 0;
  while (1) {
    if (from.balance >= value) {
      from.balance -= value;
      to.balance += value;

      printf("Account 1 -> Account 2\n");
      printf("Transfering %d...\n", value);
      print_success();
      value = (rand() % 20) + 1; // recalculates the value from 1 to 20
      break;
    } else if (countT1 > rand() % 5) {
      printf("Insuficient funds! Transfer aborted.\n");
      break;
    }
    countT1++;
    sleep(2);
  }
  return 0;
}

void *transfer2(void *arg) {
  int i, countT2 = 0;
  while (1) {
    if (to.balance >= value) {
      to.balance -= value;
      from.balance += value;

      printf("Account 2 -> Account 1\n");
      printf("Transfering %d...\n", value);
      print_success();
      value = (rand() % 20) + 1; // recalculates the value from 1 to 20
      break;
    } else if (countT2 > rand() % 5) {
      printf("Insuficient funds! Transfer aborted.\n");
      countT2++;
      break;
    }
    countT2++;
    sleep(2);
  }
  return 0;
}

//---------------//---------------//---------------//---------------//---------------//---------------//
// Main function.                                                                                     //
//---------------//---------------//---------------//---------------//---------------//---------------//

int main(int argc, char *argv[]) {
  pid_t pid;
  int i, rc, value;
  void *status;
  long t;
  pthread_t threads[NUM_THREADS];
  void *stack;
  int array[NUM_THREADS];

  srand(time(NULL)); // inicializes the seed for rand as NULL for different
                     // results in different runs

  // all accounts start with 300 currency
  from.balance = 300;
  to.balance = 300;

  value =
      (rand() % 20) +
      1; // aleatory number between 1 and 20 that signifies the transfer value
  for (t = 0; t < NUM_THREADS; i++) {
    t = t + 1;
    tid[t] = t;
  }

  for (t = 0; t < NUM_THREADS; t++) {
    if (t < NUM_THREADS / 2) { // divide the threads 50/50
      pthread_create(&threads[t], NULL, transfer1, (void *)tid[t]);
    } else {
      pthread_create(&threads[t], NULL, transfer2, (void *)tid[t]);
    }
  }
  // iniciates the threads
  for (t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], &status);
  }

  // stop the threads
  printf("Transfers done and memory freed!\n");
  pthread_exit(NULL);

  return 0;
}
