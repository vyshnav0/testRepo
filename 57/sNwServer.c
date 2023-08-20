#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main(){

    struct sockaddr_in server, client;

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

    int b = bind(sd, (struct sockaddr*)&server, sizeof server);
    if(b<0)
    {
        perror("binding");
        exit(0);
    }
    printf("Binding successfull\n");

    listen(sd,1);
    printf("Server listening\n");
    int n = sizeof client;
    int cd = accept(sd, (struct sockaddr*)&client, &n);
    if(cd<0)
    {
        perror("accept");
        exit(0);
    }

    int frame, ack, m, t;
    recv(cd, &m, sizeof m, 0);
    printf("\nNo of frames: %d\n",m);
    recv(cd, &t, sizeof t, 0);
    printf("Time limit: %d\n",t);

    int temp = (rand()%m) -1;

    while (1)
    {
        printf("\n");
        recv(cd, &frame, sizeof frame, 0);
        
        ack = frame;
        if (frame == temp)
        {
            printf("[-]Resend frame %d\n",frame);
            ack = -1;
            temp = -1;
        }
        else
            printf("Frame %d received\nSending acknowledgement %d\n",frame, ack);
        send(cd, &ack, sizeof ack, 0);

        if (ack == m-1)
        {
            printf("\nTransmission complete\n");
            break;
        }
    }
    close(cd);
    close(sd);
}
