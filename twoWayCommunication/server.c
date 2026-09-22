#include<stdio.h>
#include <WinSock2.h>
#include <string.h>

#pragma cooment(lib, "win_32.lib")

int  main(){
        WSADATA wsa;
        SOCKET server_socket, client_socket;

        if(WSAStartup(MAKEWORD(2,2),&wsa) !=0){
            printf("WSAStatrup failed !!!");
            return 1;

        }
        server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if(server_socket == INVALID_SOCKET){
            printf("socket creation failed !!!\n");
            WSACleanup();
            return 1;

        }

        struct sockaddr_in server;

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_port = htons(8080);

        if(bind(server_socket, (struct sockaddr*)&server,sizeof(server))== SOCKET_ERROR){
            printf("BINDING  failed ");
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        listen(server_socket, 5);

        printf("server is waiting \n");

        client_socket  = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET){
            printf("Accept FAILED !!!\n");
            closesocket(server_socket);
            WSACleanup();
            return 1;

        }

        printf("THE CLIENT IS CONNECTED  !!!! \n");

        char buffer [1024];

        int bytes_recived = recv(client_socket, buffer,
             sizeof(buffer)-1,
    0);

    if(bytes_recived > 0){
        buffer[bytes_recived]= '\0';
        printf("Message from client: %s\n", buffer);
    }

    char message[] = "Hello client!";

    send(client_socket, message, strlen(message), 0);

    printf("MESSAGGE SEND TO CLIENT :)");

    closesocket(client_socket);
    closesocket(server_socket);

    return 0;


}