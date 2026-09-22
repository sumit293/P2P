#include<stdio.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib") 
int main(){
WSADATA wsa;
SOCKET client_socket;


 if(WSAStartup(MAKEWORD(2,2), &wsa) !=0){
printf("WSAStatup falied \n");
return 1;
 }
 
client_socket =  socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server;

server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_port = htons(8080);

connect(
    client_socket,
    (struct sockaddr*)&server,
    sizeof(server)
);

char message[] = "Hello server! ";

send(client_socket, message, strlen(message),0);

closesocket(client_socket);
    WSACleanup();
    


 }