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

int main() {
    struct sockaddr_un server_addr; //estructuca con la direccion del server al que nos queremos meter

    // configuramos direccion

    int server_sc;

    server_addr.sun_family = AF_UNIX;               // socket local
    strcpy(server_addr.sun_path, "unix_socket");    // direccion del archivo que crea el server

    // creamos socket y lo conectamos
    server_sc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_sc, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }
    char expresion[EXPRESSION_SIZE] = {}; //buffer de tamaño fijo para la expresiónchar expresion[EXPRESSION_SIZE] = {}; //buffer de tamaño fijo para la expresión
    // Hasta aca es lo mismo qeu hizo honi

    char mensaje_server[EXPRESSION_SIZE] = {};  // buffer para recibir mensaje del server

    while (TRUE) {
        scanf("%s", expresion); // leer expresión
        send(server_sc, expresion, sizeof(char)*EXPRESSION_SIZE, 0);

        if (strcmp(expresion, "exit") == 0) {
            printf("Cerrando cliente.\n");
            close(server_sc);
            exit(0);
        }

        // recibir respuesta del server
        recv(server_sc, mensaje_server, sizeof(char)*EXPRESSION_SIZE, 0);
        printf("Server: %s\n", mensaje_server);

        // limpiar buffers
        memset(expresion, 0, EXPRESSION_SIZE);
        memset(mensaje_server, 0, EXPRESSION_SIZE);
    }
}

