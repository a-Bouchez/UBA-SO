/*
Un pipe es un mecanismo de comunicación unidireccional entre procesos relacionados (por ejemplo, un padre y su hijo). Permite que un proceso escriba datos y otro los lea, funcionando como una especie de "tubería".
    ¿Cómo funciona?

    Un proceso crea un pipe con pipe(fd).

    fd[0] es el descriptor para leer.

    fd[1] es el descriptor para escribir.

    Los procesos deben cerrarse el extremo que no usan para evitar bloqueos.

*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid == 0) {
        // Proceso hijo: lee del pipe
        close(fd[1]); // No escribe
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Hijo recibió: %s\n", buffer);
        close(fd[0]);
    } else {
        // Proceso padre: escribe en el pipe
        close(fd[0]); // No lee
        char *mensaje = "Hola hijo!";
        write(fd[1], mensaje, strlen(mensaje) + 1);
        close(fd[1]);
    }

    return 0;
}

/*
🌐 SOCKET
📘 ¿Qué es?

Un socket es un punto final para comunicación bidireccional entre procesos, que puede ser:

    Local (en la misma máquina) o

    Remota (entre computadoras vía red)

A diferencia del pipe, no requiere relación de parentesco entre procesos.
🔧 ¿Cómo funciona?

    Se crea con socket().

    El servidor usa bind(), listen(), accept().

    El cliente usa connect().

    Luego ambos usan read() y write() o send() y recv().
*/
// servidor.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(server_fd, 1);

    client_fd = accept(server_fd, NULL, NULL);
    read(client_fd, buffer, 1024);
    printf("Servidor recibió: %s\n", buffer);

    char *respuesta = "Hola cliente!";
    write(client_fd, respuesta, strlen(respuesta));
    close(client_fd);
    close(server_fd);

    return 0;
}

// cliente.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    char *mensaje = "Hola servidor!";
    write(sock, mensaje, strlen(mensaje));
    read(sock, buffer, 1024);
    printf("Cliente recibió: %s\n", buffer);

    close(sock);
    return 0;
}
