#pragma once
#include"socket.h"



class OpenSSL {

	//friend class instance_obj<OpenSSL>;
private:
	//��ʼ����ʶ��
	static int Initflag ;
	static std::mutex mex;

private:
	//opensslģʽ
	const SSL_METHOD* meth = NULL;

	//openssl_ctxʵ��
	SSL_CTX* ctx = NULL;

	//opensslʵ��
	SSL* ssl = NULL;

	//socketʵ��
	SOCKET* socket = NULL;

public:
	//��ʼ������
	OpenSSL();
	OpenSSL(SOCKET* socket_c);

	~OpenSSL();

public:
	//��������
	//����opensslģʽ��Ĭ��ͨ��
	OpenSSL* SetContext(const SSL_METHOD* meth_c);

	//����Socket
	OpenSSL* SetSocketObject(SOCKET* socket_c);

	//����SSLʵ��
	SSL* GetSSL();

public:
	//��ʼ��openssl
	void Init_Openssl();

	//�ͷ�openssl��Դ
	void Cleanup_Openssl();

	//����openssl����
	void Create_Context();

	//����opensslʵ��
	OpenSSL* CreateOpensslObject();

	//����Ҫ��socket����
	OpenSSL* BindSocket();

	//��������
	OpenSSL* CreateLink();

	//startopenssl
	SSL* startopenssl();
};
