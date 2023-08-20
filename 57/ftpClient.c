#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define max 1024

void main(){
    struct sockaddr_in server;
    char buffer[max];
    FILE *fp;

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd<0)
    {
        perror("Socket failure");
        exit(0);
    }
    printf("Socket connected...\n");
    server.sin_family = AF_INET;
    server.sin_port = 8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(sd, (struct sockaddr*)&server, sizeof server);
    if (c<0)
    {
        perror("connect failure");
        exit(0);
    }
    printf("Connected to server\n");

    printf("Reading from FTPC.txt...\n");
    fp = fopen("FTPC.txt", "r");
    if (fp == NULL) 
    {
        perror("file error");
        exit(0);
    }

    while (fgets(buffer, max, fp)!=NULL)
    {
        printf("Sending data: %s",buffer);
        send(sd, buffer, max, 0);
        bzero(buffer, max);
    }

    printf("File transfer complete\n");
    printf("Client disconnected\n");
    close(sd);
}