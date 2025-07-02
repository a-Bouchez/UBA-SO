/*
- los hijos saben poco, no conocen al resto de hijos y no se van a poder comunicar entre ellos
- La mejor manera va a ser que cada cliente le manda a su respectvo hijo el menssage y este hijo se lo fowardea al server (padre) y como conoce los sockets del resto puede reenviearselo
- En estos ejercicios podemos asumir el tamaño maximo del mensjae --> buffer[128]. no hace falta malloc
- como hacemos que no se cuelgue el servidor? siganl 
    el hijo cuando manda un menssage activa una señal para decirle al padre que vaya a mirar su pipe, recordemos que el read del pipe es bloqueante por lo que tenemos que evitar qeu el padre
    se quede tildado leyendo algun pipe del hijo.

- Podemos usar un if para checquear que no nos pasemos del maximo de clientes
- POdemos usar un solo pipe para comunicarse entre todos en vez de 5 pipes

*/
enum{FALSE, TRUE};
enum{READ, WRITE};

int pipes[2];
int sc_arr[5] = {-1};

// suponemos que tenemos una funcion que crea un socket, lo buildea y nos devuelve el FD IMPLEMENTAR
int accept_connection() {
    return 1;
} // devuelve cliente hace el accept del server


// necestiamos mandar mas de una cosa, pero no se peude en c --> struct

struct menssage
{
    int id;
    char buffer[128];

} menssage_t;


// rutina cliente
void rutina_cliente( int socket_connection) {
    char buffer[128];   // donde van a escribir
    while (read(socket_connection, buffer, sizeof(buffer) != 0))
    {
        read(socket_connection, buffer, sizeof(buffer));    // lo dejamos aca tildado hasta que pueda leer
        // inicializamos struct simbolicamente
        menssage_t menssage = {id:socket_connection, buffer: buffer};
        write(pipes[WRITE], menssage , sizeof(menssage));
        // le decimos al padre que le mandamos algo
        Kill(detppid(), SIGURD);
    }
    // si llegamos aca es porque tuvimos un EOF
    exit(0);
}

void manejador_fowardig(int sig) {
    menssage_t msg;
    read(pipes[READ], msg, sizeof(msg)); //leemos el struct

    // queremos mandarle el message a todos los hijos menos el que lo manda
    for (int i = 0; i < 5 ; i++) // tamaño del arr
    {
        if (sc_arr[i] != -1 && sc_arr[i] != msg.id)
        {
            write(sc_arr[i], msg.buffer, sizeof(msg.buffer));
        }
        
    }
    
}

//servidor
int main() {
    // setupeamos los handlers  y pipes antes del while
    signal(SIGURD, sigurd_handler);
    pipe(pipes);
    int cant_clientes = 0;

    while (TRUE)
    {
        if (cant_clientes == 5)
        {
            while (cant_clientes == 5)
            {
                // que piense
                sleep(1);
            }
        }
        
        int socket_connection = accept_connection();
        cant_clientes ++;

        put_sc_arr(socket_connection);

        // Forkeamos
        pid_t pid_hijo = fork();

        if (pid_hijo == 0) {
            rutina_cliente(socket_connection);
        }
    }
    
    
}

// cliente

int  sc = makeConnection();
char buffer[128];
pid_t pid_or_0 = fork();
if (pid_or_0 == 0)
{
    while (TRUE){
        read(sc, buffer, sizeof(buffer));
        printf(%s,buffer);

    }
    exit(0);
} else {
    while (TRUE)
    {
        scanf(%s, buffer);
        write(sc, buffer, sizeof(buffer);
    }
    
}

