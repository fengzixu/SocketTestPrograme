/*
���ƣ�����TCPЭ��������̵Ŀͻ��˳���
ʱ�䣺2014��11��25
���ߣ�fengzixu
��飺
�ڿͻ��˳����У�ֻ��Ҫ��һ���׽��־Ϳ������ͨ�Ź��ܡ���Ϊ�����ð󶨺ͼ����˿ڣ�������������������ʱ�򣬾ͻ�Я���˿ں�IP��ַ��Ϣ��
�ͻ����ڷ�������������֮�󣬻������յ�һ���������˷��ص����ӳɹ�����Ϣ��Ȼ����ʽ����ͨѶ�׶�.
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