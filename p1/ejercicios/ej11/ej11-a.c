/*
tenemos que mandar mensajes y tenemos las siguentes operaciones

    void bsend(pid dst, int msg) Envía el valor msg al proceso dst.

    int breceive(pid src) Recibe un mensaje del proceso src.

    pid get_current_pid() que devuelve el process id del proceso que invoca dicha llamada.
*/

// a) proceso padre e hijo se mandan mensaje y le suman uno

void rutina_hijo() {
    int msg;
    while (1)
    {
        msg = brecive(getppid());
        printf("recibí:%d",msg);
        msg++;
        printf("mando msg:%d",msg);
        bsend(getppid(), msg);
    }
}

int main() {
    int msg = 0;
    
    int pid = fork();

    if (pid == 0)
    {
        rutina_hijo();
    }
    
    // rutina del padre, aprovchamos que el hijo arranca leyendo así podemos mandar el primer mensaje
    while (1)
    {
        printf("mando msg:%d",msg);
        bsend(pid, msg);
        msg = brecive(pid);
        printf("recibí:%d",msg);
        msg++;
    }

    return 1;
}
