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
        printf("Nombre del alumno: Ximena López\n");
    }
    else
    {
        wait(NULL);

        printf("PID del hijo: %d\n", pid);
        printf("PID del padre: %d\n", getpid());
    }
}