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

	SOCKET client_socket = socket(AF_INET,SOCK_DGRAM,0);
	char sendbuff[1000] = {0};
	sockaddr_in clientadd;
	clientadd.sin_family = AF_INET;
	clientadd.sin_port=htons(6000);
	clientadd.sin_addr.S_un.S_addr = inet_addr("125.221.225.14");
	gets(sendbuff);
	sendto(client_socket,sendbuff,sizeof(sendbuff),0,(SOCKADDR*)&clientadd,sizeof(sockaddr_in));
	closesocket(client_socket);
	WSACleanup();
	return 0;
}
