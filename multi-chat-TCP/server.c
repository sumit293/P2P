#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI handleClient(LPVOID arg)
{
    SOCKET client_socket = (SOCKET)arg;

    char buffer[1024];
    char message [1024];

    printf("The client is connected !!!\n");

    while (1) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';
        printf("client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        printf("server: ");
        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        message[strcspn(message, "\n")] = '\0';
        send(client_socket, message, (int)strlen(message), 0);

        if (strcmp(message, "exit") == 0) {
            break;
        }
    }

    closesocket(client_socket);
    printf("The client is disconnected !!!\n");
    return 0;
}

int main(void)
{
    WSADATA wsa;
    SOCKET server_socket;
    SOCKET client_socket;
    struct sockaddr_in server;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed !!!\n");
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR ||
        listen(server_socket, 1) == SOCKET_ERROR) {
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port 8080...\n");
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket != INVALID_SOCKET) {
        handleClient((LPVOID)client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
