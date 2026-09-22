#include<stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main (){
    WSADATA wsa;
    SOCKET client_socket;
    if(WSAStartup(MAKEWORD(2,2),&wsa) !=0){
        printf("WSAStatrup failed !!!");
        return 1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM,0);

    if(client_socket == INVALID_SOCKET){
        printf("SOCKET creation failed !!! \n");
        WSACleanup();
        return 1;

    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if(connect(client_socket,
    (struct sockaddr*)&server, sizeof(server))== SOCKET_ERROR){
        printf("connection failed !!!\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;

    }

    printf("connected  to server  :)");

    char message[] = "HELLO SERVER ";
    send(
        client_socket, message , strlen(message),0
    );

    printf( "the message is sent to server \n");

    char buffer [1024];

    int bytes_recived = recv(
        client_socket, buffer, 
        sizeof(buffer)-1, 0
    );

    if(bytes_recived>0)
{
    buffer[bytes_recived] = '\0';

    printf("the message from server is : %s \n", buffer);

}   
closesocket(client_socket);
WSACleanup();
return 0;
 
}