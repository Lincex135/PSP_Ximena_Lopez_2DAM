#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t pid1, pid2;

    // P1 crea a P2
    pid1 = fork();

    if (pid1 == 0)
    {
        // P2
        printf("Soy el proceso P2\n");
        printf("Voy a dormir 10secs\n");
        sleep(10);
        printf("Despierto\n");
    }
    else
    {
        // P1 crea a P3
        pid2 = fork();

        if (pid2 == 0)
        {
            // P3
            printf("Soy el proceso P3\n");
            printf("Mi PID es: %d\n", getpid());
            printf("El PID de mi padre es: %d\n", getppid());
        }
        else
        {
            // P1 espera a que terminen P2 y P3
            wait(NULL);
            wait(NULL);
        }
    }
}