#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 a) Orden de ejecución:
    - P1 es siempre el primero en mostrar su mensaje (lo hace antes de crear a nadie)
      y siempre el último en terminar, porque espera a sus hijos.
    - P2 y P3 son hermanos: los dos se ejecutan a la vez, así que NO se puede
      asegurar cuál muestra su mensaje antes.
    - P4 siempre aparece después de P3 (es su hijo y no existe hasta que P3 lo crea),
      pero puede salir antes o después que P2.
    - P4 termina siempre antes que P3, y P3 y P2 antes que P1.
    Por tanto, NO será siempre el mismo orden: el sistema operativo decide
    qué proceso planifica primero. Los posibles órdenes de mensajes son:
      P1, P2, P3, P4   /   P1, P3, P2, P4   /   P1, P3, P4, P2
    Además, qué procesos muestran el PPID depende de si su PID es par o impar,
    y eso cambia en cada ejecución.
*/

void main()
{
    pid_t pid2, pid3, pid4;

    // P1
    if (getpid() % 2 == 0)
        printf("Soy P1, mi PID es %d y el PID de mi padre es %d\n", getpid(), getppid());
    else
        printf("Soy P1, mi PID es %d\n", getpid());

    pid2 = fork();
    if (pid2 == -1)
    {
        printf("ERROR. No se ha podido crear el proceso hijo.");
        exit(-1);
    }
    if (pid2 == 0)
    {
        // P2
        if (getpid() % 2 == 0)
            printf("Soy P2, mi PID es %d y el PID de mi padre es %d\n", getpid(), getppid());
        else
            printf("Soy P2, mi PID es %d\n", getpid());
        exit(0);
    }

    pid3 = fork();
    if (pid3 == -1)
    {
        printf("ERROR. No se ha podido crear el proceso hijo.");
        exit(-1);
    }
    if (pid3 == 0)
    {
        // P3
        if (getpid() % 2 == 0)
            printf("Soy P3, mi PID es %d y el PID de mi padre es %d\n", getpid(), getppid());
        else
            printf("Soy P3, mi PID es %d\n", getpid());

        pid4 = fork();
        if (pid4 == -1)
        {
            printf("ERROR. No se ha podido crear el proceso hijo.");
            exit(-1);
        }
        if (pid4 == 0)
        {
            // P4
            if (getpid() % 2 == 0)
                printf("Soy P4, mi PID es %d y el PID de mi padre es %d\n", getpid(), getppid());
            else
                printf("Soy P4, mi PID es %d\n", getpid());
            exit(0);
        }
        wait(NULL); // P3 espera a P4
        exit(0);
    }

    wait(NULL); // P1 espera a un hijo
    wait(NULL); // P1 espera al otro hijo
    exit(0);
}