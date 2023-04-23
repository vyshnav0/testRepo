#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void main()
{
    struct sockaddr_in server, client;
    int s, sock;
    char b1[100] = " ", b2[100] = "";
    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nClient ready....\n");
    connect(s, (struct sockaddr *)&server, sizeof server);
    for (;;)
    {
        printf("\nClient : ");
        gets(b2);
        send(s, b2, sizeof b2, 0);
        if (strcmp(b2, "end") == 0)
            break;
        recv(s, b1, sizeof b1, 0);
        if (strcmp(b1, "end") == 0)
            break;
        printf("\nServer %s", b1);
    }
    close(s);
}
