#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(void) {
    WSADATA wsa;
    SOCKET client_socket = INVALID_SOCKET;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed!\n");
        return 1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Socket creation failed!\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Failed to connect to server!\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("THE SERVER is connected :)\n");

    char message[1024];
    char buffer[1024];

    while (1) {
        printf("client: ");
        if (!fgets(message, sizeof(message), stdin)) {
            break;
        }

        message[strcspn(message, "\n")] = '\0';
        send(client_socket, message, strlen(message), 0);

        if (strcmp(message, "exit") == 0) {
            break;
        }

        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';
        printf("server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}