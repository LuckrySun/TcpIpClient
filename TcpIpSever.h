#pragma once

#include"pch.h"
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class TcpIpSever
{
public:
	TcpIpSever();
	~TcpIpSever();
	bool getMessage(char receive[]);
	bool sendMessage(char send[]);

	bool initialization();

private:
	//���ͻ��������ջ�����
	//char sendBuf[1024];
	//char receiveBuf[1024];
	//������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;


	//
	bool initializeSocket();
	bool bindSocket();
	bool setListen();
	bool creatConnection();


};

