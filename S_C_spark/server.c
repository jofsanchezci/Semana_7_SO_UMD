#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9999

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    time_t rawtime;
    struct tm * timeinfo;
    char time_str[80];

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configuración de la dirección
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Enlazar el socket al puerto 9999
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Poner el servidor en modo de escucha
    if (listen(server_fd, 3) < 0) {
        perror("Error en listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Esperando conexión...\n");

    // Aceptar la conexión de un cliente
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Error al aceptar la conexión");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Bucle para enviar datos de tiempo
    while (1) {
        // Obtener el tiempo actual
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Enviar la marca de tiempo al cliente
        send(new_socket, time_str, strlen(time_str), 0);
        printf("Enviando timestamp: %s\n", time_str);

        // Esperar 1 segundo antes de enviar el siguiente timestamp
        sleep(1);
    }

    // Cerrar la conexión
    close(new_socket);
    close(server_fd);

    return 0;
}
