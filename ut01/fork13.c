#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    pid_t pid2, pid3, pid4, pid5, pid6;
    pid_t abuelo; // PID del abuelo del proceso actual

    // P1: no tiene abuelo
    printf("Soy P1, PID %d, no tengo abuelo\n", getpid());

    pid2 = fork();
    if (pid2 == -1)
    {
        printf("ERROR. No se ha podido crear el proceso hijo.");
        exit(-1);
    }
    if (pid2 == 0)
    {
        // P2: su padre es P1, no tiene abuelo
        printf("Soy P2, PID %d, no tengo abuelo\n", getpid());
        abuelo = getppid(); // PID de P1: será el abuelo de P3 y P4

        pid3 = fork();
        if (pid3 == -1)
        {
            printf("ERROR. No se ha podido crear el proceso hijo.");
            exit(-1);
        }
        if (pid3 == 0)
        {
            // P3
            printf("Soy P3, PID %d, el PID de mi abuelo es %d\n", getpid(), abuelo);
            abuelo = getppid(); // PID de P2: será el abuelo de P5

            pid5 = fork();
            if (pid5 == -1)
            {
                printf("ERROR. No se ha podido crear el proceso hijo.");
                exit(-1);
            }
            if (pid5 == 0)
            {
                // P5
                printf("Soy P5, PID %d, el PID de mi abuelo es %d\n", getpid(), abuelo);
                exit(0);
            }
            wait(NULL); // P3 espera a P5
            exit(0);
        }

        pid4 = fork();
        if (pid4 == -1)
        {
            printf("ERROR. No se ha podido crear el proceso hijo.");
            exit(-1);
        }
        if (pid4 == 0)
        {
            // P4
            printf("Soy P4, PID %d, el PID de mi abuelo es %d\n", getpid(), abuelo);
            abuelo = getppid(); // PID de P2: será el abuelo de P6

            pid6 = fork();
            if (pid6 == -1)
            {
                printf("ERROR. No se ha podido crear el proceso hijo.");
                exit(-1);
            }
            if (pid6 == 0)
            {
                // P6
                printf("Soy P6, PID %d, el PID de mi abuelo es %d\n", getpid(), abuelo);
                exit(0);
            }
            wait(NULL); // P4 espera a P6
            exit(0);
        }

        wait(NULL); // P2 espera a P3
        wait(NULL); // P2 espera a P4
        exit(0);
    }
    wait(NULL); // P1 espera a P2
    exit(0);
}