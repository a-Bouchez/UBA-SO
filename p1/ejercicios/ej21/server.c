/*
Implementar un chat compartido en un servidor con las siguiente características:

    - Cada cliente se conecta a un servidor y va a tener la capacidad de mandar cualquier mensaje.

    - Cada cliente conectado, debe recibir el mensaje que envió alguno de los clientes.

    - El servidor debe soportar hasta máximo 5 clientes al mismo tiempo.

    - Los clientes se pueden conectar y desconectar cuando quieran.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define MAX_CLIENTS 5

extern int cant;
extern int clients_sc[];

#define EXPRESSION_SIZE 100 // para el buffer

enum {FALSE,TRUE};

enum{READ, WRITE};
int client_sockets[5]; // Array de sockets de clientes
int clients = 0;
int pipe_fd[2];
int pipe_fd_clients[2]; // Pipe para avisarle al padre que un cliente se ha desconectado


// necesito eso, al sacar los pipes necesito avisarle al servidor quien manda el mensaje para que no se lo vuelva a mandar
struct mensaje_pipe {
    int sender_sock;
    int length;
    char buffer[EXPRESSION_SIZE];
} mensaje_t; 



// cuando tiramos sigterm al server tiene que leer el pipe
// aca llegamos a un problema, si uso un arr de pipes me quedo tildado acá, no se como decirle que pipe tiene que mirar y ni puede morar todos porque
// el read es bloqueante
void sigterm_handler(int sig) {
    struct mensaje_pipe msg;
    read(pipe_fd[READ], &msg, sizeof(mensaje_t));

    for (size_t i = 0; i < cant; i++)
    {
        if (clients_sc[cant] != -1 && clients_sc[cant] != msg.sender_sock)
        {
            send(clients_sc[i], msg.buffer, msg.length, 0);
        }
        
    }
    
}

void child_method(int sc) {
    struct mensaje_pipe msg_pipe;
    msg_pipe.sender_sock = sc;

    while (1) {
        int bytes = recv(sc, msg_pipe.buffer, sizeof(msg_pipe.buffer), 0);
        if (bytes <= 0) break;             // EOF o error

        msg_pipe.length = bytes;
        if (strcmp(msg_pipe.buffer,"exit")==0) {
            close(sc);
            break;
        }

        write(pipe_fd[WRITE], &msg_pipe, sizeof(msg_pipe));
        kill(getppid(), SIGURG);
    }

    // Notificar desconexión
    write(pipe_fd_clients[WRITE], &sc, sizeof(sc));
    kill(getppid(), SIGUSR1);
    close(sc);
    exit(0);
}

// servidor 
int main() {
    //crear sockets
	int server_socket;                      // para aceptar conecciones
	int client_socket;                      // para interactuar con los clientes
	struct sockaddr_un server_addr;         // dir del socket, entiendo que va a ser la ruta al archivo
	struct sockaddr_un client_addr;         // creo que los datos del cliente
	socklen_t slen = sizeof(server_addr);   // tamaño para bind
	socklen_t clen = sizeof(client_addr);   // tamaño para accept

    // aca basicamente nos dice las caracteristicas del socket, va a ser UNIX y local
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, "unix_socket");    // nombre del archivo
	unlink(server_addr.sun_path);                   // lo desvincula por si ya estaba creado

	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);                // crea socket
	bind(server_socket, (struct sockaddr *) &server_addr, slen);    // linkea el FD del socket con la addr local

	listen(server_socket, 5);   // 5 conexiones

    // creamos un el pipe que van a usar
    pipe(pipe_fd);

    // handler de señal
    signal(SIGTERM,sigterm_handler);

    // como manejamos a los clientes? vamos a hacer un hijo por cliente para poder antenderlos
	//while true, aceptar conexiones de nuevos clientes
    printf("Esperando clientes...\n");
    while (TRUE) {
        int client_socket = accept(server_socket, &client_addr,sizeof(client_addr)); // agregué esto rápido para poder subirlo, OJO con estos parámetros que los puse sin saber
        if (clients < MAX_CLIENTS) {
            clients_sc[clients++] = client_socket;
        } else {
            close(client_socket);
            continue;
        }

        if (fork() == 0) {
            close(server_socket);
            child_method(client_socket);
        }
        close(client_socket);
    }
    return 0;
}
    
