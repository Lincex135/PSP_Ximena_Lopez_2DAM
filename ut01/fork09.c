#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 b) Si eliminamos la instrucción sleep():
    No se puede asegurar ningún orden de terminación, porque los tres hijos
    (P2, P3 y P4) hacen lo mismo y no tardan nada, así que depende del orden 
    que en el que el sistema operativo decida ejecutarlos.
*/

void main()
{
  pid_t pid2, pid3, pid4;

  // P2: espera 5 segundos
  pid2 = fork();
  if (pid2 == -1)
  {
    printf("ERROR. No se ha podido crear el proceso hijo.");
    exit(-1);
  }
  if (pid2 == 0)
  {
    printf("P2 (PID %d) comienza\n", getpid());
    sleep(5);
    printf("P2 (PID %d) termina\n", getpid());
    exit(0);
  }

  // P3: espera 2 segundos
  pid3 = fork();
  if (pid3 == -1)
  {
    printf("ERROR. No se ha podido crear el proceso hijo.");
    exit(-1);
  }
  if (pid3 == 0)
  {
    printf("P3 (PID %d) comienza\n", getpid());
    sleep(2);
    printf("P3 (PID %d) termina\n", getpid());
    exit(0);
  }

  // P4: espera 4 segundos
  pid4 = fork();
  if (pid4 == -1)
  {
    printf("ERROR. No se ha podido crear el proceso hijo.");
    exit(-1);
  }
  if (pid4 == 0)
  {
    printf("P4 (PID %d) comienza\n", getpid());
    sleep(4);
    printf("P4 (PID %d) termina\n", getpid());
    exit(0);
  }

  // P1 (padre): espera a los tres hijos
  wait(NULL);
  wait(NULL);
  wait(NULL);
  printf("Soy P1 (PID %d): mis tres hijos han terminado\n", getpid());
  exit(0);
}