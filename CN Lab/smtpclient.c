#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#define BUF_SIZE 256
void main()
{
    struct sockaddr_in server, client;
    char str[50] = "hi";
    char mail_f[50], mail_to[50], msg[20], c;
    int t = 0, s, n;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 4100;
    printf("\nClient ready...\n");
    n = sizeof(server);
    printf("sending hi to server");
    sleep(10);
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    printf("\nGreeting msg is %s", str);

    if (strncmp(str, "220", 3))
        printf("\nCan not established \n code 220 expected");
    printf("\nSending HELLO");
    strcpy(str, "HELLO 127.0.0.1");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    sleep(3);
    printf("\nReceiving from server");
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    if (strncmp(str, "250", 3))
        printf("\nOK not received from server");
    printf("\nServer has send %s", str);
    printf("\nEnter FROM address\n");
    scanf("%s", mail_f);
    strcpy(str, "MAIL FROM");
    strcat(str, mail_f);
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    sleep(3);
    printf("\nReceiving from server ");
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    if (strncmp(str, "250", 3))
        printf("\nOK not received from server");
    printf("%s\n", str);
    printf("\nEnter TO address\n");
    scanf("%s", mail_to);
    strcpy(str, "RCPT TO ");
    strcat(str, mail_to);
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    sleep(3);
    printf("\nReceiving from server");
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    if (strncmp(str, "250", 3))
        printf("\n OK not received from server");

    printf(" %s\n", str);
    printf("\nSending data to server");
    strcpy(str, "DATA");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    sleep(3);
    printf("\nReceiving from server");
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    if (strncmp(str, "354", 3))
        printf("\nOK not received from server");
    printf("\n%s", str);
    printf("\nEnter mail body");
    while (1)
    {
        c = getchar();
        if (c == '$')
        {
            msg[t] = '\0';
            break;
        }
        if (c == '\0')
            continue;
        msg[t++] = c;
    }
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    sleep(3);
    printf("\nSending QUIT to server");
    strcpy(str, "QUIT");
    sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, n);
    recvfrom(s, str, sizeof(str), 0, (struct sockaddr *)&server, &n);
    if (strncmp(str, "221", 3))
        printf("\nOK not received from server");
    printf("\nServer has send GOODBYE......Closing connection\n");
    printf("\nBye");
    close(s);
}