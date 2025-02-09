#pragma once
#include"head.h"


//����ͷ��
using request =struct Request{ 
	//��������
	std::string type;
	//����·��
	std::string path;
	//�������
	std::string parametric;
	//http�汾
	std::string httpversion;
	//host����
	std::string host;
	//�ͻ�����Ϣ
	std::string UserAgent;
	//�ͻ���������ȡ����
	std::string Accept;
    //���������ݸ�ʽ����
	std::string ContentType;
	//����Cookie��Ϣ
	std::string Cookie;
	//ָʾ��ǰ�����Ǵ��ĸ�URLҳ�淢���
	std::string Referer;
	//������������
	std::string AcceptLanguage;
	//��������״̬
	std::string Connection;


	//post������
	std::string postdata;
};


//����ͷѡ����
using prefix = struct Prefix{
	//��������
	std::string type = "type:";
	//����·��
	std::string path = "path:";
	//�������
	std::string parametric = "?";
	//http�汾
	std::string httpversion = "httpversion:";
	//host����
	std::string host = "host:";
	//�ͻ�����Ϣ
	std::string UserAgent = "UserAgent:";
	//�ͻ���������ȡ����
	std::string Accept = "Accept:";
	//���������ݸ�ʽ����
	std::string ContentType = "ContentType:";
	//����Cookie��Ϣ
	std::string Cookie = "Cookie:";
	//ָʾ��ǰ�����Ǵ��ĸ�URLҳ�淢���
	std::string Referer = "Referer:";
	//������������
	std::string AcceptLanguage = "AcceptLanguage:";
	//��������״̬
	std::string Connection = "Connection:";
};


//��������������ʽƥ���ı�
using textregex = struct textregex {
	//��������״̬
	std::string netcondition = "[a-zA-Z]{4}/\\d\\.\\d\\s[\\d]{3}\\s([a-zA-Z])*";
	//����״̬��
	std::string statuscode = "(\\d){3}";
	//Location�ض�λ��ַ
	std::string location = "Location:\\s([a-zA-Z])*://(\\w)*\\.(\\w)*\\.(\\w)*";
	//����
	std::string domain = "";
};

//����������
class NETWORK {
	//friend class instance_obj<NETWORK>;

private:
	//Socketʵ��
	RNSocket* socket = NULL;
	//OpenSSLʵ��
	OpenSSL* openssl = NULL;
	SSL* ssl = NULL;
	//ICU�ַ���ʽת��
	ICUMAIN* icu = NULL;
	//������ʽ�ַ���ƥ��
	RETRIEVE* match = NULL;
	//������ʽƥ��ɹ�����
	std::vector<std::string>* match_vector;
	//log�ı�·��
	RIIERU_FILEIO* RFile = NULL;

private:
	//����ͷ��
	request* requesttemp = NULL;
	//����ͷ
	std::string* rehead = NULL;
	//ѡ������
	prefix* tyname = NULL;
	//��������������
	std::string* netdata = NULL;
	//����ƥ���ַ���
	textregex* regex = NULL;


	//url�����ַ�
	std::string* reservationschar = NULL;

	//��ȡ�����ַ���
	char* networkbuffer = NULL;

public:
	//��ʼ��
	NETWORK();
	~NETWORK();

public:
	//����Socket����
	void SetSocket(RNSocket* socket_c);

	//����log�ı�·��
	void SetTextPath(RIIERU_FILEIO* file);

public:

	//����url�����ַ�
	NETWORK* SetReservationsChar(std::string && word);

	//��ȡ��������������
	std::string* GetNetData();

	//������������
	int CreateNetwork();

	//����https���� --- ��Ҫԭ�ַ��������ʽ �� Ŀ���ַ��������ʽ Ŀ���ַ��������ʽĬ��utf-8
	int HttpsWrite(request* httpshead, bool flag,std::string&& mode, UConverterType salgorithmicType = UCNV_UTF8);

	//��ȡhttps����
	int HttpsRead(RIIERU_FILEIO* file = NULL);


	//����socket����(����)
	NETWORK* ResetNetwork();

	//��utf-8�ַ�������Ϊurlʶ���ʽ  ����1����Ҫ��url    ����2����ŵĿ�����  ����3����Ҫ�������ַ�
	NETWORK* SetfortRul(std::string && url,std::string&& newurl, bool flag = 0);

	//��ȡ��Ϣ���
	int Review(request* httpshead, RIIERU_FILEIO* file = NULL);

	//��������������
	NETWORK* NetRestart(socketdata* data);

	//��������������
	NETWORK* NetRestart(std::string  data);

};