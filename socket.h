#pragma once

#include"head.h"

using socketdata = struct socketdata {
	//通讯协议族
	int af = AF_INET;
	//socket类型
	int type = SOCK_STREAM;
	//通讯协议
	int protocol = IPPROTO_TCP;
	//服务端协议族
	int serveraf = AF_INET;
	//服务端端口
	int port = 443;
	//访问域名
	std::string host;
};


//socket功能类
class RNSocket{
private:

	//socket初始化对象
	WSADATA Wsadata;

	//域名
	hostent* host;

	//socket连接属性
	SOCKET socketdata;

	//服务器连接设置
	sockaddr_in server_socket;

public:
	//初始化
	RNSocket();
	RNSocket(WORD verion,std::string&& url);
	
	~RNSocket();

public:
	//更改或设置域名
	int SetUrl(std::string&& url);

	//更改或设置socket属性
	int SetSocket(int af,int type,int protocol);

	//设置服务器连接属性  设置协议簇和端口
	int SetServerSocket(int af,int port);

	//建立连接
	int Connect();
    

	//获取Socket对象
	SOCKET* GetSocket();
};