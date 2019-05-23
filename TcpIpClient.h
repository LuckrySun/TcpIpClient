#include "pch.h"
#include <iostream>
#include<winsock.h>
#include<string>

#pragma comment(lib,"ws2_32.lib")

using namespace std; 

//声明客户端类
class TcpIpClient {

private:
	//设置服务器端信息
	char *address;
	int htonsPoint;
	//填充服务端地址信息
	SOCKADDR_IN server_addr;
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[1024];
	char recv_buf[1024];
	//初始化函数
	void initialization();
	//定义结构体来接受数据
	struct StrPerson {
		char name[20];
		int age;
		float high;
	};

public:

	StrPerson p2;
	bool linkSever();                                  //是否连接上服务器
	char sentMessenges();                              //发送的信息
	//bool getReceive(int receive[], int n = 1024);    //判断是否有数据传输过来
	char recMessenge();                                //接收信息
	TcpIpClient() {};	                               //默认构造函数
	TcpIpClient(char*ad, int hp);                      //构造函数
	~TcpIpClient()                                     //析构函数
	{
		closesocket(s_server);                         //关闭套接字
		WSACleanup();                                  //释放DLL资源 
	};
};

