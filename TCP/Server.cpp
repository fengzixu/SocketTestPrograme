/*
名称：基于TCP协议的网络编程的服务器端程序
时间：2014、11、25
作者：fengzixu
简介:
总体来讲就是根据TCP的socket编程写一个服务器和客户端的程序然后运行在本地。
关于服务器端的程序，整个过程中需要用到两个套接字，一个是监听套接字，还有一个是连接套接字。
监听套接字从创建开始一直到服务器程序没有终止的之前，都是存在的，而且没有关闭过。因为他要时时刻刻监听客户端的要求。但是
连接套接字主要是用于和客户端建立连接，然后进行通信，这样一来，每次客户端的不同请求都会造成连接套接字关闭和打开，甚至是有不同的
客户端依次和服务器端进行通信。

在给socketaddr_in对象的成员赋值的时候，出了family成员不需要强制使用网络字节顺序，其他的都需要。
过程很简单，比较容易理解，主要是一些细节和API不熟悉，不过慢慢用了应该还好。
1.初始化套接字库
2.创建套接字
3.绑定端口
4.开始监听
5.接受请求，建立连接
6.处理请求，发送回应
*/




#include<stdio.h>
#include<WinSock2.h>

int main()
{
	WORD wVerionRequested = MAKEWORD(1,1);			//指定加载的套接字动态库的版本，保存相应的版本号
	WSADATA wsadata;								//加载的有关套接字的版本库的信息都会存在这个结构体里面
	int start = WSAStartup(wVerionRequested, &wsadata);             //加载套接字动态库
	if(start != 0)									//如果成功的话，那么返回值为0
		return 0;
	if(LOBYTE(wsadata.wVersion)!=1 || HIBYTE(wsadata.wVersion)!=1)       //wVersion数据成员中的高位部分表示了套接字库的副版本，低位部分表示了套接字库的主版本，检查是否是我们需要的版本号
	{
		WSACleanup();	//如果不是就要释放套接字库分配给此进程的资源
		return 0;
	}
	SOCKET server_socket = socket(AF_INET,SOCK_STREAM,0);    //创建一个套接字

	SOCKADDR_IN addrsrv;			//bind函数要绑定信息，需要用到一个结构体，里面存放本地地址的信息，他根据使用的TCP协议而变为SOCKADDR_IN类型
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(6000);				//指定要分配给这个套接字的端口
	addrsrv.sin_addr.S_un.S_addr = INADDR_ANY;		//指定本机的ip地址
	bind(server_socket, (SOCKADDR *)&addrsrv, sizeof(SOCKADDR));
	listen(server_socket,10);					//监听此端口
	SOCKADDR_IN buffptr;						//创建一个结构体，用于接收客户端发来请求的时候，携带的客户端的地址信息，IP和端口号等
	int bufflen = sizeof(SOCKADDR);
	while(1)
	{
		SOCKET accept_socket = accept(server_socket,(SOCKADDR*)&buffptr,&bufflen);		//开始不断的接受客户端请求的到来
		char sendbuff[1000] = {0};														//发送缓冲区
		char recivebuff[1000] = {0};													//接收缓冲区
		sprintf(sendbuff,"welcome %s to www.fengzixu.net",inet_ntoa(buffptr.sin_addr));					//把我需要的信息写入到发送缓冲区，利用inet_ntoa函数将buffptr指向的存储客户端地址信息结构体中的sin_addr转换为点分十进制的字符串
		send(accept_socket,sendbuff,sizeof(sendbuff)+1,0);					//之所以+1是因为发送一个字符数组过去之后一定要在最后留有一个\0字符的位置
		recv(accept_socket,recivebuff,sizeof(recivebuff),0);
		printf("%s\n",recivebuff);
		closesocket(accept_socket);					//本次处理请求结束，释放为此次请求所分配的资源，关闭连接套接字。
	}
	return 0;
}