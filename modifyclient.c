#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	char buf[300];
	int k;
	int sock_desc;
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	sock_desc=socket(AF_INET,SOCK_STREAM,0);

	if(sock_desc==-1)
	{
	printf("Error di  socket creation\n");
	exit(1);
	}

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("192.168.0.4");
	client.sin_port = htons(8888);

	k = connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	if(k == -1)
	{
	printf("MASALAH nak connect ke server\n");
	exit(1);
	}

	while(1)
	{
	printf("Client: "); //Msg for server
	fgets(buf,100,stdin);
		if(strncmp(buf,"bye",3) == 0)
	break;
	k = send(sock_desc,buf,100,0);
		if(k == -1)
	{
		printf("MASALAH Penghantaran\n");
			exit(1);
	}
	k = recv(sock_desc,buf,100,0);
		if(k == -1)
	{
	printf("MASALAH Penerimaan\n");
			exit(1);
	}

	printf("\nServer: %s",buf); //Mesej for server
	}

	close(sock_desc);
	exit(0);
	return 0;
}
