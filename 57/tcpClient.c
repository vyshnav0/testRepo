#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h> // for socket(), connect()
#include <sys/types.h>  // different datatypes
#include <netinet/in.h> // for server address structure
#include <arpa/inet.h> // for manipulating Internet addresses: inet_addr

void main(){
    char buffer[100];

    // myserver is kinda like an object of sockaddr_in that 
    // can access its params like sin_family, sin_port etc
    struct sockaddr_in myserver;

    // AF_INET is domain, SOCK_STREAM - tcp, protocol
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd<0){
        printf("[-]error creating socket");
        exit(0);
    }
    else
        printf("[+]socket connected\n");

    myserver.sin_family = AF_INET; // socket will use IPv4
    myserver.sin_port = 2000;
    myserver.sin_addr.s_addr = inet_addr("127.0.0.1"); // sets the ip to local addr

    printf("Client is ready for communication...\n");

    int server_size = sizeof myserver;
    // socket descriptor, address of the remote server you want to connect to and server size
    int cli = connect(sd, (struct sockaddr *)&myserver, server_size);
    if (cli < 0) {
        printf("[-]Error connecting to socket");
        exit(0);
    }
    else
        printf("[+]Connected to socket\n");

    while(1){
        printf("\nClient: ");
        gets(buffer);
        send(sd, buffer, sizeof(buffer), 0);
        
        if (strcmp(buffer, "bye") == 0)
            break;
        recv(sd, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "bye") == 0)
            break;
        printf("Server: %s\n",buffer);
    }
    close(sd);
    printf("[-]Disconnected from server...\n");

}