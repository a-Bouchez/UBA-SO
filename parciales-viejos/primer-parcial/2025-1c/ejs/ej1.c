/*
    proceso será encargado de completar los valores de un arreglo de enteros de M posiciones con valores específicos.
    para eso crea N procesos hijos que tienen int generarValor(int indice) siendo esta var el indice del arreglo que se quiere generar y devueve el num.
    solo puede ser ejecutada por los hijos.
    Por último cuando el padre tenga todos los valores del arreglo y los hijos hayan terminado usa printArray(int[] array).

    a) Escribie Pseudo code de un programa que haga esto usando pipes como medio de comunicación entre procesos. Asumimos que M es multiplo de n y
       que los hijos trabajan de forma equitativa. 

            La idea va a ser: Calcular la cantidad de hijos, darles a cada uno un indice, que le manden el número al padre y este printee el arr
                              No me dice que tenga que ser en un orden pero podemos mandar un struct indice número  

       
*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

extern int generarValor(int indice);

typedef struct msg
{
    int index;
    int num;

} msg_t;


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

void rutina_hijo(int indice_inicial, int* pipe_u, int cant_indices) {
    // cerramos la punta de lectura que no vamos a usar
    close(pipe_u[READ]);

    // creamos el struct
    msg_t msg;

    for (size_t i = 0; i < cant_indices; i++)
    {
        // metemos indice y valor
        msg.index = indice_inicial + i;
        msg.num = generarValor(indice_inicial + i);
        write(pipe_u[WRITE], &msg, sizeof(msg));
    }
    // cerramos la punta de escritura
    close(pipe_u[WRITE]);
    // generamos todos los indices que nos tocas --> nos matamos
    exit(0);
}

int main(int M, int N) {
    // sabemos que M es múltiplo de N vemos la cantidad de indices que hace cada hijo
    int indices = M/N;

    // hacemos el arr que vamos a modificar
    int arr[M];

    // ponemos todo en - inf
    for (int i = 0; i < M; i++) {
        arr[i] = -INFINITY;
    }
    
    // creamos un pipe por el que lee el padre
    int pipe_u[2]; // pipes es int[count-1][2]
    pipe(pipe_u);

    // creamos un arreglo que tiene el indice de los hijos con su PID para mandarselos y qeu hagan ese indice
    int *children = malloc(sizeof(*children) *N);

    // creamos a los hijos
    for (size_t i = 0; i < N; i++)
    {
        children[i] = fork();
        if (children[i] == 0)
        {
            rutina_hijo(i,pipe_u,indices);
        }
    }

    // acá llega solo el padre
    // como no va a escribir nunca cerramos la punta de escritura
    close(pipe_u[WRITE]);

    // buffer al que vamos a leer el mensaje
    msg_t msg;

    int escrturas = 0;
    while (escrturas < M)
    {
        // esperamos a que nos llegue algo de los hijos, el read es bloqueante
        read(pipe_u, &msg, sizeof(msg));
        arr[msg.index] = msg.num;
        escrturas++;
    }
    
    // cerramos el pipe
    close(pipe_u[READ]);

    // matamos zombies
    for (int i = 0; i < N; i++) {
		wait(NULL);
	}

    printArray(arr);
    free(children); // al final no lo usé pero bueno lo dejo

    return 0;
}

/*
    b) supongamos que generarValor() puede demorar un tiempo variable en cada caso, por lo que algunos procesos hijos pueden terminar su trabajo antes
    que otros y queremos que no haya procesos hijos ociosos en caso de qeu queden items en el arreglo sin procesar. Funciona la solución provista para 
    el punto a)? justificar en caso positivo y en el negativo explicar por qué y porponer una idea de solución.

        Antes hubiera dicho que sí. Ya que no tengo hijos ociosos porque hago que se maten luego de terminar. Pero parece que esa no es la respuesta
        que buscaban.

        La idea es que no hagan un cant_indices fijos y generen todo lo que puedan.

        Entonces --> No funciona mi sol del punto a) porque hago que se maten luego de terminar de producir. Tendriamos qeu generar los N hijos y 
        simplemente darles un indice inicial. Luego crear un arreglo booleano por cada uno y n-1 pipes para que se puedan comunicar entre ellos y
        avisen que indice arrancan a generar. Los otros los prenden en sus respectivos arreglos y generan los siguientes.

        igual una más fácil sería que el padre le mande al hijo por su pipe que número quiere que genere y que después el hijo le pida otro número.
*/