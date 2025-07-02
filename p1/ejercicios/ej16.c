// el B del 11 pero con pipes

#include <signal.h>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// este está bueno, es similar al taller. Vamos a querer hacer un anillo entre el apdre y los 2 hijos

// acá se puede hacer de distintas maneras, podemos usar solo un pipe y que leen/escriban cuando necesiten o podemos hacer n pipes


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

int n = 3; // padre y 2 hijos
int esperado = 50;

void rutina_hijos(int i, int pipes[][2]) {
    // renombres para mayor claridad
	int *pipe_escritura = pipes[i];
	int *pipe_lectura;

	// si no sos el primer hijo
	if (i != 0)
	{	
		// vas a poder leer del anterior
		pipe_lectura = pipes[i - 1];
	}
	else
	{ // si es el primer proceso, le llega del último pipe
		pipe_lectura = pipes[n - 1];
	}

    // cerramos los pipes que no me corresponden
	for (int j = 0; j < n; j++) {
		//  solo escribo en mi pipe
		if (j != i) {
			close(pipes[j][WRITE]); 
		}
		// solo leo en el pipe anterior a no ser qeu sea el hijo 0
		if (j != i - 1 && !(i == 0 && j == n - 1)) {
			close(pipes[j][READ]); 
		}
	}


    // la rutina como tal
    while (TRUE)
    {
        int msg;
        
        int tam = read(pipe_lectura[READ], &msg, sizeof(int));

        msg ++;

        if (tam == 0 || msg >= esperado)
        {
           close(pipe_escritura[WRITE]);
           close(pipe_lectura[READ]);
           exit(0);
        }

        write(pipe_escritura[WRITE], &msg, sizeof(int));
    }
}

int main() {

    // arr de tamaño n de pipes
    int pipes[n][2];

    // inicializamos los pipes
    for (size_t i = 0; i < n; i++)
    {
        pipe(pipes[i]);
    }
    
    // todos los hijos van a tener una copia de los FD de todos los pipes, depsues vamos a tener que cerrar los que no se usan

    for (size_t i = 1; i < n; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            rutina_hijos(i, pipes);
        }
    }
    
    // rutina del padre

    // se tiene que comunicar con el hijo 1 y leer del hijo 2, todos leen del pipe i-1 menos el padre que lee del n
    // podemos cerrar la punta de lectura del pipe 

    for (size_t i = 0; i < n; i++)
    {
        // solo escribo en mi pipe
        if (i != 0)
        {
            close(pipes[i][WRITE]);
        }

        // solo leeo del anterior
        if (i != n - 1)
        {
            close(pipes[i][READ]); 
        }
        
    }

    int msg = 0;

    // tenemos que hacer que se maten, para eso usamos end of file
    while (TRUE)
    {
        write(pipes[0][WRITE], &msg, sizeof(int));

        int tam = read(pipes[2][READ], &msg, sizeof(int));
        
        msg++; 

        // llegué al end of file
        if (tam == 0 || msg >= 50)
        {
           // cierro mis pipes
            close(pipes[0][WRITE]);
            close(pipes[2][READ]);
            break;
        }
        
    }
    
    // matamos zombies
	for (int i = 0; i < n; i++) {
		wait(NULL);
	}

    return 0;
}   