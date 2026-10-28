#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // P1 (padre) -> P2 (hijo): el numero
    int pipe2[2]; // P2 (hijo) -> P1 (padre): el factorial
    pid_t pid;

    // Creamos los dos pipes
    pipe(pipe1);
    pipe(pipe2);

    // Creamos el proceso hijo
    pid = fork();

    if (pid == 0) {
        // HIJO (P2): lee de pipe1 y escribe en pipe2
        close(pipe1[1]); // No escribe en pipe1
        close(pipe2[0]); // No lee de pipe2

        int numero, i;
        int factorial = 1;

        read(pipe1[0], &numero, sizeof(numero));

        for (i = 1; i <= numero; i++) {
            factorial = factorial * i;
        }

        write(pipe2[1], &factorial, sizeof(factorial));

        close(pipe1[0]);
        close(pipe2[1]);
    }
    else {
        // PADRE (P1): escribe en pipe1 y lee de pipe2
        close(pipe1[0]); // No lee de pipe1
        close(pipe2[1]); // No escribe en pipe2

        int numero, resultado;
        time_t t;

        srand((unsigned) time(&t));
        numero = rand() % 11; // numero entre 0 y 10

        printf("El proceso padre genera el numero %d en el pipe1\n", numero);
        write(pipe1[1], &numero, sizeof(numero));

        read(pipe2[0], &resultado, sizeof(resultado));
        printf("El factorial calculado por el proceso hijo: %d != %d\n", numero, resultado);

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
