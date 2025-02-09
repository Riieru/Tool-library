#pragma once
#include"head.h"


//请求头组
using request =struct Request{ 
	//请求类型
	std::string type;
	//请求路径
	std::string path;
	//请求参数
	std::string parametric;
	//http版本
	std::string httpversion;
	//host域名
	std::string host;
	//客户端信息
	std::string UserAgent;
	//客户端期望获取类型
	std::string Accept;
    //请求体数据格式类型
	std::string ContentType;
	//请求Cookie信息
	std::string Cookie;
	//指示当前请求是从哪个URL页面发起的
	std::string Referer;
	//请求期望语言
	std::string AcceptLanguage;
	//请求连接状态
	std::string Connection;


	//post请求体
	std::string postdata;
};


//请求头选项组
using prefix = struct Prefix{
	//请求类型
	std::string type = "type:";
	//请求路径
	std::string path = "path:";
	//请求参数
	std::string parametric = "?";
	//http版本
	std::string httpversion = "httpversion:";
	//host域名
	std::string host = "host:";
	//客户端信息
	std::string UserAgent = "UserAgent:";
	//客户端期望获取类型
	std::string Accept = "Accept:";
	//请求体数据格式类型
	std::string ContentType = "ContentType:";
	//请求Cookie信息
	std::string Cookie = "Cookie:";
	//指示当前请求是从哪个URL页面发起的
	std::string Referer = "Referer:";
	//请求期望语言
	std::string AcceptLanguage = "AcceptLanguage:";
	//请求连接状态
	std::string Connection = "Connection:";
};


//网络请求正则表达式匹配文本
using textregex = struct textregex {
	//网络请求状态
	std::string netcondition = "[a-zA-Z]{4}/\\d\\.\\d\\s[\\d]{3}\\s([a-zA-Z])*";
	//网络状态码
	std::string statuscode = "(\\d){3}";
	//Location重定位地址
	std::string location = "Location:\\s([a-zA-Z])*://(\\w)*\\.(\\w)*\\.(\\w)*";
	//域名
	std::string domain = "";
};

//网络主程序
class NETWORK {
	//friend class instance_obj<NETWORK>;

private:
	//Socket实例
	RNSocket* socket = NULL;
	//OpenSSL实例
	OpenSSL* openssl = NULL;
	SSL* ssl = NULL;
	//ICU字符格式转换
	ICUMAIN* icu = NULL;
	//正则表达式字符串匹配
	RETRIEVE* match = NULL;
	//正则表达式匹配成功数据
	std::vector<std::string>* match_vector;
	//log文本路径
	RIIERU_FILEIO* RFile = NULL;

private:
	//请求头组
	request* requesttemp = NULL;
	//请求头
	std::string* rehead = NULL;
	//选项组名
	prefix* tyname = NULL;
	//服务器返回数据
	std::string* netdata = NULL;
	//网络匹配字符串
	textregex* regex = NULL;


	//url保留字符
	std::string* reservationschar = NULL;

	//读取缓冲字符串
	char* networkbuffer = NULL;

public:
	//初始化
	NETWORK();
	~NETWORK();

public:
	//设置Socket对象
	void SetSocket(RNSocket* socket_c);

	//设置log文本路径
	void SetTextPath(RIIERU_FILEIO* file);

public:

	//设置url保留字符
	NETWORK* SetReservationsChar(std::string && word);

	//获取服务器返回数据
	std::string* GetNetData();

	//创建网络连接
	int CreateNetwork();

	//发送https请求 --- 需要原字符串编码格式 和 目标字符串编码格式 目标字符串编码格式默认utf-8
	int HttpsWrite(request* httpshead, bool flag,std::string&& mode, UConverterType salgorithmicType = UCNV_UTF8);

	//读取https返回
	int HttpsRead(RIIERU_FILEIO* file = NULL);


	//重置socket数据(更新)
	NETWORK* ResetNetwork();

	//将utf-8字符串编码为url识别格式  参数1：需要的url    参数2：存放的空容器  参数3：需要保留的字符
	NETWORK* SetfortRul(std::string && url,std::string&& newurl, bool flag = 0);

	//读取信息检查
	int Review(request* httpshead, RIIERU_FILEIO* file = NULL);

	//重设置网络连接
	NETWORK* NetRestart(socketdata* data);

	//重设置网络连接
	NETWORK* NetRestart(std::string  data);

};