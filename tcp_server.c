#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET server_socket, client_socket;

    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    server_socket  = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
     server.sin_family = AF_INET;
     server.sin_addr.s_addr= in_addr("127.0.0.1");
    server.sin_port= htons(8080);

    bind(server_socket, (struct sockaddr*)&server, sizeOf(server));

    listen(server_socket, 4);

    client_socket = accept(server_socket, NULL, NULL);

    printf("client connected \n");

    char  buffer[1024];

    int bytes_received = recv(
        client_socket,
         buffer, 
         sizeof(buffer)-1, 
         0
        );

        buffer[bytes_received] = '\0';

        printf("Received message: %s\n", buffer);
        closesocket(client_socket);
        closesocket(server_socket);

        WSACleanup();

        return  0;
        

    


}