#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void main()
{
	struct sockaddr_in client,server;
	int s,n,sock,i,frame[100],temp;
	s=socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port=2022;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	printf("Client is ready\n");
	connect(s,(struct sockaddr *)&server, sizeof server);
	printf("\nClient\n");
	printf("Enter the number of frames: ");
	scanf("%d",&n);
	for(i=0;i<n+1;i++)
	{
		frame[i]=i;
	}
	i=0;
	send(s,&n,sizeof(int),0);

	while(1)
	{
		printf("Frame %d sent\n",frame[i]);
		send(s,&frame[i],sizeof(int),0);
		recv(s,&temp,sizeof(int),0);
		if(temp==n)
		{
			printf("Acknowledgement %d Received Successfully\n",temp);
			break;
		}
		if(temp==frame[i+1])
		{
			i++;
			printf("Acknowledgement %d Received Successfully\n",temp);
		}
		else
		{
			sleep(5);
			printf("Timeout\n");
		}
	}
	close(s);
}
