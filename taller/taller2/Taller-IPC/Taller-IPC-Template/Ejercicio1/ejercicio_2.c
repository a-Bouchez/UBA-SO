#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
  // Redirijo stdout al pipe
  dup2(pipe_fd[WRITE], STDOUT_FILENO); 
  // Cierrro el extremo de lectura del pipe
  close(pipe_fd[READ]);              
  // Cierrro el descriptor original de escritura pq ahora STDOUT_FILENO es una copia de pipe_fd[WRITE]
  //No hace falta cerrar manualmente el extremo de escritura del pipe porque una vez que termine
  //la ejecucion del hijo1 todos los fd se cierra incluyendo el que apunta a el extremo de escritura 
  //del hijo1, lo mismo con el hijo2 obviamente. 
  close(pipe_fd[WRITE]);           
       
  execlp("ls", "ls", "-a", NULL); 
  exit(0);
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
 dup2(pipe_fd[READ], STDIN_FILENO); 
 close(pipe_fd[WRITE]);              
 close(pipe_fd[READ]);  

  execlp("wc", "wc", "-l", NULL);
  exit(0);
}

int main(int argc, char const* argv[]) {
  //Creo el pipe
  int pipe_fd[2];
  pipe(pipe_fd);

  //Creo los dos procesos hijo
  pid_t pid_hijo1 = fork();
  if(pid_hijo1 == 0){
    ejecutar_hijo_1(pipe_fd); 
  }

  pid_t pid_hijo2 = fork();
  if(pid_hijo2 == 0){
    ejecutar_hijo_2(pipe_fd); 
  }

  //No le permito al padre ni leer ni escribir en el pipe
  close(pipe_fd[WRITE]);
  close(pipe_fd[READ]);

  wait(NULL);
  wait(NULL);

  return 0;
}
