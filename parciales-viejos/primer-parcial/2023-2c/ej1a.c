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
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

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


void rutina_hijo(int* padre_hijo[], int* hijo_padre[], int num_hijo,int n) {    // tengo o que pasar n si o si o cerrar los pipes antes de ir a la fun
    // cerramos las puntas que no usamos, esta caso lectura de hijo_padre y escritura de padre_hijo
    for (size_t i = 0; i < n; i++)
    {
        close(hijo_padre[i][READ]);
        close(padre_hijo[i][WRITE]);
    }

    // leemos el mensaje
    msg_t msg;
    read(padre_hijo[num_hijo][READ], &msg, sizeof(msg));

    // calculamos el labo
    int pid = getpid();
    int labo = pid % msg.m;

    // manadamos el msg
    write(hijo_padre[num_hijo][WRITE],&labo,sizeof(labo));

    // cerramos las puntas que nos faltan
    close(padre_hijo[num_hijo][READ]);
    close(hijo_padre[num_hijo][WRITE]);

    // nos matamos
    exit(0);
}
    


int main(int argc, char const* argv[]){
    // agarro m y n
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    // creamos nx2 pipes, los padre_hijo y los hijo_padre (comunicación unidireccional y ecriben los 2)
    int padre_hijo[n][2];
    int hijo_padre[n][2];

    // inicializamos los pipes
    for (size_t i = 0; i < n; i++)
    {
        pipe(padre_hijo[i]);
        pipe(hijo_padre[i]);
    }

    // creo mensaje con los 2 valores que quiero pasare
    msg_t msg;
    msg.m=m;
    msg.n=n;

    // para guardar los pid
    int children[n]; 

    //creamos hijos
    for (size_t i = 0; i < n; i++)
    {
        children[i] = fork();
        if (children[i] == 0)
        {
            // si no quiero mandar n como parámetro puedo cerrar acá las puntas qeu no uso

            rutina_hijo(padre_hijo,hijo_padre,i,n); // chau pendejos
        }
    }

    // somos el padre

    //cerramos las puntas de escritura de los pipes hijo_padre y las de lectura de los padre_hijo

    for (size_t i = 0; i < n; i++)
    {
        close(padre_hijo[i][READ]);
        close(hijo_padre[i][WRITE]);
    }
    
    // podría hacerlo en el anterior pero prefiero acá para que se lea mejor, mandamos msg 
    for (size_t i = 0; i < n; i++)
    {
        write(padre_hijo[i][WRITE],&msg,sizeof(msg));
    }
    
    //ahora leemos lo que nos madaron y lo printeamos
    for (size_t i = 0; i < n; i++)
    {
        int res;
        read(hijo_padre[i][READ],&res,sizeof(res));
        printf("Hijo con pid: %d va al labo %d \n",children[i],res);
    }

    // matamos zombies
    for (size_t i = 0; i < n; i++)
    {
        wait(NULL);
    }
    
    return 0;    

}