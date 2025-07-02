#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define EXPRESSION_SIZE 100 //100 caracteres debería ser más que suficiente para cualquier cuenta razonable (es donde vamos a guardar las operaciones para mandarselas al server)

enum {FALSE, TRUE};

int server_socket; // lo necesito global para poder matarlo desde el handler

// Handler de SIGINT, cierra socket y avisa que lo cerraste asi
void handler_signint(int sig) {
    close(server_socket);
    printf("Saliendo del server con SIGINT");
    exit(0);
}

int main() {
    struct sockaddr_un server_addr; //estructuca con la direccion del server al que nos queremos meter

    // configuramos direccion

    server_addr.sun_family = AF_UNIX;               // socket local
    strcpy(server_addr.sun_path, "unix_socket");    // direccion del archivo que crea el server

    // creamos socket y lo conectamos
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }

    // Hasta aca es lo mismo qeu hizo honi

    //handoler para sigint
    signal(SIGINT, handler_signint);

    // lo que vamos a mandar y recibir
    int resultado;
    char expresion[EXPRESSION_SIZE] = {}; //buffer de tamaño fijo para la expresión
    while (TRUE) //while true, leer stdin para conseguir las expresiones de cuentas, ponerlas en el buffer y enviarlas al servidor
    {
        //TODO: leer stdin y ponerlo en el buffer
        scanf("%s", expresion); // literal lee de stdin
        send(server_socket, expresion, sizeof(char)*EXPRESSION_SIZE, 0); //enviar la expresion al server

        if (strcmp(expresion, "exit") == 0){ //si el input era "exit", cerrar el socket y morir (está bien haberselo mandado al server. Él también debe morir.)
            printf("Cerrando cliente.\n");
            close(server_socket);
            exit(0);
        }

        recv(server_socket, &resultado, sizeof(int), 0); //recibir resultado
        printf("Resultado recibido: %d\n", resultado);

        //borrar buffer para prepararlo para la próxima operación
        memset(expresion, 0, EXPRESSION_SIZE);
    }
    

	exit(0);
}
