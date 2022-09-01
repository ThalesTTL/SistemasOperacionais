<h1> Sistemas Operacionais | Laboratório 02a </h1>

<hr>

<h2>Integrantes do Grupo</h2>
<ul>
  <li>Thales Torres Lopes | TIA: 32135513</li>
 
  <li>Luiz Gabriel Profirio Mendes | TIA: 42082293</li>
 
  <li>Victor Silva Fernandes | TIA: 32163967</li>
</ul>

<hr>

<h3>Código Analisado (Questão 1)</h3>
<code><pre>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    if (argc != 2){ /* check for valid number of command-line arguments */
      fprintf(stderr, "Usage: %s processes\n", argv[0]);
      return 1;
    }
    n = atoi(argv[1]);
    for (i = 1; i < n; i++)
      if (childpid = fork())
      break;
    fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
  }
</pre></code>

<h4>Código Analisado (Questão 2)</h4>
<code><pre>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    if (argc != 2){ /* check for valid number of command-line arguments */
      fprintf(stderr, "Usage: %s processes\n", argv[0]);
      return 1;
    }
    n = atoi(argv[1]);
    for (i = 1; i < n; i++)
      if (childpid = fork())
      break;
    fprintf(stdout, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
  }
</pre></code>

<h5>Perguntas e Respostas</h5>

<p>1)Rode o programa anterior para valores grandes de n. As mensagens sempre estarão ordenadas pelo valor de i?</p>
<p><b>R: As mensagens sempre estão ordenadas pois o i só aumenta por meio do 'for', que aumenta de 1 em 1 com o comando de 'i++'.</b></p>

<p>2) O que acontece se o programa anterior escreve-se as mensagens para sys.stdout, usando print, ao invés de para sys.stderr?</p>
<p><b>R: Não acontece nada, ele continua imprimindo no mesmo lugar.</b></p>



