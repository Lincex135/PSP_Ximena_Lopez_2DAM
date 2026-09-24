#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    printf("Inicio\n");
    pid_t pid = fork();

    /*
     * Aquí se crea un nuevo proceso.
     *
     * A partir del fork existen 2 procesos:
     * - El padre
     * - El hijo
     *
     * Los dos continúan ejecutando el programa desde la siguiente instrucción.
     */

    printf("Después del fork\n");
    if (pid == 0)
    {
        // Este código lo ejecuta el HIJO
        printf("Soy el hijo\n");
    }
    else
    {
        // Este código lo ejecuta el PADRE
        printf("Soy el padre\n");
    }

    // Tanto el padre como el hijo llegan aquí, por lo que "Fin" se muestra 2 veces.

    printf("Fin\n");
}

/*
 * El orden de Inicio es siempre el primero.
 * Después del fork(), padre e hijo se ejecutan de forma independiente,
 * por lo que los mensajes del padre y del hijo pueden aparecer en distinto orden.
 */