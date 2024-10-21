#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9999

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error al crear el socket\n");
        return -1;
    }

    // Configurar la dirección del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir la dirección IP del servidor a formato binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Dirección no válida\n");
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Conexión fallida\n");
        return -1;
    }

    // Bucle para recibir y enviar datos del servidor
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        printf("Recibido del servidor: %s\n", buffer);

        // Simulación de procesamiento adicional o enviar el mismo timestamp
        // Puedes enviar el buffer a otra dirección o simplemente seguir el flujo
        // Aquí el dato se procesaría en Apache Spark.
    }

    // Cerrar la conexión
    close(sock);

    return 0;
}
