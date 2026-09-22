#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

int main(void) {
    WSADATA wsa;
    SOCKET server_socket = INVALID_SOCKET;
    SOCKET client_socket = INVALID_SOCKET;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed!\n");
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed!\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed!\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Listen failed!\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("server waiting ...\n");
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed!\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("CLIENT connected !!!\n");

    char buffer[1024];
    char message[1024];

    while (1) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';
        printf("client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            send(client_socket, "exit", strlen("exit"), 0);
            break;
        }

        printf("server: ");
        if (!fgets(message, sizeof(message), stdin)) {
            break;
        }
        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            send(client_socket, "exit", strlen("exit"), 0);
            break;
        }

        send(client_socket, message, strlen(message), 0);
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}