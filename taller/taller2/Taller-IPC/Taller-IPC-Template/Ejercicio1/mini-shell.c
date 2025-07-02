#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

enum { READ, WRITE };


void rutina_hijo(int index, size_t count, char **comando, int pipes[][2]){
	//cableo los pipes

	//Al primer hijo le queda el stdin original
	if (index != 0)
	{
		dup2(pipes[index-1][READ], STDIN_FILENO);
	}
	//al ultimo hijo le queda el stdout original
	if (index != count-1 ){
		dup2(pipes[index][WRITE], STDOUT_FILENO);
	}
	
	
	//cierro los pipes
	for (size_t i = 0; i < count-1; i++)
	{
		close(pipes[i][READ]);
		close(pipes[i][WRITE]);
	}
	
	//reemplazar la imagen del hijo
	execvp(comando[0], comando); 
}

static int run(char ***progs, size_t count)
{	
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);
	
	int pipes[count-1][2]; //pipes es int[count-1][2]
	
	//creo los pipes para los hijos
	for (size_t i = 0; i < count; i++)
	{
		pipe(pipes[i]); 
	}

	//TODO: Pensar cuantos procesos necesito
	for (int i = 0; i < count; i++)
	{
		printf("inicié hijo %d\n",i);
		children[i] = fork();
		if (children[i] == 0) //si soy el hijo...
		{			
			rutina_hijo(i, count, progs[i], pipes); //...no voy a salir de acá

		}
		sleep(1); //A mimir...
	}

	// hay que cerrar también los pipes del padre
	for (size_t i = 0; i < count-1; i++)
	{
		close(pipes[i][READ]);
		close(pipes[i][WRITE]);
	}
	
	//TODO: Pensar cuantos pipes necesito.

	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d con indice %d no terminó correctamente [%d]: ",
			    (int)children[i], i, WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}
	r = 0;
	free(children);

	

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
