#include"head.h"


int OpenSSL::Initflag = 0;
std::mutex OpenSSL::mex;


//��ʼ������
OpenSSL::OpenSSL() {

}

OpenSSL::OpenSSL(SOCKET* socket_c):socket(socket_c) {

}

OpenSSL::~OpenSSL() {
	Cleanup_Openssl();
}

//��������
//����opensslģʽ��Ĭ��ͨ��
OpenSSL* OpenSSL::SetContext(const SSL_METHOD* meth_c) {
	if (meth_c != NULL) {
		meth = meth_c;
		return this;
	}
	return NULL;
}

//����Socket
OpenSSL* OpenSSL::SetSocketObject(SOCKET* socket_c) {
	if (socket_c != NULL) {
		socket = socket_c;
		return this;
	}
	return NULL;
}




//��ʼ��openssl
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

//�ͷ�openssl��Դ
void OpenSSL::Cleanup_Openssl() {
	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
}



//����openssl����
void OpenSSL::Create_Context() {

	if (meth == NULL) meth = TLS_method();
	
	ctx = SSL_CTX_new(meth);
	if (!ctx) {
		ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
	}
}


//����opensslʵ��
OpenSSL* OpenSSL::CreateOpensslObject() {
	if (ctx == NULL) {
		printf("OpenSSL��δ��ʼ��");
		return NULL;
	}
	ssl = SSL_new(ctx);
	if (ssl == NULL) {
		printf("CreateOpensslObject��������ʵ��ʧ��");
		return NULL;
	}
	return this;
}

//����Ҫ��socket����
OpenSSL* OpenSSL::BindSocket() {
	if (ssl == NULL || socket == NULL) {
		printf("OpenSSLδ����ʵ��������socket����");
		return NULL;
	}
	SSL_set_fd(ssl, *socket);
	return this;
}

//��������
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

//����SSLʵ��
SSL* OpenSSL::GetSSL() {
	if (ssl == NULL) {
		printf("SSL����δ����");
		return 0;
	}
	return ssl;
}