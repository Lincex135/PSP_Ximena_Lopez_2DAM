#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
  pid_t pid2, pid3;
  int i, suma;

  // P2: suma de 1 a 100
  pid2 = fork();
  if (pid2 == -1)
  {
    printf("ERROR. No se ha podido crear el proceso hijo.");
    exit(-1);
  }
  if (pid2 == 0)
  {
    suma = 0;
    for (i = 1; i <= 100; i++)
    {
      suma = suma + i;
    }
    printf("P2 (PID %d): suma de los numeros 1..100 = %d\n", getpid(), suma);
    exit(0);
  }

  // P3: suma de 101 a 200
  pid3 = fork();
  if (pid3 == -1)
  {
    printf("ERROR. No se ha podido crear el proceso hijo.");
    exit(-1);
  }
  if (pid3 == 0)
  {
    suma = 0;
    for (i = 101; i <= 200; i++)
    {
      suma = suma + i;
    }
    printf("P3 (PID %d): suma de los números 101..200 = %d\n", getpid(), suma);
    exit(0);
  }

  // P1 (padre): espera a todos
  wait(NULL);
  wait(NULL);
  printf("Todos los cálculos han finalizado.\n");
  exit(0);
}
