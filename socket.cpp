#include"head.h"

//初始化
RNSocket::RNSocket() {

	WSAStartup(MAKEWORD(2, 2), &Wsadata);

}
RNSocket::RNSocket(WORD verion , std::string&& url) {

	WSAStartup(verion, &Wsadata);

	host = gethostbyname(url.c_str());
}




RNSocket::~RNSocket() {

	// 关闭套接字
	closesocket(socketdata);

	// 清理 Winsock
	WSACleanup();
}






//更改或设置域名
int RNSocket::SetUrl(std::string&& url) {

	host = gethostbyname(url.c_str());

	if (host == NULL) return 0;

	server_socket.sin_addr = *((struct in_addr*)host->h_addr);

	return 1;
}

//更改或设置socket属性
int RNSocket::SetSocket(int af, int type, int protocol) {

	if (socketdata != NULL) {
		//已有对象，先释放
			// 关闭套接字
		closesocket(socketdata);
		socketdata = NULL;
	}
	socketdata = socket(af, type, protocol);
	if (socketdata == INVALID_SOCKET) {
		std::cerr << "Could not create socket. Error Code: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	return 1;
}

//设置服务器连接属性  设置协议簇和端口
int RNSocket::SetServerSocket(int af, int port) {

	//初始化判断
	
	if (host == NULL) {
		printf("未设置域名或设置错误");
		return 0;
	}
	
	//设置服务器端信息
	server_socket.sin_family = af;
	server_socket.sin_port = htons(port);
	
	return 1;
}


//建立连接
int RNSocket::Connect() {
	//建立连接
	if (connect(socketdata, (sockaddr*)&server_socket, sizeof(server_socket)) < 0) {
		printf("socket链接失败");
		return NULL;
	}
	

	return 1;
}

//获取Socket对象
SOCKET* RNSocket::GetSocket() {
	if (socketdata == NULL) {
		printf("socket未初始化成功");
		return NULL;
	}
	return &socketdata;
}
