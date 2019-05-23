#include "pch.h"
#include"TcpIpClient.h"

using namespace std;

//构造函数的初始化
TcpIpClient::TcpIpClient(char*ad, int hp) :address(ad), htonsPoint(hp)
{
	initialization();     //初始化服务器端信息
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(address);
	server_addr.sin_port = htons(htonsPoint);
	cout << address << endl;
}

//连接服务器是否成功
bool TcpIpClient::linkSever() {
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		return 0;
		WSACleanup();
	}
	else {
		cout << "服务器连接成功！" << endl;
		return 1;
	}
}
//初始化
void TcpIpClient::initialization()
{
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

//发送数据函数
char TcpIpClient::sentMessenges() {
	cout << "请输入发送信息:";
	cin >> send_buf;
	send_len = send(s_server, send_buf, 100, 0);
	if (send_len < 0) {
		cout << "发送失败！" << endl;
		return -1;
	}
}

/*
//是否有接收信息
bool TcpIpClient::getReceive(int receive[], int n = 1024) {
}
*/

//接收信息函数
char TcpIpClient::recMessenge() {
	//接收信息
	recv_len = recv(s_server, recv_buf, 100, 0);

	//输出结构体信息			
	memcpy(&p2, recv_buf, 100);
	cout << p2.age << ";" << p2.high << ";" << p2.name << endl;


	if (recv_len < 0) {
		cout << "接受失败！" << endl;
		return -2;
	}
	else {
		//cout << "服务端信息:" << recv_buf << endl;
		cout << "成功接收数据" << endl;
	}
}


