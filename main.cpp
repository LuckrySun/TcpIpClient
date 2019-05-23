// InternetCommunication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include"TcpIpClient.h"
using namespace std;

int main() {
	//设置服务器信息
	char c[13] = { '1','9','2','.','1','6','8','.','1','.','1','5' };
	TcpIpClient a(c, 5099);

	//请输入服务端的ip地址
	//cout<<"请输入服务端的ip地址"<<endl;
	//char severIP[13];
	//cin >> severIP;
	//cout << severIP << endl;
	//输入服务端的端口号
	//cout << "输入服务端的端口号" << endl;
	//int hnum;
	//cin >> hnum;
	//cout << hnum << endl;
	//TcpIpClient a(severIP, hnum);

	while(1){
		if (a.linkSever())
		{
		cout << "请输入要发送的信息" << endl;
		//char senta[];
		a.sentMessenges();
		a.recMessenge();
		}
		else
		{
			cout << "服务器没有连接上" << endl;
			break;
		}
	}
	a.~TcpIpClient();

	
	return 0;
}


