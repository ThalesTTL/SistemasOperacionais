/*
  Luiz Gabriel Profirio Mendes      TIA: 42082293
  Thales Torres Lopes               TIA: 32135513
  Victor Silva Fernandes            TIA: 32163967
*/

// Projeto feito para rodar em Linux (Replit) //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define PENSANDO 0
#define FAMINTO 1
#define COMENDO 2

int i, NumeroDeFilosofos, tempoComendo, tempoPensando, estado[];

//semáforos
sem_t mutex;
sem_t sem_fil[100];

pthread_t *thread;

void mostrar ();
void *filosofo (void *j);
void pegarGarfo (int i);
void devolverGarfo (int i);
void intencao (int i);
void pensar ();
void comer ();
  
int main()
{
  NumeroDeFilosofos = 5;
  tempoPensando = 4;
  tempoComendo = 2;
  
  //Inicializa o estado
  for (i = 0; i < NumeroDeFilosofos; i++)
    {
      estado[i] = 0;
    }
  mostrar ();
  pthread_t thread[1000];

  //inicia os semáforos
  sem_init (&mutex, 0, 1);

  for (i = 1; i <= NumeroDeFilosofos; i++)
    {
      sem_init (&sem_fil[i], 0, 0);
    }

  //cria as threads(filosofos)
  for (i = 1; i <= NumeroDeFilosofos; i++)
    {
      pthread_create (&thread[i], NULL, filosofo, &i);
    }

  //faz um join nas threads
  for (i = 1; i <= NumeroDeFilosofos; i++)
    {
      pthread_join (thread[i], NULL);

    }
  return 0;
}


//Calcula a posição do filosófo a esquerda
int calcularEsquerda (int meio, int total)
{
  int esquerda;
  esquerda = (meio + total - 1) % total;
  return esquerda;
}

//Calcula a posição do filósofo a direita
int calcularDireita (int meio, int total)
{
  int direita;
  direita = (meio + 1) % total;
  return direita;
}

//Funcao que mostra o estado dos filósofos
void mostrar ()
{
  for (i = 1; i <= NumeroDeFilosofos; i++)
    {
      if (estado[i] == PENSANDO)
      	{
      	  printf ("O filósofo %d está pensando...\n", i);
      	}
      if (estado[i] == FAMINTO)
      	{
      	  printf ("O filósofo %d está com fome...\n", i);
      	}
      if (estado[i] == COMENDO)
      	{
      	  printf ("O filósofo %d está comendo!\n", i);
      	}
    }
  printf ("\n");
  sleep(3);
}

//Ação do filósofo
void *filosofo (void *j)
{
  //Determina o número do filósofo
  int i = *(int *) j;
  //Roda infinitamente
  while (1)
    {
      pensar (i);
      pegarGarfo (i);
      comer (i);
      devolverGarfo (i);
    }
}

//A thread(filósofo) espera um tempo aleatório pensando ou comendo
void
pensar ()
{
  estado[i] = PENSANDO;
  usleep (tempoPensando);
}
//A thread muda seu estado para faminto e tenta pegar os talheres
void pegarGarfo (int i)
{
  sem_wait (&mutex);		      //Pega o semáforo pra si
  estado[i] = FAMINTO;		    //Seta que está com fome
  mostrar ();			            //Mostra o estado dos outros filósofos
  intencao (i);			          //Tenta pegar os garfos pra comer
  sem_post (&mutex);		      //Libera o semáforo
  sem_wait (&sem_fil[i]);	    //Atualiza seu próprio semáforo
}

//Função que testa se o filósofo pode comer
void intencao (int i)
{
  int esquerda, direita;
  esquerda = calcularEsquerda (i, NumeroDeFilosofos);
  direita = calcularDireita (i, NumeroDeFilosofos);
  if (estado[i] == FAMINTO && estado[esquerda] != COMENDO && estado[direita] != COMENDO)
    {
      estado[i] = COMENDO;
      mostrar();
      sem_post (&sem_fil[i]);
    }
}
//A thread muda seu estado para pensando e libera os talheres
void devolverGarfo (int i)
{
  int esquerda, direita;
  sem_wait (&mutex);
  estado[i] = PENSANDO;
  mostrar ();
  esquerda = calcularEsquerda (i, NumeroDeFilosofos);
  direita = calcularDireita (i, NumeroDeFilosofos);
  sem_post (&mutex);
}

void
comer ()
{
  usleep (tempoComendo);
}
