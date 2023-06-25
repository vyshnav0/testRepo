#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#define BUF_SIZE 256
void main()
{
    struct sockaddr_in server, client;
    char str[50], msg[20];
    int s, n;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 4100;
    bind(s, (struct sockaddr *)&server, sizeof(server));
    n = sizeof(client);
    printf("Server waiting...");
    recvfrom(s, str, 100, 0, (struct sockaddr *)&client, &n);
    printf("\nGot message from client:%s", str);
    printf("\nSending greeting msg to client");
    strcpy(str, "220 127.0.0.1");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    sleep(3);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    if (strncmp(str, "HELO", 4))
        printf("\n 'HELO' expected from client...");

    printf("\n%s", str);
    printf("\nSending Response...");
    strcpy(str, "250 ok");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    sleep(3);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    if (strncmp(str, "MAIL FROM", 9))
        printf("\nMAIL FROM expected from client...");
    printf("\n%s", str);
    printf("\nSending Response...");
    strcpy(str, "250 ok");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    sleep(3);
    printf("\nReceiving to address");
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    if (strncmp(str, "RCPT TO", 7))
        printf("RCPT TO expected from client...");
    printf("\n%s", str);
    printf("\nSending Response...");
    strcpy(str, "250 ok");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    sleep(3);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    if (strncmp(str, "DATA", 4))
        printf("DATA expected from client...");
    printf("\n%s", str);
    printf("\nSending Response...");
    strcpy(str, "354 go ahead");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    printf("\nMail body received");
    printf("\n%s", msg);

    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&client, &n);
    if (strncmp(str, "QUIT", 4))
        printf("QUIT expected from client...");
    printf("sending quit...\n");
    strcpy(str, "221 ok");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&client, n);
    close(s);
}