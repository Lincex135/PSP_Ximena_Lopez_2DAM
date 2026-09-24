#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Soy el proceso HIJO\n");
        printf("Mi PID es: %d\n", getpid());
        printf("El PID de mi padre es: %d\n", getppid());
    }
    else
    {
        wait(NULL);

        printf("Soy el proceso PADRE\n");
        printf("Mi PID es: %d\n", getpid());
        printf("Mi hijo tenía el PID: %d\n", pid);
        printf("El proceso hijo ha terminado\n");
    }
}