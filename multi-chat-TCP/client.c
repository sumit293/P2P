#include<stdio.h>
#include <WinSock2.h>
#include<string.h>
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET client_socket;
    SOCKET server_socket;

    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        
        printf("WSAStatrup failed !!!");
        return 1;
    }
    client_socket = socket(AF_INET,  SOCK_STREAM,0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    int result = connect(client_socket, (struct sockaddr*)&server, sizeof(server));
        IF(result == SOCKET_ERROR){
            printf("connection failed !!!\n");
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }

        // remainni f 



}
