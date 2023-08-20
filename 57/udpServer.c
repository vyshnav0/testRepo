#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(){
    struct sockaddr_in udpserver, udpclient;
    char buffer[1024];
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd<0){
        printf("[-]Socket creation error\n");
        exit(0);
    }
    printf("[+]Socket created\n");

    udpserver.sin_family = AF_INET;
    udpserver.sin_port = 3000;
    udpserver.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(sd, (struct sockaddr*)&udpserver, sizeof udpserver);
    if(b<0){
        printf("[-]Binding error\n");
        exit(0);
    }
    printf("[+]Binding successfull\n[+]Server ready, waiting for client\n");

    int n = sizeof udpclient;
    while (1){   
        recvfrom(sd, buffer, sizeof buffer, 0, (struct sockaddr*)&udpclient, &n);
        if (strcmp(buffer, "end") == 0){
            break;
        }
        printf("\nClient: %s", buffer);
        printf("\nServer: ");
        gets(buffer);
        sendto(sd, buffer, sizeof buffer, 0, (struct sockaddr*)&udpclient, n);
        if (strcmp(buffer, "end")==0){
            break;
        } 
    }

    int num;
    char msg[] = "Enter the number:";
    sendto(sd, msg, sizeof msg, 0, (struct sockaddr*)&udpclient, n);
    recvfrom(sd, &num, sizeof num, 0, (struct sockaddr*)&udpclient, &n);
    printf("\nRecieved number %d from Client, finding factorial..",num);

    int fact= 1;
    if (num == 0){
        fact = 1;
    }
    else{
        for (int i = 1; i <= num; i++){
            fact*= i;
        }
    }
    printf("\nFactorial found. Sending to client..");
    sendto(sd, &fact, sizeof fact, 0, (struct sockaddr*)&udpclient, n);
    close(sd);
    printf("\nConnection closed");
}