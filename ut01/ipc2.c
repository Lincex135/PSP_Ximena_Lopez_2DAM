#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSGSIZE 10 // tamaño fijo de cada mensaje que viaja por el pipe

int main() {
    int fd[2];
    char mensaje[MSGSIZE];
    pid_t pid;

    // Creamos el pipe
    pipe(fd);

    // Creamos el proceso hijo
    pid = fork();

    if (pid == 0) {
        // HIJO: lee los numeros y los suma
        close(fd[1]); // Cierra el descriptor de escritura

        int suma = 0;

        read(fd[0], mensaje, MSGSIZE);
        while (strcmp(mensaje, "+") != 0) {
            printf("Numero a sumar: %s\n", mensaje);
            suma = suma + atoi(mensaje);
            read(fd[0], mensaje, MSGSIZE);
        }

        printf("Recibido carácter +\n");
        printf("La suma total es igual a: %d\n", suma);

        close(fd[0]);
    }
    else {
        // PADRE: pide los numeros por teclado y los escribe en el pipe
        close(fd[0]); // Cierra el descriptor de lectura

        do {
            printf("Introduce un numero (+ para terminar): ");
            scanf("%9s", mensaje);
            write(fd[1], mensaje, MSGSIZE);
        } while (strcmp(mensaje, "+") != 0);

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
