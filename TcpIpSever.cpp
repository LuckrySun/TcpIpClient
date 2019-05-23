//
//
#include"pch.h"
#include"TcpIpSever.h"


TcpIpSever::TcpIpSever()
{
}

TcpIpSever::~TcpIpSever()
{
	closesocket(s_server);
	closesocket(s_accept);
	WSACleanup();
}

bool TcpIpSever::initialization()
{
	bool is, bs, sl, cc;
	is = initializeSocket() ? true : false;
	bs = bindSocket() ? true : false;
	sl = setListen() ? true : false;
	cc = creatConnection() ? true : false;
	if (is & bs & sl & cc)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TcpIpSever::initializeSocket() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
		return false;
	}
	else {
		cout << "初始化套接字库成功！" << endl;		
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
	return true;
}

bool TcpIpSever::bindSocket()
{
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(5099);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "套接字绑定成功！" << endl;
		return true;
	}
}

bool TcpIpSever::setListen()
{
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "设置监听状态成功！" << endl;
		cout << "服务端正在监听连接，请稍候...." << endl;
		return true;
	}
	
}

bool TcpIpSever::creatConnection()
{
	int len = 0;
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "连接失败！" << endl;
		WSACleanup();
		return false;
	}
	cout << "连接建立，准备接受数据" << endl;
	return true;
}

bool TcpIpSever::getMessage(char receive[])
{
	int recv_len = 0;
	recv_len = recv(s_accept, receive, 1024, 0);
	if (recv_len < 0) {
		cout << "接受失败！" << endl;
		return false;
	}
	else {
		cout << "客户端信息:" << receive << endl;
		return true;
	}
}

bool TcpIpSever::sendMessage(char message[])
{
	int send_len = 0;
	cout << "请输入回复信息:" << "不用输入了" << endl;
	//cin >> send_buf;
	send_len = send(s_accept, message, 100, 0);
	if (send_len < 0) {
		cout << "发送失败！" << endl;
		return false;
	}
	return true;
}