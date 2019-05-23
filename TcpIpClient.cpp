#include "pch.h"
#include"TcpIpClient.h"

using namespace std;

//���캯���ĳ�ʼ��
TcpIpClient::TcpIpClient(char*ad, int hp) :address(ad), htonsPoint(hp)
{
	initialization();     //��ʼ������������Ϣ
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(address);
	server_addr.sin_port = htons(htonsPoint);
	cout << address << endl;
}

//���ӷ������Ƿ�ɹ�
bool TcpIpClient::linkSever() {
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "����������ʧ�ܣ�" << endl;
		return 0;
		WSACleanup();
	}
	else {
		cout << "���������ӳɹ���" << endl;
		return 1;
	}
}
//��ʼ��
void TcpIpClient::initialization()
{
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ
}

//�������ݺ���
char TcpIpClient::sentMessenges() {
	cout << "�����뷢����Ϣ:";
	cin >> send_buf;
	send_len = send(s_server, send_buf, 100, 0);
	if (send_len < 0) {
		cout << "����ʧ�ܣ�" << endl;
		return -1;
	}
}

/*
//�Ƿ��н�����Ϣ
bool TcpIpClient::getReceive(int receive[], int n = 1024) {
}
*/

//������Ϣ����
char TcpIpClient::recMessenge() {
	//������Ϣ
	recv_len = recv(s_server, recv_buf, 100, 0);

	//����ṹ����Ϣ			
	memcpy(&p2, recv_buf, 100);
	cout << p2.age << ";" << p2.high << ";" << p2.name << endl;


	if (recv_len < 0) {
		cout << "����ʧ�ܣ�" << endl;
		return -2;
	}
	else {
		//cout << "�������Ϣ:" << recv_buf << endl;
		cout << "�ɹ���������" << endl;
	}
}


