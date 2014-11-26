#include<stdio.h>
#include<WinSock2.h>

int main()
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSAData wsdata;
	int flag = WSAStartup(wVersionRequested,&wsdata);
	if(flag != 0)
		return 0;
	if(HIBYTE(wsdata.wVersion) != 1 || LOBYTE(wsdata.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}

	SOCKET serversocket = socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in sockadd;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(6000);
	sockadd.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(serversocket, (SOCKADDR*)&sockadd,sizeof(SOCKADDR));
	char recivebuff[1000] = {0};
	char sendbuff[1000] = {0};
	char tempbuff[1000] = {0};
	sockaddr_in clientadd;
	int len = sizeof(clientadd);
	while(1)
	{
		recvfrom(serversocket,recivebuff,sizeof(recivebuff),0,(SOCKADDR*)&clientadd,&len);
		if(recivebuff[0] == 'q')
		{
			sendto(serversocket,"q",sizeof(sendbuff), 0, (SOCKADDR*)&clientadd,len);
			printf("chat end\n");
			break;	
		}
		sprintf(tempbuff,"%s say : %s",inet_ntoa(clientadd.sin_addr),recivebuff);
		printf("%s\n",tempbuff);
		printf("please input your word :");
		gets(sendbuff);
		sendto(serversocket,sendbuff,strlen(sendbuff)+1,0,(SOCKADDR*)&clientadd,len);
	}
	closesocket(serversocket);
	WSACleanup();
	return 0;
}