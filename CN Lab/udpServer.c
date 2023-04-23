#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void main()
{
    struct sockaddr_in client, server;
    int s, n, num, fact = 1, i;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("\nServer ready,waiting for client...\n");
    n = sizeof(client);
    recvfrom(s, &num, sizeof(int), 0, (struct sockaddr *)&client, &n);
    if (num == 0)
        fact = 1;
    else
    {
        for (i = 1; i <= num; i++)
            fact *= i;
    }
    sendto(s, &fact, sizeof(int), 0, (struct sockaddr *)&client, n);
    printf("Factorial is calculated\n");
    close(s);
}