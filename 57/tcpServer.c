#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(){
    struct sockaddr_in myserver, myclient;
    char buffer[100];

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd<0){
        printf("Socket creation error ");
        exit(0);
    }
    printf("[+]Socket created successfully\n");
    myserver.sin_family = AF_INET;
    myserver.sin_port = 2000;
    myserver.sin_addr.s_addr = inet_addr("127.0.0.1");

    int size = sizeof myserver;
    int b = bind(sd, (struct sockaddr*)&myserver, size);
    if (b<0) {
        printf("Bind error");
        exit(0);
    }
    printf("[+]Binding successfull\n");
    listen(sd, 1);
    printf("[+]Server listening, waiting for Client\n");

    int n = sizeof(myclient);
    int cd = accept(sd, (struct sockaddr*)&myclient, &n);
    if (cd<0) {
        printf("Client connection error ");
        exit(0);
    }
    printf("[+]Client connection accepted\n");

    while(1){
        recv(cd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "bye")==0)
            break;
        printf("Client says: %s\n", buffer);
        printf("Socket: ");
        gets(buffer);
        send(cd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "bye")==0)
            break;
    }

    close(cd);
    printf("\n[-]Client disconnected");
    close(sd);
}