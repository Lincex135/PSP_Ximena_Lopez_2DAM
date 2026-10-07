#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    pid_t pid2, pid3, pid4, pid5;
    int acumulado = getpid(); // P1 define acumulado con su PID

    printf("Soy P1, PID %d, acumulado = %d\n", getpid(), acumulado);

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
            printf("Soy P2, PID %d (par): acumulado + 10 = %d\n", getpid(), acumulado + 10);
        else
            printf("Soy P2, PID %d (impar): acumulado - 100 = %d\n", getpid(), acumulado - 100);

        pid5 = fork();
        if (pid5 == -1)
        {
            printf("ERROR. No se ha podido crear el proceso hijo.");
            exit(-1);
        }
        if (pid5 == 0)
        {
            // P5
            if (getpid() % 2 == 0)
                printf("Soy P5, PID %d (par): acumulado + 10 = %d\n", getpid(), acumulado + 10);
            else
                printf("Soy P5, PID %d (impar): acumulado - 100 = %d\n", getpid(), acumulado - 100);
            exit(0);
        }
        wait(NULL); // P2 espera a P5
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
            printf("Soy P3, PID %d (par): acumulado + 10 = %d\n", getpid(), acumulado + 10);
        else
            printf("Soy P3, PID %d (impar): acumulado - 100 = %d\n", getpid(), acumulado - 100);

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
                printf("Soy P4, PID %d (par): acumulado + 10 = %d\n", getpid(), acumulado + 10);
            else
                printf("Soy P4, PID %d (impar): acumulado - 100 = %d\n", getpid(), acumulado - 100);
            exit(0);
        }
        wait(NULL); // P3 espera a P4
        exit(0);
    }

    wait(NULL); // P1 espera a un hijo
    wait(NULL); // P1 espera al otro hijo
    exit(0);
}