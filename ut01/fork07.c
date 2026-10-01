#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 b) Salida del código ORIGINAL (sin wait):
    Primero sale "CCC" una sola vez, porque se imprime antes del fork().
    Después salen "AAA" (padre) y "BBB" (hijo), y su orden NO está garantizado:
      CCC / AAA / BBB     o     CCC / BBB / AAA
    Sí se podría producir otra salida, porque padre e hijo son dos procesos
    independientes y el sistema operativo decide cuál se ejecuta antes.
*/

void main()
{
  printf("CCC \n");
  if (fork()!=0)
  {
    wait(NULL);          // c) el padre espera a que el hijo termine
    printf("AAA \n");
  } else printf("BBB \n");
  exit(0);
}