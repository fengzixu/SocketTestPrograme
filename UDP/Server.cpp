/*
名称：基于UDP协议的服务端程序
作者： fengzixu
时间: 2014/11/25
简介：
基于UDP和TCP两个协议的不同版本，大致的框架都是相同的，只是有几处细节不同。
首先，基于TCP协议的服务端，需要两个套接字，一个用来绑定端口并且监听，一个用来建立连接。
但是UDP协议中不需要监听和建立连接，绑定端口之后直接就可以通信，且从始至终只用一个套接字(在创建套接字的时候，TCP和UDP的类型是不一样的)
其次，就是接受信息的API不同。TCP是recv而UDP是recvfrom
*/


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

	SOCKET server_socket = socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in sockadd;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(6000);
	sockadd.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(server_socket, (SOCKADDR*)&sockadd,sizeof(SOCKADDR));

	char recivebuff[1000] = {0};
	sockaddr_in clientaddr;
	int len = sizeof(clientaddr);
	recvfrom(server_socket,recivebuff,sizeof(recivebuff),0,(SOCKADDR*)&clientaddr,&len);
	printf("%s\n",recivebuff);
	closesocket(server_socket);
	WSACleanup();
	return 0;
}