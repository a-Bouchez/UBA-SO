#include <signal.h>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// la señal que usamos para avisarle al padre que ya está
void handler_sigterm (int sig) {
    
}

// cada proceso usa su pipe 
void ejecutarHijo(int index, int pipes[][2]) {
    //cerrar todos los pipes menos los del abuelo y el padre
     
    signal(SIGTERM, handler_sigterm);

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Debe ejecutar con la cantidad de hijos como parametro\n");
        return 0;
    }

    int N = atoi(argv[1]);
    int pipes[N * 2][2];

    for (int i = 0; i < N * 2; i++) {
        pipe(pipes[i]);
    }

    for (int i = 0; i < N; i++) {
        int pid = fork();
        if (pid == 0) {
            ejecutarHijo(i, pipes);
            return 0;
        } else {
            int numero = dameNumero(pid);
            write(pipes[i][1], &numero, sizeof(numero));
        }
    }

    int cantidadTerminados = 0;
    char hijoTermino[N];
    memset(hijoTermino, 0, sizeof(hijoTermino));

    while (cantidadTerminados < N) {
        for (int i = 0; i < N; i++) {
            if (hijoTermino[i]) {
                continue;
            }

            char termino = 0;
            write(pipes[i][1], &termino, sizeof(termino));
            read(pipes[N + i][0], &termino, sizeof(termino));

            if (termino) {
                int numero;
                int resultado;
                read(pipes[N + i][0], &numero, sizeof(numero));
                read(pipes[N + i][0], &resultado, sizeof(resultado));
                informarResultado(numero, resultado);
                hijoTermino[i] = 1;
                cantidadTerminados++;
            }
        }
    }

    wait(NULL);
    return 0;
}
