/*
    a)
    m labos nuevos, necesitamos un sistema paraque n estudiantes sepan a donde ir.
    reparto random.
    usar pipes
    Padre:
        - pide a cada uno de los n hijos que calculen donde les toca. (pasan n por parámetro)
        - informa m a los hijos por pipe
        - imprime por la salida estandar id del hijo y el labo
    Hijo:
        - calcula donde le toca y le avisa al padre
        - usan el id del proceso como semilla para ver en que labo caen (pid%m)

    no me quiero tirar flores pero me parece que mi código está mejor que el de Honi eh. (voy a desaprobar igual)

    b)
    modificar el código anterior para realizar el siguiente comportamiento.
    el código del padre ya no las imprima por pantalla. En cambio se debe ejecutar un programa que nos proveen llamado “nuevaSalida”.
    el programa ejecutable toma como parámetros por entrada estándar el id de un proceso y el n'umero de laboratorio asignado y lo imprime en 
    pantalla (salida estándar).
    queremos que el resultado de este programa no sea escrito en el STDOUT sino en un archivo llamado “resultados.out” en donde guardaremos un log
    de la ejecucion.

    int open(char* archivo, O_WRONLY) // abre el archivo en modo de escritura, retornando el descriptor correspondiente

    int dameLabo(int process_id, m) // toma el process_id correspondiente a un proceso hijo de un alumno y el n´umero de laboratorios nuevos "m"
                                       y devuelve aleatoriamente un n´umero de labo asignado, entre 1 y m, usando como semilla el process_id enviado
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

extern int O_WRONLY;

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

typedef struct msg
{
    int m;
    int n;
}msg_t;


void rutina_hijo(int* padre_hijo[], int* hijo_padre[], int num_hijo,int n) {  
    for (size_t i = 0; i < n; i++)
    {
        close(hijo_padre[i][READ]);
        close(padre_hijo[i][WRITE]);
    }

    msg_t msg;
    read(padre_hijo[num_hijo][READ], &msg, sizeof(msg));

    int pid = getpid();
    int labo = pid % msg.m;

    write(hijo_padre[num_hijo][WRITE],&labo,sizeof(labo));

    close(padre_hijo[num_hijo][READ]);
    close(hijo_padre[num_hijo][WRITE]);

    exit(0);
}
    


int main(int argc, char const* argv[]){
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int padre_hijo[n][2];
    int hijo_padre[n][2];

    for (size_t i = 0; i < n; i++)
    {
        pipe(padre_hijo[i]);
        pipe(hijo_padre[i]);
    }

    msg_t msg;
    msg.m=m;
    msg.n=n;

    int children[n]; 

    for (size_t i = 0; i < n; i++)
    {
        children[i] = fork();
        if (children[i] == 0)
        {
            rutina_hijo(padre_hijo,hijo_padre,i,n); // chau pendejos
        }
    }


    for (size_t i = 0; i < n; i++)
    {
        close(padre_hijo[i][READ]);
        close(hijo_padre[i][WRITE]);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        write(padre_hijo[i][WRITE],&msg,sizeof(msg));
    }
    
    // hacemos un pipe para el archivo 
    // conseguimos el descriptor del archivo al que queremos mandar la salida
    int salida = open("resultados.out",O_WRONLY);
    dup2(salida, 1);    //pasamos el std_out al archivo para que cuando queramos escribir ahí en realidad escribamos en el archivo

    for (size_t i = 0; i < n; i++)
    {
        int res;
        read(hijo_padre[i][READ],&res,sizeof(res));
        
        // después de leer le pasamos las cosas al archivo por un pipe
        int entrada[2];
        // prendmos el pipe
        pipe(entrada);

        // el otro programa me saca todo mi code así que usamos un hijo
        int pid = fork();
        if (pid == 0)
        {
            // hacemos lo mismo que el anterior pero con el std_in
            dup2(entrada[READ],0);

            // cerramos la punta que no usamos
            close(entrada[WRITE]);

            // Reemplazamos el proceso hijo por la ejecución del programa nuevaSalida.
            // Se mantienen los file descriptors prevamiente configurados.
            char* argv_nuevaSalida[] = {"nuevaSalida", NULL};
            execvp(argv_nuevaSalida[0], argv_nuevaSalida);
        }
        
        // Somos el padre, escribimos en el pipe de stdin el pid del proceso hijo
        // (el que representa un estudiante) junto a su labo asignado.
        fprintf(entrada[WRITE], "%d %d\n", children[i], res);
        // Cerramos el pipe.
        close(entrada[READ]);
        close(entrada[WRITE]); // Este es el que importa para disparar EOF al hijo.
    }

    // matamos zombies
    for (size_t i = 0; i < n; i++)
    {
        wait(NULL);
    }
    
    return 0;    

}