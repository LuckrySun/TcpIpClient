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
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
		return false;
	}
	else {
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;		
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ
	return true;
}

bool TcpIpSever::bindSocket()
{
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(5099);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "�׽��ְ󶨳ɹ���" << endl;
		return true;
	}
}

bool TcpIpSever::setListen()
{
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "���ü���״̬ʧ�ܣ�" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "���ü���״̬�ɹ���" << endl;
		cout << "��������ڼ������ӣ����Ժ�...." << endl;
		return true;
	}
	
}

bool TcpIpSever::creatConnection()
{
	int len = 0;
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "����ʧ�ܣ�" << endl;
		WSACleanup();
		return false;
	}
	cout << "���ӽ�����׼����������" << endl;
	return true;
}

bool TcpIpSever::getMessage(char receive[])
{
	int recv_len = 0;
	recv_len = recv(s_accept, receive, 1024, 0);
	if (recv_len < 0) {
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	else {
		cout << "�ͻ�����Ϣ:" << receive << endl;
		return true;
	}
}

bool TcpIpSever::sendMessage(char message[])
{
	int send_len = 0;
	cout << "������ظ���Ϣ:" << "����������" << endl;
	//cin >> send_buf;
	send_len = send(s_accept, message, 100, 0);
	if (send_len < 0) {
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}