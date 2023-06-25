#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 4444
int main()
{
    int clientSocket, ret, s;
    FILE *fp;

    struct sockaddr_in cliAddr;
    struct sockaddr_in serverAddr;
    char buffer[1024], name[100], fname[100], rcvg[100];
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");
    memset(&cliAddr, '\0', sizeof(cliAddr));
    memset(buffer, '\0', sizeof(buffer));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Connected to Server.\n");
    while (1)
    {
        printf("Enter the existing file name\t");
        scanf("%s", name);
        printf("Enter the new file name\t");
        scanf("%s", fname);
        fp = fopen(fname, "w");
        while (1)
        {
            send(clientSocket, name, sizeof(name), 0);

            s = recv(clientSocket, rcvg, 100, 0);
            if (s < 0)
                printf("Error in receiving data");
            else
            {
                rcvg[s] = '\0';
                if (strcmp(rcvg, "error") == 0)
                    printf("File is not available\n");
                if (strcmp(rcvg, "completed") == 0)
                {
                    printf("File is transferred........\n");
                    break;
                }
                else
                {
                    fputs(rcvg, stdout);
                    fprintf(fp, "%s", rcvg);
                    bzero(rcvg, sizeof(rcvg));
                }
            }
        }
        fclose(fp);
        close(clientSocket);
        return 0;
    }