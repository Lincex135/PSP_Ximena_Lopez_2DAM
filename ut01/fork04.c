#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t pid1, pid2;

    // Crear el primer hijo P2
    pid1 = fork();

    if (pid1 == 0)
    {
        // Proceso P2
        printf("Soy P2\n");
        printf("Mi PID es: %d\n", getpid());
        printf("El PID de mi padre es: %d\n", getppid());

        sleep(3);
    }
    else
    {
        // El padre crea el segundo hijo P3
        pid2 = fork();

        if (pid2 == 0)
        {
            // Proceso P3
            printf("Soy P3\n");
            printf("Mi PID es: %d\n", getpid());
            printf("El PID de mi padre es: %d\n", getppid());

            sleep(1);
        }
        else
        {
            // El padre espera a que terminen los dos hijos
            wait(NULL);
            wait(NULL);

            printf("Todos mis hijos han terminado\n");
        }
    }
}