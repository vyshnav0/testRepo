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
    int s, n, num, fact;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nCleint ready....\n");
    n = sizeof(server);
    printf("\nEnter the number whose factorial is to be find : ");
    scanf("%d", &num);
    sendto(s, &num, sizeof(int), 0, (struct sockaddr *)&server, n);
    recvfrom(s, &fact, sizeof(int), 0, NULL, NULL);
    printf("Factorial of %d = %d\n", num, fact);
    close(s);
}