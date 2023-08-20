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
    struct sockaddr_in server, client;
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

    int b = bind(sd, (struct sockaddr*)&server, sizeof(server));
    if (b<0)
    {
        printf("binding failed");
        exit(0);
    }
    printf("Binding successful\n");

    listen(sd, 1);

    int n = sizeof client;
    int cd = accept(sd, (struct sockaddr*)&client, &n);
    if (cd < 0){
        perror("accept failed");
        exit(0);
    }
    printf("Accepted client connection\n");

    fp = fopen("FTPS", "w");
    if (fp == NULL)
    {
        perror("file error");
        exit(0);
    }
    while (1)
    {
        int m = recv(cd, buffer, sizeof buffer, 0);
        if (m<=0)
        {
            printf("File tranfer Complete\n");
            exit(0);
        }
        printf("Recieved: %s",buffer);
        fprintf(fp, "%s", buffer);        
        bzero(buffer, sizeof buffer);
    }
    printf("Server disconnected\n");
    close(sd);    
    close(cd);    
}