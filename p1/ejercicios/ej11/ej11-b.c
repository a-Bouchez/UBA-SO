/*
tenemos que mandar mensajes y tenemos las siguentes operaciones

    void bsend(pid dst, int msg) Envía el valor msg al proceso dst.

    int breceive(pid src) Recibe un mensaje del proceso src.

    pid get_current_pid() que devuelve el process id del proceso que invoca dicha llamada.

    se peude hacer mas lindo con señales y demas pero tengo paja.
*/
#include <stdio.h>
#include <unistd.h>     // para fork(), sleep()

extern void  bsend(int dst, int msg);
extern int   breceive(int src);
extern int get_current_pid();

enum{FALSE, TRUE};

int llegamos_al_num(int i) {
    if (i == 50)
    {
        return TRUE;
    }
    return FALSE;
}

int pids[3];

void rutina_hijo(int i) {
    int msg;
    while (1)
    {
        if (i == 1) { // Hijo1
            msg = breceive(pids[0]); // Recibe del padre
            printf("H1 recibió: %d\n", msg);
            if (llegamos_al_num(msg)) exit(0);
            msg++;
            printf("H1 manda: %d\n", msg);
            bsend(pids[2], msg);     // Envia a hijo2
        } else if (i == 2) { // Hijo2
            msg = breceive(pids[1]); // Recibe de hijo1
            printf("H2 recibió: %d\n", msg);
            if (llegamos_al_num(msg)) exit(0);
            msg++;
            printf("H2 manda: %d\n", msg);
            bsend(pids[0], msg);     // Envia al padre
        }
    }
}


int main() {
    int msg = 0;


    pids[0] = get_current_pid();

    for (int i = 0; i < 2; i++)
    {
        pids[i+1] = fork();
        if (pids[i+1] == 0)
        {
            rutina_hijo(i +1);
        }
        
    }
    
    // rutina del padre, aprovchamos que el hijo arranca leyendo así podemos mandar el primer mensaje
    while (1)
    {
        printf("mando msg:%d",msg);
        bsend(pids[1], msg);
        msg = breceive(pids[1]);
        if (llegamos_al_num(msg))
        {
            printf("llegamos al num \n");
            exit(0);
        }
        printf("recibí:%d",msg);
        msg++;
    }

    return 0;
}
