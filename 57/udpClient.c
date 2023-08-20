#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(){
    struct sockaddr_in udpclient, udpserver;
    char buffer[1024];

    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd<0){
        printf("Socker Creation failed");
        exit(0);
    }
    printf("[+]Socket Created..");

    udpserver.sin_family = AF_INET;
    udpserver.sin_port = 3000;
    udpserver.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = sizeof udpserver;
    printf("\nClient ready to communicate..");
    while (1){
        printf("\nClient: ");
        gets(buffer);
        sendto(sd, buffer, sizeof buffer, 0, (struct sockaddr*)&udpserver, n);
        if (strcmp(buffer, "end") == 0){
            break;
        }
        recvfrom(sd, buffer, sizeof buffer, 0, (struct sockaddr*)&udpserver, &n);
        printf("\nServer: %s",buffer);
        if (strcmp(buffer, "end")==0){
            break;
        }
    }
    int num,fact;
    recvfrom(sd, buffer, sizeof buffer, 0, (struct sockaddr*)&udpserver, &n);
    printf("\n%s",buffer);
    scanf("%d",&num);
    sendto(sd, &num, sizeof num, 0, (struct sockaddr*)&udpserver, n);
    recvfrom(sd, &fact, sizeof fact, 0, (struct sockaddr*)&udpserver, &n);
    printf("\nThe factorial of %d is %d",num,fact);
    close(sd);
    printf("\nConnection closed");
}