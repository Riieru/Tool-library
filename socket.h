#pragma once

#include"head.h"

using socketdata = struct socketdata {
	//ͨѶЭ����
	int af = AF_INET;
	//socket����
	int type = SOCK_STREAM;
	//ͨѶЭ��
	int protocol = IPPROTO_TCP;
	//�����Э����
	int serveraf = AF_INET;
	//����˶˿�
	int port = 443;
	//��������
	std::string host;
};


//socket������
class RNSocket{
private:

	//socket��ʼ������
	WSADATA Wsadata;

	//����
	hostent* host;

	//socket��������
	SOCKET socketdata;

	//��������������
	sockaddr_in server_socket;

public:
	//��ʼ��
	RNSocket();
	RNSocket(WORD verion,std::string&& url);
	
	~RNSocket();

public:
	//���Ļ���������
	int SetUrl(std::string&& url);

	//���Ļ�����socket����
	int SetSocket(int af,int type,int protocol);

	//���÷�������������  ����Э��غͶ˿�
	int SetServerSocket(int af,int port);

	//��������
	int Connect();
    

	//��ȡSocket����
	SOCKET* GetSocket();
};