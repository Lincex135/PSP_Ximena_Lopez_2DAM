#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

void main()
{
  int fd[2];
  char buffer[50];
  pid_t pid;
  time_t hora;
  char *fecha;

  // Creamos el pipe
  pipe(fd);

  // Se crea un proceso hijo
  pid = fork();

  if (pid == 0)
  {
    // HIJO: solo lee
    close(fd[1]);                       // Cierra el descriptor de escritura
    read(fd[0], buffer, 50);
    printf("Soy el proceso hijo con pid %d\n", getpid());
    printf("Fecha/hora: %s", buffer);   
    close(fd[0]);
  }
  else
  {
    // PADRE: solo escribe
    close(fd[0]);                       // Cierra el descriptor de lectura
    time(&hora);
    fecha = ctime(&hora);
    write(fd[1], fecha, strlen(fecha) + 1);
    close(fd[1]);
    wait(NULL);
  }
}