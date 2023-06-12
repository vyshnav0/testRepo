#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<math.h>
int main()
{
	struct sockaddr_in client,server;
	int s,sock,ack,frame,n,num;
	s=socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port=2022;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(s,(struct sockaddr *)&server,sizeof server);
	listen(s,1);
	printf("Server is ready\nWaiting for client...\n");
	n = sizeof client;
	sock=accept(s,(struct sockaddr *)&client,&n);
	recv(sock,&num,sizeof(int),0);
	int temp=rand()%num-1;
	printf("%d\n",temp);
	while(1)
	{
		recv(sock,&frame,sizeof(int),0);
		printf("Frame %d Received Successfully\n",frame);
		ack=frame+1;
		if(frame==temp)
		{
			ack=100;
			temp--;
		}
		printf("Acknowledgement %d Send\n",ack);
		send(sock,&ack,sizeof(int),0);
		if(ack==num)
		break;

	}
	close(sock);
	close(s);
}
