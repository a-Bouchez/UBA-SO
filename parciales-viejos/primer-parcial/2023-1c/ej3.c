/*
    parerlizar conteo de números perfectos dentro del conjunto de mediciones de una estrella, subprocesos comunicados con pipes.
    se deberá contar con un procesos cordinador y cantidad parametrizable de subprocesos verificadores.

    Coordinador:

        Debe leer la cantidad N de verificadores a través de un argumento. Luego usa boolean hayNumero() que indica si quedan números para leer
        y leerNum() para leerlo si hay.

        Cada vez que lee un num debe mandarlo a un verificador para que lo procese asegurando que la cantidad de números que reciba c/u sea equitativa.

        Guarda los números perfectos en un arr int totales[N]

    Verificador:

        Toman el num y llaman a boolean esPerfecto(int num) y le envian el número solo si es perfcecto
    
*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

typedef boolean;

extern esPerfecto(int num);
extern boolean hayNumero();
extern int leerNum();
extern O_WRONLY;
extern O_APPEND;

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

int i = 0;

int main(int argc, char const* argv[]){
    int n = atoi(argv[1]);
    // completar

    while (hayNumero())
    {   
        int sig_num = leerNum();
        // completar
        int hijo_destino = i % n;

        
        i++;
    }
    int totales[n];
    // completar
}

/*
    crear N pipes padre->hijo
    crear N pipes hijo->padre

    inicializarlos

    fork N hijos
        if pid == 0
            rutina_hijos(pipes)
    padre:
        while hayNumero():
            leer numero
            enviar a siguiente hijo en round robin

        cerrar escritura de pipes padre->hijo

        while no se hayan recolectado todos los perfectos:
            read de pipes hijo->padre

        cerrar lectura de pipes padre->hijo

        wait() hijos
        print totales[]
        return 0
        
    hijo:
        cerrar puntas no usadas
        loop:
            int bytes = read número de su pipe padre->hijo
            if esPerfecto(numero):
                write número en pipe hijo->padre
            if bytes == Eof:
                cerramos nuestro pipe
                exit(0);

    Lo que hay implementado es el RR. Parece que los pipes son unidereccionales por lo que los hijos necesitan un pipe para escribirle al padre
    (medio raro pero me lo corrigió el chat así qeu duden de eso), el resto está bien me parece.
*/

//code de HONI/YAGO

#define READ 0
#define WRITE 1
#define FROM_PARENT 0
#define TO_PARENT 1

void verificador(int fdr, int fdw) {
    int num;
    int count = 0;
    while (read(fdr, &num, sizeof(num))) {
        if (esPerfecto(num)) count++;
    }
    write(fdw, &count, sizeof(count));
    exit(EXIT_SUCCESS);
}

int main(int argc, char const* argv[]) {
    int n = atoi(argv[1]);

    int pipes[n][2][2];
    for (int i = 0; i < n; i++) {
        pipe(pipes[i][FROM_PARENT]);
        pipe(pipes[i][TO_PARENT]);
    }

    pid_t children[n];
    for (int i = 0; i < n; i++) {
        if ((children[i] = fork()) == 0) { // child
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    close(pipes[j][FROM_PARENT][READ]);
                    close(pipes[j][FROM_PARENT][WRITE]);
                    close(pipes[j][TO_PARENT][READ]);
                    close(pipes[j][TO_PARENT][WRITE]);
                } else {
                    close(pipes[j][FROM_PARENT][WRITE]);
                    close(pipes[j][TO_PARENT][READ]);
                }
            }
            verificador(pipes[i][FROM_PARENT][READ], pipes[TO_PARENT][WRITE]);
        }
    }

    int child = 0;
    while (hayNumero()) {
        int num = leerNumero();
        write(pipes[child][FROM_PARENT][WRITE], &num, sizeof(num));
        child = (child+1) % n;
    }

    for (int i = 0; i < n; i++) {
        close(pipes[i][FROM_PARENT][READ]);
        close(pipes[i][FROM_PARENT][WRITE]);
    }

    int totales[n];
    int num;
    for (int i = 0; i < n; i++) {
        totales[n] = read(pipes[i][TO_PARENT][READ], &num, sizeof(num));
        wait(NULL); // Evitamos dejar procesos zombies.
    }

    int fd_informe = open("informe.txt", O_WRONLY | O_APPEND);

    int fd_startgpt_stdin[2];
    pipe(fd_startgpt_stdin);

    for (int i = 0; i < n; i++) {
        dprintf(fd_startgpt_stdin[WRITE], "%d\n", totales[i]);
    }
    close(fd_startgpt_stdin[WRITE]);

    dup2(fd_startgpt_stdin[READ], STDIN_FILENO);
    dup2(fd_informe, STDOUT_FILENO);

    char* argv[] = {"stargpt", "-generar-parrafo", NULL};
    execvp(argv[0], argv);
}

