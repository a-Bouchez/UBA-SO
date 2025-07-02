#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

/*
	Resumen: Basicamente abusamos de que al hacer read se quedan tildados hasta que puedan leer. Cuando terminan de hacer sus cosas se matan solos
*/

enum
{
	READ,
	WRITE
};

enum
{
	FALSE,
	TRUE
};

int numero_actual;

int generate_random_number()
{
	return (rand() % 50);
}

void rutina_hijo(int pipe_inicial[2], int index, int n, int start, int pipes[][2])
{
	// renombres para mayor claridad
	int *pipe_escritura = pipes[index];
	int *pipe_lectura;

	// si no sos el primer hijo
	if (index != 0)
	{	
		// vas a poder leer del anterior
		pipe_lectura = pipes[index - 1];
	}
	else
	{ // si es el primer proceso, le llega del último pipe
		pipe_lectura = pipes[n - 1];
	}

	// cerramos los pipes que no me corresponden
	for (int i = 0; i < n; i++) {
		//  solo escribo en mi pipe
		if (i != index) {
			close(pipes[i][WRITE]); 
		}
		// solo leo en el pipe anterior a no ser qeu sea el hijo 0
		if (i != index - 1 && !(index == 0 && i == n - 1)) {
			close(pipes[i][READ]); 
		}
	}

	// si no somos start este pipe ni lo tocamos
	if (index != start) {
		close(pipe_inicial[READ]);
		close(pipe_inicial[WRITE]);
	}

	while (TRUE) // ejecuto while true para que hagan read() para siempre, no se me matan
	{
		if (index == start) // si es el proceso hijo que inicia todo...
		{
			// el static lo que hace es que quede en memoria para asuegurarnos de que el flag y el numero sec no pierdan sus valores
			static int primera_vez = TRUE;
			static int secret_number;

			// oara asegurarnis de solo crear un numero
			if (primera_vez)
			{
				primera_vez = FALSE; // que solo haga el setup una vez
				
				// que lea el numero actual del padre
				read(pipe_inicial[READ], &numero_actual, sizeof(int));
				close(pipe_inicial[READ]);

				// creo el numero secreto. Debe ser mayor que el valor inicial del número actual (No se si esto lo piden)
				do
				{
					secret_number = generate_random_number();
				} 
					while (secret_number <= numero_actual);
			}
			else
			{
				// esto se ejecuta todas las veces menos la primera, es la rutina del hijo iniciador post creacion del numero 

				// leer el numero actual
				read(pipe_lectura[READ], &numero_actual, sizeof(int));

				// checkear si se excedió al secret number y mandárselo al padre si sí.
				if (secret_number < numero_actual)
				{
					write(pipe_inicial[WRITE], &numero_actual, sizeof(int));
					close(pipe_inicial[WRITE]);
					exit(0);
				}
			}

			// desde acá se ejecuta siempre en este proceso, es lo qeu hacen todosl os hijos, aumentan el numero y lo mandan por el pipe

			numero_actual++; //incrementar numero actual

			write(pipes[index][WRITE], &numero_actual, sizeof(int));
		}
		else
		{ //si es cualquier otro hijo...
			// leer el numero actual, incrementarlo y pasarlo al siguiente
			int tam_bytes_leidos =  read(pipe_lectura[READ], &numero_actual, sizeof(int));
			numero_actual++;
			write(pipes[index][WRITE], &numero_actual, sizeof(int));

			// que pasa si el tamaño es 0???? significa que no quedo nada para leer --> termino el juego, hora de que se maten
			// existe algo llamado end of file (EOF) y 0 nos indica que llemaos a eso.
			if (tam_bytes_leidos == 0)
			{
				// cerramos el pipe del que leemos y mi parte de escirtura
				close(pipe_escritura[READ]);
				close(pipe_lectura[READ]);
				exit(0);
			}
		}
	}
}


int main(int argc, char **argv)
{
	// Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	if (argc != 4)
	{
		printf("Uso: anillo <n> <c> <s> \n");
		exit(0);
	}


	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	
	printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);

	int pipes[n][2]; // pipes es int[count-1][2]
	pid_t *children = malloc(sizeof(*children) * n);

	// creo los pipes para cada hijo (el ultimo pipe conecta el ultimo hijo con el primero)
	for (size_t i = 0; i < n; i++)
	{
		pipe(pipes[i]);
	}

	// creo pipe para pasar el número inicial a start
	int pipe_inicial[2];
	pipe(pipe_inicial);

	// escribo en el pipe inicial el valor inicial (buffer)
	write(pipe_inicial[WRITE], &buffer, sizeof(int));

	// creo los hijos
	for (int i = 0; i < n; i++)
	{
		children[i] = fork();
		if (children[i] == 0) // si soy el hijo...
		{
			rutina_hijo(pipe_inicial, i, n, start, pipes); //...no voy a salir de acá
		}
		sleep(1); // A mimir...
	}

	// cerrar pipes
	for (size_t i = 0; i < n; i++)
	{
		close(pipes[i][READ]);
		close(pipes[i][WRITE]);
	}

	//leo lo que me devuelva mi hijo start cuando lo haga, y lo imprimo
	read(pipe_inicial[READ], &buffer, sizeof(int));
	printf("Número final: %d\n", buffer);
	
	//cierro el pipe con mi hijo
	close(pipe_inicial[READ]);
	close(pipe_inicial[WRITE]);

	// matamos zombies
	for (int i = 0; i < n; i++) {
		wait(NULL);
	}
	
	// nos aseguramos que start no quede zombie
	//waitpid(children[start], NULL, 0);

}
