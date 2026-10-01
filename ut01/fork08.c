#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 b) Salida del código ORIGINAL (sin wait):
    "AAA" sale una sola vez y siempre la primera, porque se imprime antes de
    cualquier fork().
    Después salen "BBB" (una vez, del hijo 1001) y "CCC" (dos veces: una del
    padre 1000 y otra del hijo 1002, que también ejecuta el printf("CCC")).
    Esas tres líneas pueden salir en cualquier orden, por ejemplo:
      AAA / BBB / CCC / CCC     o     AAA / CCC / BBB / CCC   (u otras).
    Sí se podría producir otra salida, porque el sistema operativo decide el orden.
*/

void main()
{
  pid_t pid1, pid2;
  printf("AAA \n");
  pid1 = fork();
  if (pid1==0)
  {
    printf("BBB \n");
  }
  else
  {
    pid2 = fork();
    wait(NULL);          // c) el padre espera a un hijo
    wait(NULL);          // c) y al otro hijo
    printf("CCC \n");
  }
  exit(0);
}