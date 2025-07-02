#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/*
	Que carajo es un socket?
		Un socket es el extremo de una conexion, constituida por una direccion ip y un puerto.
		Dos procesos que se quieren comunicar entre sı se deben poner de acuerdo usando los sockets correspondientes
		pueden trabajar en distintas maquinas Solo se deben conocer de antemano las direccciones ip y los puertos utilizados para la conexion.
		
	entiendo que los clientes siguen esta estrutura
	
		Crear el socket → socket()

		Configurar dirección del servidor

		Conectarse → connect()

		Leer y escribir
*/

enum { FALSE, TRUE};
#define EXPRESSION_SIZE 100 //100 caracteres debería ser más que suficiente para cualquier cuenta razonable


int main() {

	int server_socket; 					// va a guardar el descriptor de archivo del socket.
	struct sockaddr_un server_addr;		// la estructura que representa la dirección del socket del servidor

	server_addr.sun_family = AF_UNIX;	// especificamos el tipo de socket
	strcpy(server_addr.sun_path, "unix_socket"); // aca entiendo que le asiganamos alg0?

	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);	// creamos el socket y decimos que es comunicacion local y el tipo
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) { // aca nos intentamos de conectar al socket si funk todo pelota cc error y salimos
        perror("Error");
        exit(1);
    }

	int resultado;
	// Necesito un bufffer para poder almacenar los mensajes asi 
	char expresion[EXPRESSION_SIZE] = {};

	// para leer la entrada desde stdin
	while (TRUE)
	{
		
	}
	

	exit(0);
}
