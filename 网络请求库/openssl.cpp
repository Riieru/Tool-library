#include"head.h"


int OpenSSL::Initflag = 0;
std::mutex OpenSSL::mex;


//初始化构造
OpenSSL::OpenSSL() {

}

OpenSSL::OpenSSL(SOCKET* socket_c):socket(socket_c) {

}

OpenSSL::~OpenSSL() {
	Cleanup_Openssl();
}

//参数设置
//设置openssl模式，默认通用
OpenSSL* OpenSSL::SetContext(const SSL_METHOD* meth_c) {
	if (meth_c != NULL) {
		meth = meth_c;
		return this;
	}
	return NULL;
}

//设置Socket
OpenSSL* OpenSSL::SetSocketObject(SOCKET* socket_c) {
	if (socket_c != NULL) {
		socket = socket_c;
		return this;
	}
	return NULL;
}




//初始化openssl
void OpenSSL::Init_Openssl() {

	mex.lock();

	if (Initflag == 0) {
		SSL_library_init();
		SSL_load_error_strings();
		OpenSSL_add_ssl_algorithms();
		Initflag++;
	}

	mex.unlock();
}

//释放openssl资源
void OpenSSL::Cleanup_Openssl() {
	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
}



//创建openssl服务
void OpenSSL::Create_Context() {

	if (meth == NULL) meth = TLS_method();
	
	ctx = SSL_CTX_new(meth);
	if (!ctx) {
		ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
	}
}


//创建openssl实例
OpenSSL* OpenSSL::CreateOpensslObject() {
	if (ctx == NULL) {
		printf("OpenSSL尚未初始化");
		return NULL;
	}
	ssl = SSL_new(ctx);
	if (ssl == NULL) {
		printf("CreateOpensslObject函数创建实例失败");
		return NULL;
	}
	return this;
}

//绑定需要的socket服务
OpenSSL* OpenSSL::BindSocket() {
	if (ssl == NULL || socket == NULL) {
		printf("OpenSSL未创建实例或设置socket对象");
		return NULL;
	}
	SSL_set_fd(ssl, *socket);
	return this;
}

//创建连接
OpenSSL* OpenSSL::CreateLink() {
	SSL_connect(ssl);
	return this;
}

//startopenssl
SSL* OpenSSL::startopenssl() {

	Init_Openssl();
	Create_Context();
	CreateOpensslObject();
	BindSocket();
	CreateLink();
	return ssl;
}

//返回SSL实例
SSL* OpenSSL::GetSSL() {
	if (ssl == NULL) {
		printf("SSL对象未生成");
		return 0;
	}
	return ssl;
}