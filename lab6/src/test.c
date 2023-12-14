#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 


int main() {
    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP адрес сервера
    server.sin_port = htons(3000); // Порт сервера

    // Попытка подключения
    printf("connecting...\n");
    if (connect(sck, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("connected successful...\n");

    // Теперь вы можете использовать сокет для обмена данными с сервером

    return 0;
}