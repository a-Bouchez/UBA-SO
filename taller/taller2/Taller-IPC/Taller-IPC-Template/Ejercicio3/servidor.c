#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define EXPRESSION_SIZE 100 //100 caracteres debería ser más que suficiente para cualquier cuenta razonable, aca almacenamos las operaciones matematicas

enum {FALSE, TRUE};

// No tengo mucho para explicar aca, su nombre lo dice todo
int calcular(const char *expresion) {
    int num1, num2, resultado;
    char operador;

    // Usamos sscanf para extraer los dos números y el operador de la expresión
    if (sscanf(expresion, "%d %c %d", &num1, &operador, &num2) != 3) { // es como el slice de python my beloved, le agregue espacios para que poddamos escribir las cosas separadas
        printf("Formato incorrecto\n");
        return 0;  // En caso de error, retornamos 0.
    }

    // Realizamos la operación según el operador, Como solo nos fijamos en el operador para saber en que caso caer es mejor usar un switch
    // basicamente nos deja usar condiciones menos interesantes que un if pero es mas rapido y hace parecer que se programar
    switch (operador) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
            } else {
                printf("Error: División por cero\n");
                return 0;  // Si hay división por cero, retornamos 0.
            }
            break;
        default:
            printf("Operador no reconocido\n");
            return 0;  // Si el operador no es válido, retornamos 0.
    }

    return resultado;
}

void child_method(int client_socket){
    int resultado;                      // aca metemos el resultado
    char expresion[EXPRESSION_SIZE];    // aca almacenamos la operacion qeu nos manda el cliente
    while (TRUE) //while true, recibir los requests de cuentas del cliente y responder con el resultado
    {
        recv(client_socket, expresion, sizeof(char)*EXPRESSION_SIZE, 0); //leer la expresión que me mandó el cliente, (lo escucha y es bloqueante)
        if (strcmp(expresion, "exit") == 0){ //si el input era "exit", cerrar el socket y morir
            printf("Cerrando instancia de server.\n");
            close(client_socket);
            exit(0);
        }
        //hacer la cuenta y enviar resultado al cliente
        resultado = calcular(expresion);
        send(client_socket, &resultado, sizeof(int), 0);
    }
}

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

	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);   // crea socket
	bind(server_socket, (struct sockaddr *) &server_addr, slen);    // linkea el FD del socket con la addr local

	listen(server_socket, 5); //le pongo un backlog de 5 por si el server es super lento por alguna razón (?)

    int num;
	//while true, aceptar conexiones de nuevos clientes
    printf("Esperando clientes...\n");
    while (TRUE)
	{
        // accept deja conectarse al socket a los clientes y por c/u devolvemos un client socket nuevo
		client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        printf("Conectado a cliente.\n");

        // Logica de forks de todo estos ejercicios
        pid_t pid = fork();
        if (pid == 0)
        {
            //si soy el hijo, empiezo a atender a mi cliente. Me voy a mi función, de la cuál no voy a salir
            child_method(client_socket);
        }
        //si soy el padre cierro el socket de comunicación, porque no lo voy a usar (y tal vez lo voy a pisar con el próximo cliente)
        close(client_socket);
	}

    exit(0);
}

