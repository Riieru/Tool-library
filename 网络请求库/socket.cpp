#include"head.h"

//��ʼ��
RNSocket::RNSocket() {

	WSAStartup(MAKEWORD(2, 2), &Wsadata);

}
RNSocket::RNSocket(WORD verion , std::string&& url) {

	WSAStartup(verion, &Wsadata);

	host = gethostbyname(url.c_str());
}




RNSocket::~RNSocket() {

	// �ر��׽���
	closesocket(socketdata);

	// ���� Winsock
	WSACleanup();
}






//���Ļ���������
int RNSocket::SetUrl(std::string&& url) {

	host = gethostbyname(url.c_str());

	if (host == NULL) return 0;

	server_socket.sin_addr = *((struct in_addr*)host->h_addr);

	return 1;
}

//���Ļ�����socket����
int RNSocket::SetSocket(int af, int type, int protocol) {

	if (socketdata != NULL) {
		//���ж������ͷ�
			// �ر��׽���
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

//���÷�������������  ����Э��غͶ˿�
int RNSocket::SetServerSocket(int af, int port) {

	//��ʼ���ж�
	
	if (host == NULL) {
		printf("δ�������������ô���");
		return 0;
	}
	
	//���÷���������Ϣ
	server_socket.sin_family = af;
	server_socket.sin_port = htons(port);
	
	return 1;
}


//��������
int RNSocket::Connect() {
	//��������
	if (connect(socketdata, (sockaddr*)&server_socket, sizeof(server_socket)) < 0) {
		printf("socket����ʧ��");
		return NULL;
	}
	

	return 1;
}

//��ȡSocket����
SOCKET* RNSocket::GetSocket() {
	if (socketdata == NULL) {
		printf("socketδ��ʼ���ɹ�");
		return NULL;
	}
	return &socketdata;
}
