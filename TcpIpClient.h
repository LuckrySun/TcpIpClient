#include "pch.h"
#include <iostream>
#include<winsock.h>
#include<string>

#pragma comment(lib,"ws2_32.lib")

using namespace std; 

//�����ͻ�����
class TcpIpClient {

private:
	//���÷���������Ϣ
	char *address;
	int htonsPoint;
	//������˵�ַ��Ϣ
	SOCKADDR_IN server_addr;
	//���������׽��֣����������׽���
	SOCKET s_server;
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[1024];
	char recv_buf[1024];
	//��ʼ������
	void initialization();
	//����ṹ������������
	struct StrPerson {
		char name[20];
		int age;
		float high;
	};

public:

	StrPerson p2;
	bool linkSever();                                  //�Ƿ������Ϸ�����
	char sentMessenges();                              //���͵���Ϣ
	//bool getReceive(int receive[], int n = 1024);    //�ж��Ƿ������ݴ������
	char recMessenge();                                //������Ϣ
	TcpIpClient() {};	                               //Ĭ�Ϲ��캯��
	TcpIpClient(char*ad, int hp);                      //���캯��
	~TcpIpClient()                                     //��������
	{
		closesocket(s_server);                         //�ر��׽���
		WSACleanup();                                  //�ͷ�DLL��Դ 
	};
};

