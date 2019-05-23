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
	//发送缓冲区接收缓冲区
	//char sendBuf[1024];
	//char receiveBuf[1024];
	//服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;


	//
	bool initializeSocket();
	bool bindSocket();
	bool setListen();
	bool creatConnection();


};

