/*
���ƣ�����TCPЭ��������̵ķ������˳���
ʱ�䣺2014��11��25
���ߣ�fengzixu
���:
�����������Ǹ���TCP��socket���дһ���������Ϳͻ��˵ĳ���Ȼ�������ڱ��ء�
���ڷ������˵ĳ���������������Ҫ�õ������׽��֣�һ���Ǽ����׽��֣�����һ���������׽��֡�
�����׽��ִӴ�����ʼһֱ������������û����ֹ��֮ǰ�����Ǵ��ڵģ�����û�йرչ�����Ϊ��Ҫʱʱ�̼̿����ͻ��˵�Ҫ�󡣵���
�����׽�����Ҫ�����ںͿͻ��˽������ӣ�Ȼ�����ͨ�ţ�����һ����ÿ�οͻ��˵Ĳ�ͬ���󶼻���������׽��ֹرպʹ򿪣��������в�ͬ��
�ͻ������κͷ������˽���ͨ�š�

�ڸ�socketaddr_in����ĳ�Ա��ֵ��ʱ�򣬳���family��Ա����Ҫǿ��ʹ�������ֽ�˳�������Ķ���Ҫ��
���̺ܼ򵥣��Ƚ�������⣬��Ҫ��һЩϸ�ں�API����Ϥ��������������Ӧ�û��á�
1.��ʼ���׽��ֿ�
2.�����׽���
3.�󶨶˿�
4.��ʼ����
5.�������󣬽�������
6.�������󣬷��ͻ�Ӧ
*/




#include<stdio.h>
#include<WinSock2.h>

int main()
{
	WORD wVerionRequested = MAKEWORD(1,1);			//ָ�����ص��׽��ֶ�̬��İ汾��������Ӧ�İ汾��
	WSADATA wsadata;								//���ص��й��׽��ֵİ汾�����Ϣ�����������ṹ������
	int start = WSAStartup(wVerionRequested, &wsadata);             //�����׽��ֶ�̬��
	if(start != 0)									//����ɹ��Ļ�����ô����ֵΪ0
		return 0;
	if(LOBYTE(wsadata.wVersion)!=1 || HIBYTE(wsadata.wVersion)!=1)       //wVersion���ݳ�Ա�еĸ�λ���ֱ�ʾ���׽��ֿ�ĸ��汾����λ���ֱ�ʾ���׽��ֿ�����汾������Ƿ���������Ҫ�İ汾��
	{
		WSACleanup();	//������Ǿ�Ҫ�ͷ��׽��ֿ������˽��̵���Դ
		return 0;
	}
	SOCKET server_socket = socket(AF_INET,SOCK_STREAM,0);    //����һ���׽���

	SOCKADDR_IN addrsrv;			//bind����Ҫ����Ϣ����Ҫ�õ�һ���ṹ�壬�����ű��ص�ַ����Ϣ��������ʹ�õ�TCPЭ�����ΪSOCKADDR_IN����
	addrsrv.sin_family = AF_INET;
	addrsrv.sin_port = htons(6000);				//ָ��Ҫ���������׽��ֵĶ˿�
	addrsrv.sin_addr.S_un.S_addr = INADDR_ANY;		//ָ��������ip��ַ
	bind(server_socket, (SOCKADDR *)&addrsrv, sizeof(SOCKADDR));
	listen(server_socket,10);					//�����˶˿�
	SOCKADDR_IN buffptr;						//����һ���ṹ�壬���ڽ��տͻ��˷��������ʱ��Я���Ŀͻ��˵ĵ�ַ��Ϣ��IP�Ͷ˿ںŵ�
	int bufflen = sizeof(SOCKADDR);
	while(1)
	{
		SOCKET accept_socket = accept(server_socket,(SOCKADDR*)&buffptr,&bufflen);		//��ʼ���ϵĽ��ܿͻ�������ĵ���
		char sendbuff[1000] = {0};														//���ͻ�����
		char recivebuff[1000] = {0};													//���ջ�����
		sprintf(sendbuff,"welcome %s to www.fengzixu.net",inet_ntoa(buffptr.sin_addr));					//������Ҫ����Ϣд�뵽���ͻ�����������inet_ntoa������buffptrָ��Ĵ洢�ͻ��˵�ַ��Ϣ�ṹ���е�sin_addrת��Ϊ���ʮ���Ƶ��ַ���
		send(accept_socket,sendbuff,sizeof(sendbuff)+1,0);					//֮����+1����Ϊ����һ���ַ������ȥ֮��һ��Ҫ���������һ��\0�ַ���λ��
		recv(accept_socket,recivebuff,sizeof(recivebuff),0);
		printf("%s\n",recivebuff);
		closesocket(accept_socket);					//���δ�������������ͷ�Ϊ�˴��������������Դ���ر������׽��֡�
	}
	return 0;
}