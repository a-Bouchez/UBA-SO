// #include <csignal>
#include <signal.h>  // no me deja compilarlo con el de arriba ??? mire el codigo de guille y no esta, no se de donde lo saque 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/*
    El proceso padre env´ıa una se˜nal de SIGTERM a cada uno de sus hijos, con un segundo de diferencia entre si
    .
    Cada hijo saca al azar un n´umero del 0 al N.

    Cuando un hijo recibe la se˜nal del padre, debe hacer lo siguiente: si el n´umero sacado al azar es maldito,
    debe expresar sus ´ultimas palabras y luego debe terminar su ejecuci´on; en caso contrario, sobrevive.
    Todo lo enunciado hasta ac´a, se tiene que repetir K rondas.

    Una vez finalizadas las rondas, los hijos que sobrevivieron ser´an los ganadores. El padre debe notificar al
    usuario qu´e hijos sobrevivieron, con identificador y su PID.

    Finalmente, el padre debe enviar una se˜nal de SIGKILL a los hijos restantes y finalizar su ejecuci´on
*/

// voy a tener que crear un puntero a un arreglo para poder almacenar las uid y sus identificadores

#define TRUE 1
#define DEAD -1

int n;
int numero_maldito;
int arr_hijos[10];              // sabemos tamaño max < 10
int *ptr_hijos = arr_hijos;     // puntero para poder acceder al arreglo

int generate_random_number(){
    //Funcion para cargar nueva semilla para el numero aleatorio
    srand(time(NULL) ^ getpid());
    return (rand() % n);
}

// los handlers siempre recuben un int que es la señal, hay que hacer uno por cada señal que se manda
void handler_sigterm(int sig){
    // aca soy hijo y recibo esto asi qeu tengi que gamblear
    int n = generate_random_number();
    if (n == numero_maldito) {
        printf("ggs\n");
        // termina su ejecutarse
        exit(0);
    }
}

// La señal SIGCHLD se envía automáticamente a un proceso padre cuando uno de sus hijos cambia de estado (termina o es detenido).
// Nos da la uid de un hijo cuando se mata en este caso, de manera que esta se encarga de llenar el acta de qeu la quedaron
void handler_sigchld(int sig) {
    // nos tira el uid en el wait, como no sabemos cuanto esperamos ponemos null
    int muerto = wait(NULL);
    
    // recorremos arreglo y miramos cual es
    for (int i = 0; i < n; i++) {
        if (ptr_hijos[i] == muerto) {
            ptr_hijos[i] = DEAD;
        }
    }
}
void rutina_padre(int rondas){
     // setup del handler de la muerte de los hijos
     signal(SIGCHLD, handler_sigchld);

     // tenemos que mandar una señal k veces
     for (int k = 0; k < rondas ; k++) {
         // a los n hijos
         for (int i = 0; i<n; i++) {
             // primero chequeamos que el hijo no se haya pegado un tiro (lo que hace ir a la uba)
             if (ptr_hijos[i] != DEAD) {
                kill(arr_hijos[i], SIGTERM);
             }
         }
         sleep(1);
     }
 
     printf("No se murieron:\n");
     // miramos cuales quedaron vivos recorriend el arreglo y los matamos con sigkill
     for (int i = 0; i < n; i++) {
         if (ptr_hijos[i] != DEAD) {
             printf("Hijo: %d uid: %d \n", i, ptr_hijos[i]);
             kill(ptr_hijos[i], SIGKILL);
         }
     }
}

void rutina_hijos(){
    // les setupeamos la señal para que la puedan recibir
    signal(SIGTERM,handler_sigterm);

    // porque while true? los hijos mueren si terminan de ejecutarse, queremos que los mate el padre
    while (TRUE) {
    }
}

int main(int argc, char const *argv[]){
    
    n = atoi(argv[1]);
	int rondas = atoi(argv[2]);
	numero_maldito = atoi(argv[3]);

    // primero debemos chequear las cosas que nos piden 

    // tres parametros de entrada el primero es siempre el nombre del programa
    if (argc != 4) {
        printf("faltan parametros de entrada bolas tristes\n");
        return 1;
    }

    // n tiene que ser menor a 10
    if (n >= 10) {
        printf("Muchos hijos, como los conejos.\n");
        return  1;
    }

    // el num maldito tiene que ser menor a n y mayor a 0
    if (numero_maldito > n || numero_maldito < 0) {
        printf("La pifiamos con el numero maldito, mira hijos o mayor a 0\n");
        return 1;
    }

    // aca arranca el ej, tenemos que hacer n forks

    for (int i = 0; i < n; i++) {
        int uid = fork();

        // salimos del loop si somos hijos para no hacernos un ddos sin querer
        if (uid == 0) {
            // aca podemos salir del for con un break o despachar a los hijos
            // si los despachamos nos ahorramos de checkear con el if
            rutina_hijos();
        }

        // si somos el padre arrancamos allenar el arreglo con el uid de los hijos
        ptr_hijos[i] = uid;
    }
    // necesito este sleep para que los hijos lleguen a hacer setup de la señal
    sleep(1);

    // rutina del padre, me gusta hacerla a parte pero es un poco al pedo. queda linda para el debugg si la sacamos
        // solo digo
    rutina_padre((rondas));

    exit(0);
}
