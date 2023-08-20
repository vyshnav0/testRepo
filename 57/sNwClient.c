#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main(){

    struct sockaddr_in server;

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd<0)
    {
        perror("socket");
        exit(0);
    }
    printf("Socket created\n");
    server.sin_family = AF_INET;
    server.sin_port = 5000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int cd = connect(sd, (struct sockaddr*)&server, sizeof server);
    if (cd<0)
    {
        perror("connection");
        exit(0);
    }
    printf("Connected to the server\n");

    int m, frame[20], ack, t, i = 0;
    printf("\nEnter the number of frames to send: ");
    scanf("%d", &m);
    send(sd, &m, sizeof m, 0);
    for (int j = 0; j < m; j++)
    {
        frame[j] = j;
    }
    printf("Enter the timeout: ");
    scanf("%d", &t);
    send(sd, &t, sizeof t, 0);

    while (1)
    {
        printf("\n[+]Sending frame %d\n",frame[i]);
        send(sd, &frame[i], sizeof frame[i], 0);

        recv(sd, &ack, sizeof ack, 0);
        if (ack == m-1)
        {
            printf("\nTransmission complete\n");
            break;
        }

        if (ack == frame[i])
        {
            printf("Acknowledgement %d received\n",ack);
            i++;
        }
        else{
            sleep(t);
            printf("Acknowledgement not recieved\nResending frame %d", frame[i]);
        }
    }
    close(sd);    
}
