# Crear el archivo README con la descripción de la aplicación
readme_content = """
# Aplicación de Procesamiento Distribuido en Tiempo Real con Apache Spark y Sockets en C

## Descripción
Esta aplicación es un ejemplo simple de cómo combinar **Apache Spark Structured Streaming** con un servidor y cliente de **Sockets en C** para procesar datos en tiempo real. La aplicación incluye:

1. **Servidor en C**: Genera y envía marcas de tiempo (timestamps) cada segundo a través de un socket.
2. **Cliente en C**: Recibe los datos enviados por el servidor.
3. **Apache Spark**: Procesa los datos en tiempo real, contando cuántos eventos (timestamps) se reciben por minuto.

## Requisitos Previos

- **Apache Spark** instalado en tu sistema.
- **Netcat** o una configuración de servidor de sockets.
- **Compilador C** para compilar y ejecutar el servidor y el cliente.

## Instrucciones

### 1. Compilar y ejecutar el servidor en C

El servidor se encargará de enviar marcas de tiempo (timestamps) al cliente cada segundo.

Compila el código del servidor con el siguiente comando:

```bash
gcc -o server server.c
