/*
���ƣ�����UDPЭ��ķ���˳���
���ߣ� fengzixu
ʱ��: 2014/11/25
��飺
����UDP��TCP����Э��Ĳ�ͬ�汾�����µĿ�ܶ�����ͬ�ģ�ֻ���м���ϸ�ڲ�ͬ��
���ȣ�����TCPЭ��ķ���ˣ���Ҫ�����׽��֣�һ�������󶨶˿ڲ��Ҽ�����һ�������������ӡ�
����UDPЭ���в���Ҫ�����ͽ������ӣ��󶨶˿�֮��ֱ�ӾͿ���ͨ�ţ��Ҵ�ʼ����ֻ��һ���׽���(�ڴ����׽��ֵ�ʱ��TCP��UDP�������ǲ�һ����)
��Σ����ǽ�����Ϣ��API��ͬ��TCP��recv��UDP��recvfrom
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