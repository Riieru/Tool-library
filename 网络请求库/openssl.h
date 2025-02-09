#pragma once
#include"socket.h"



class OpenSSL {

	//friend class instance_obj<OpenSSL>;
private:
	//初始化标识符
	static int Initflag ;
	static std::mutex mex;

private:
	//openssl模式
	const SSL_METHOD* meth = NULL;

	//openssl_ctx实例
	SSL_CTX* ctx = NULL;

	//openssl实例
	SSL* ssl = NULL;

	//socket实例
	SOCKET* socket = NULL;

public:
	//初始化构造
	OpenSSL();
	OpenSSL(SOCKET* socket_c);

	~OpenSSL();

public:
	//参数设置
	//设置openssl模式，默认通用
	OpenSSL* SetContext(const SSL_METHOD* meth_c);

	//设置Socket
	OpenSSL* SetSocketObject(SOCKET* socket_c);

	//返回SSL实例
	SSL* GetSSL();

public:
	//初始化openssl
	void Init_Openssl();

	//释放openssl资源
	void Cleanup_Openssl();

	//创建openssl服务
	void Create_Context();

	//创建openssl实例
	OpenSSL* CreateOpensslObject();

	//绑定需要的socket服务
	OpenSSL* BindSocket();

	//创建连接
	OpenSSL* CreateLink();

	//startopenssl
	SSL* startopenssl();
};
