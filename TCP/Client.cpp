/*
名称：基于TCP协议的网络编程的客户端程序
时间：2014、11、25
作者：fengzixu
简介：
在客户端程序中，只需要用一个套接字就可以完成通信功能。因为他不用绑定和监听端口，在向服务器发送请求的时候，就会携带端口和IP地址信息。
客户端在发送了连接请求之后，会首先收到一条服务器端发回的连接成功的信息，然后正式进入通讯阶段.
*/



#include<stdio.h>
#include<WinSock2.h>

int main()
{
	WORD wVersionRequested;
	WSADATA wsdata;

	wVersionRequested = MAKEWORD(1,1);
	int result = WSAStartup(wVersionRequested,&wsdata);
	if(result != 0)
	{
		return 0;
	}
	if(LOBYTE(wsdata.wVersion) != 1 || HIBYTE(wsdata.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}
	while(1){
	SOCKET connect_socket = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in sockad;
	sockad.sin_family = AF_INET;
	sockad.sin_port = htons(6000);
	sockad.sin_addr.S_un.S_addr = inet_addr("125.221.225.14");
	//connect(connect_socket,(sockaddr*)&sockad,sizeof(SOCKADDR));
	connect(connect_socket,(sockaddr*)&sockad,sizeof(SOCKADDR));
	char sendbuff[1000] = {0};
	char recivebuff[1000] = {0};
	recv(connect_socket,recivebuff,sizeof(recivebuff),0);
	printf("%s\n",recivebuff);
	printf("input your message: ");
	gets(sendbuff);
	send(connect_socket,sendbuff,sizeof(sendbuff)+1,0);
	closesocket(connect_socket);
	}
	WSACleanup();
	return 0;
}