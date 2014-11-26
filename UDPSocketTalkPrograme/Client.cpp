#include<stdio.h>
#include<WinSock2.h>

int main()
{
	WORD wVersionRequested = MAKEWORD(1,1);
	WSAData wsdata;
	int flag = WSAStartup(wVersionRequested,&wsdata);

	if(flag!=0)
		return 0;

	if(HIBYTE(wsdata.wVersion)!=1 || LOBYTE(wsdata.wVersion)!=1)
	{
		WSACleanup();
		return 0;
	}


	SOCKET clientsocket = socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in sockadd;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(6000);
	sockadd.sin_addr.S_un.S_addr = inet_addr("125.221.225.14");

	int len = sizeof(SOCKADDR);
	char sendbuff[1000];
	char recivebuff[1000];
	char tempbuff[1000];
	while(1)
	{
		printf("please input your words:");
		gets(sendbuff);
		sendto(clientsocket,sendbuff,strlen(sendbuff)+1,0,(SOCKADDR*)&sockadd,len);
		recvfrom(clientsocket,recivebuff,sizeof(recivebuff),0,(SOCKADDR*)&sockadd,&len);
		if(recivebuff[0] == 'q')
		{
			sendto(clientsocket,"q",strlen("q")+1,0,(SOCKADDR*)&sockadd,len);
			printf("chat end\n");
			break;
		}
		
		
			sprintf(tempbuff,"%s said : %s", inet_ntoa(sockadd.sin_addr),recivebuff);
			printf("%s\n",tempbuff);
		
	}
	closesocket(clientsocket);
	WSACleanup();
	return 0;
}