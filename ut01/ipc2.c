#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char mensaje[10];
    pid_t pid;

    // Creamos el pipe
    pipe(fd);

    // Creamos el proceso hijo
    pid = fork();

    if (pid == 0) {
        // HIJO: lee los numeros y los suma
        close(fd[1]);

        int suma = 0;

        read(fd[0], mensaje, sizeof(mensaje));

        do {
            if (strcmp(mensaje, "+") != 0) {
                suma = suma + atoi(mensaje);
                read(fd[0], mensaje, sizeof(mensaje));
            }
        } while (strcmp(mensaje, "+") != 0);

        printf("La suma total es igual a: %d\n", suma);

        close(fd[0]);
    }
    else {
        // PADRE: pide los numeros por teclado y los escribe en el pipe
        close(fd[0]);

        do {
            printf("Introduce un numero (+ para terminar): ");
            scanf("%9s", mensaje);

            write(fd[1], mensaje, strlen(mensaje) + 1);

        } while (strcmp(mensaje, "+") != 0);

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
