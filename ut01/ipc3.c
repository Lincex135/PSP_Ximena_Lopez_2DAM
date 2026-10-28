#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int numeros[2];
    pid_t pid;

    // Creamos el pipe
    pipe(fd);

    // Creamos el proceso hijo
    pid = fork();

    if (pid == 0) {
        // HIJO: genera dos numeros aleatorios y los escribe
        close(fd[0]); 

        time_t t;
        srand((unsigned) time(&t));

        // rand() % 50 da de 0 a 49, sumando 1 obtenemos de 1 a 50
        numeros[0] = rand() % 50 + 1;
        numeros[1] = rand() % 50 + 1;

        write(fd[1], numeros, sizeof(numeros));

        close(fd[1]);
    }
    else {
        // PADRE: lee los numeros y muestra las operaciones
        close(fd[1]);

        read(fd[0], numeros, sizeof(numeros));

        printf("%d + %d = %d\n", numeros[0], numeros[1], numeros[0] + numeros[1]);
        printf("%d - %d = %d\n", numeros[0], numeros[1], numeros[0] - numeros[1]);
        printf("%d * %d = %d\n", numeros[0], numeros[1], numeros[0] * numeros[1]);
        printf("%d / %d = %d\n", numeros[0], numeros[1], numeros[0] / numeros[1]);

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}
