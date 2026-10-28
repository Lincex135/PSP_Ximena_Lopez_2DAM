#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // P2 (hijo) -> P1 (padre): el DNI
    int pipe2[2]; // P1 (padre) -> P2 (hijo): la letra
    pid_t pid;

    // Creamos los dos pipes
    pipe(pipe1);
    pipe(pipe2);

    // Creamos el proceso hijo
    pid = fork();

    if (pid == 0) {
        // HIJO (P2): pide el DNI, lo escribe en pipe1 y lee la letra de pipe2
        close(pipe1[0]); // No lee de pipe1
        close(pipe2[1]); // No escribe en pipe2

        int dni;
        char letra;

        printf("Introduce el número de tu DNI: ");
        scanf("%d", &dni);

        write(pipe1[1], &dni, sizeof(dni));

        read(pipe2[0], &letra, sizeof(letra));
        printf("la letra del NIF es %c\n", letra);

        close(pipe1[1]);
        close(pipe2[0]);
    }
    else {
        // PADRE (P1): lee el DNI de pipe1, calcula la letra y la escribe en pipe2
        close(pipe1[1]); // No escribe en pipe1
        close(pipe2[0]); // No lee de pipe2

        int dni;
        char letras[] = "TRWAGMYFPDXBNJZSQVHLCKE";
        char letra;

        read(pipe1[0], &dni, sizeof(dni));

        letra = letras[dni % 23];

        write(pipe2[1], &letra, sizeof(letra));

        close(pipe1[0]);
        close(pipe2[1]);
        wait(NULL);
    }

    return 0;
}
