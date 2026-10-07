#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    pid_t pid2, pid3, pid4;

    // P1
    printf("Soy P1, PID %d, PID de mi padre %d, suma %d\n", getpid(), getppid(), getpid() + getppid());

    pid2 = fork();
    if (pid2 == -1)
    {
        printf("ERROR. No se ha podido crear el proceso hijo.");
        exit(-1);
    }
    if (pid2 == 0)
    {
        // P2
        printf("Soy P2, PID %d, PID de mi padre %d, suma %d\n", getpid(), getppid(), getpid() + getppid());

        pid3 = fork();
        if (pid3 == -1)
        {
            printf("ERROR. No se ha podido crear el proceso hijo.");
            exit(-1);
        }
        if (pid3 == 0)
        {
            // P3
            printf("Soy P3, PID %d, PID de mi padre %d, suma %d\n", getpid(), getppid(), getpid() + getppid());

            pid4 = fork();
            if (pid4 == -1)
            {
                printf("ERROR. No se ha podido crear el proceso hijo.");
                exit(-1);
            }
            if (pid4 == 0)
            {
                // P4
                printf("Soy P4, PID %d, PID de mi padre %d, suma %d\n", getpid(), getppid(), getpid() + getppid());
                exit(0);
            }
            wait(NULL); // P3 espera a P4
            exit(0);
        }
        wait(NULL); // P2 espera a P3
        exit(0);
    }
    wait(NULL); // P1 espera a P2
    exit(0);
}