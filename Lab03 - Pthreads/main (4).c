#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

int NUM_OF_THREADS, local_m, local_n;
float* A;
float* x;
float* y;

void FillM(float A[], int rows, int cols);
void FillV(float x[], int rows);
void printM(float A[], int rows, int cols);
void printV(float x[], int rows);

void *Pth_mat_vect(void* rank);

int main(int argc, char* argv[]){
	if(argc != 4)
	{
		fputs("You need to pass M N NUM_OF_THREADS as arguments\n", stdout);
		return EXIT_FAILURE;
	}
	else
	{
		local_m = atoi(argv[1]);
		local_n = atoi(argv[2]);
		NUM_OF_THREADS = atoi(argv[3]);
	}

	srand(time(NULL));

	int i, _error;

	pthread_t* threads = (pthread_t *)malloc(NUM_OF_THREADS * sizeof(pthread_t));

	A = (float *) malloc(local_m * local_n * sizeof(float));
	x = (float *) malloc(local_n * sizeof(float));
	y = (float *) malloc(local_m * sizeof(float));


	FillM(A, local_m, local_n);

	FillV(x, local_n);


	// Creamos los threads
	for(i = 0; i < NUM_OF_THREADS; i++)
	{
		_error = pthread_create(&threads[i], NULL,
						Pth_mat_vect, &i);

		if (_error){
		  fprintf(stderr, "error: pthread_create, rc: %d\n", _error);
		  return EXIT_FAILURE;
		}
	}



	for (i = 0; i < NUM_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	fprintf(stdout, "SIZE: %d x %d AND %d THREADS\n", local_m, local_n, NUM_OF_THREADS);

	if(local_m < 6 && local_m < 6)
	{
		puts("RES PARALELO:\n");
		printV(y, local_m);
	}

	free(A);
	free(x);
	free(y);
	free(threads);
  return 0;
}

void FillM(float A[], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++) 
    	for (j = 0; j < cols; j++)
    		A[i * cols + j] = rand() % 1;
}

void FillV(float x[], int rows)
{
	int i;
	for (i = 0; i < rows; i++) 
		x[i] = rand() % 1;
}

void printM(float A[], int rows, int cols) {
   int	i, j;

   for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++)
         printf("%.2f ", A[i*cols + j]);
      printf("\n");
   }
}

void printV(float x[], int rows) {
   int   i;

   for (i = 0; i < rows; i++)
      printf("%.5f ", x[i]*1000);
   printf("\n");
} 

void *Pth_mat_vect(void* rank) {
   	long my_rank = (long) rank;
    int my_first_row = my_rank * local_m;
    int my_last_row = my_first_row + (my_rank+1)*local_m - 1;
    int i, j;
	for (i = my_first_row; i <= my_last_row; i++) {
	  y[i] = 0.0;
	  for (j = 0; j < local_n; j++)
	      //y[i] += A[i][j]*x[j];
        y[i] += A[i*local_m+j]*x[j];
	}
   return NULL;
} 
