#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()

/*
Pasos a seguir...
Creamos el pipe.
Creamos los subprocesos.
Queremos que todo lo que el subproceso 1 escriba a stdout, el
subproceso 2 lo lea desde stdin. Para ello, usando dup2:
Conectamos el descriptor de stdout del subproceso 1 al extremo de
escritura del pipe.
Conectamos el descriptor de stdin del subproceso 2 al extremo de
lectura del pipe.
Ejecutamos el comando ls -al en el subproceso 1.
Ejecutamos el comando wc -l en el subproceso 2.
*/

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
  dup2(pipe_fd[WRITE], STDOUT_FILENO); // Redirigir stdout al pipe
  close(pipe_fd[READ]);                // No se usa
  close(pipe_fd[WRITE]);               // Ya lo redirigimos
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
  dup2(pipe_fd[READ], STDIN_FILENO);  // Redirigir stdin al pipe
  close(pipe_fd[WRITE]);              // No se usa
  close(pipe_fd[READ]);               // Ya lo redirigimos
}

int main(int argc, char const* argv[]) {
  int pipe_fd[2];                     // creamos pipe
  pipe(pipe_fd);

  pid_t pid1 = fork();
  if (pid1 == 0) {
    ejecutar_hijo_1(pipe_fd);
  }

  pid_t pid2 = fork();
  if (pid2 == 0) {
    ejecutar_hijo_2(pipe_fd);
  }

  // Padre
  close(pipe_fd[READ]);
  close(pipe_fd[WRITE]);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

  return 0;
}

/*
🧷 waitpid(pid, status, options)

Sirve para esperar que un proceso hijo termine. En tu caso, el proceso padre (el main) espera a que los dos hijos (los que ejecutan ls y wc) terminen.

    pid: puede ser:

        El PID del hijo específico que querés esperar.

        -1: para esperar a cualquier hijo (como wait()).

    status: puntero a un entero donde se guarda el estado de salida del hijo (o NULL si no te importa).

    options: suele ser 0, pero podés poner flags como WNOHANG para no bloquear.

🔁 dup2(oldfd, newfd)

Hace que newfd se convierta en una copia de oldfd, cerrando newfd primero si ya estaba abierto. Es útil para redirigir entradas y salidas.
ejemplo clásico:

dup2(pipe_fd[WRITE], STDOUT_FILENO);

→ Ahora todo lo que se escriba por stdout va al pipe (en lugar de mostrarse en pantalla).


Para encadenar 3 comandos como en un shell (por ejemplo ls -al | grep txt | wc -l), tenés que usar 2 pipes, ya que cada pipe conecta solo dos procesos: 
el anterior escribe, el siguiente lee.

comando1 | comando2 | comando3
(ls -al) | (grep txt) | (wc -l)

2 pipes:

    pipe1 conecta comando1 → comando2

    pipe2 conecta comando2 → comando3

3 hijos (uno por comando)

Redirecciones con dup2 para cada uno

resumen visual:
ls -al     →     grep txt      →     wc -l
[Hijo 1]         [Hijo 2]            [Hijo 3]
 stdout          stdin | stdout      stdin
   │                │      │            │
   └── pipe1[1] ──▶ pipe1[0] └──▶ pipe2[1] ──▶ pipe2[0]


   un esquema simplificado seria 
   int pipe1[2]; // entre hijo1 y hijo2
int pipe2[2]; // entre hijo2 y hijo3
pipe(pipe1);
pipe(pipe2);

pid_t pid1 = fork();
if (pid1 == 0) {
  // Hijo 1: ls -al
  dup2(pipe1[WRITE], STDOUT_FILENO); // stdout -> pipe1
  close(pipe1[READ]);
  close(pipe1[WRITE]);
  close(pipe2[READ]);
  close(pipe2[WRITE]);
  execlp("ls", "ls", "-al", NULL);
  perror("execlp ls");
  exit(1);
}

pid_t pid2 = fork();
if (pid2 == 0) {
  // Hijo 2: grep txt
  dup2(pipe1[READ], STDIN_FILENO);   // stdin <- pipe1
  dup2(pipe2[WRITE], STDOUT_FILENO); // stdout -> pipe2
  close(pipe1[READ]);
  close(pipe1[WRITE]);
  close(pipe2[READ]);
  close(pipe2[WRITE]);
  execlp("grep", "grep", "txt", NULL);
  perror("execlp grep");
  exit(1);
}

pid_t pid3 = fork();
if (pid3 == 0) {
  // Hijo 3: wc -l
  dup2(pipe2[READ], STDIN_FILENO);   // stdin <- pipe2
  close(pipe1[READ]);
  close(pipe1[WRITE]);
  close(pipe2[READ]);
  close(pipe2[WRITE]);
  execlp("wc", "wc", "-l", NULL);
  perror("execlp wc");
  exit(1);
}

// Padre
close(pipe1[READ]);
close(pipe1[WRITE]);
close(pipe2[READ]);
close(pipe2[WRITE]);

waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);
waitpid(pid3, NULL, 0);

*/