#include"head.h"

//��ʼ��
NETWORK::NETWORK() {
	rehead = new std::string;
	networkbuffer = new char[1024];
	netdata = new std::string;
	tyname = new prefix;
	icu = new ICUMAIN;
	match = new RETRIEVE;
	regex = new textregex;
	match_vector = new std::vector<std::string>;
}

NETWORK::~NETWORK() {
	delete(openssl);
	delete(networkbuffer);
	delete(netdata);
	delete(tyname);
	delete(rehead);
	delete(icu);
	if (reservationschar != NULL) delete(reservationschar);
	delete(match);
	delete(regex);
	delete(match_vector);
}



//����url�����ַ�
NETWORK* NETWORK::SetReservationsChar(std::string&& word) {
	if (reservationschar == NULL) {
		//����
		reservationschar = new std::string(word);
	}
	else
	{
		reservationschar->clear();
		reservationschar->append(word);
	}
	if (reservationschar != NULL) return this;
	return NULL;
}



//����log�ı�·��
void NETWORK::SetTextPath(RIIERU_FILEIO* file) {
	RFile = file;
}



//����Socket����
void NETWORK::SetSocket(RNSocket* socket_c) {
	//����������ã�֮ǰ��Ҫ�ͷ�
	if (socket != NULL) {
		delete(openssl);
		openssl = NULL;
	}
	socket = socket_c;
}

//������������
int NETWORK::CreateNetwork() {
	if (socket == NULL) {
		printf("NETWORK��δ��ʼ��");
		return 0;
	}
	if (openssl == NULL) {
		openssl = new OpenSSL;
		//����OPENSSL����
		ssl = openssl->SetSocketObject(socket->GetSocket())->startopenssl();
	}
	return 1;
}


//��ȡ��������������
std::string* NETWORK::GetNetData() {
	return netdata;
}


//����socket����(����)
NETWORK* NETWORK::ResetNetwork() {
	//����������ã�֮ǰ��Ҫ�ͷ�
	if (socket != NULL) {
		delete(openssl);
		openssl = NULL;
	}
	//����
	CreateNetwork();
	return this;
}


//����https���� --- ��Ҫԭ�ַ��������ʽ �� Ŀ���ַ��������ʽ Ŀ���ַ��������ʽĬ��utf-8
int NETWORK::HttpsWrite(request* httpshead, bool flag,std::string&& mode, UConverterType salgorithmicType) {
	if (rehead == NULL) {
		printf("NETWORKʵ����δ��ʼ������ͷ");
		return 0;
	}
	if (httpshead == NULL) {
		printf("����ͷ�鴫�ݴ���");
		return NULL;
	}
	requesttemp = httpshead;
	//�Բ������б���
	if (!(httpshead->parametric.empty()) && flag) {
		//ת��utf-8
		std::string temp;
		icu->SetConverter(std::move(mode))->CdConversion(salgorithmicType, std::move(httpshead->parametric), std::move(temp));
		httpshead->parametric.clear();
		//����Ϊurl
		SetfortRul(std::move(temp), std::move(httpshead->parametric),reservationschar);


	}

	rehead->clear();
	//�������ͷ

	//�����ж�
	if (!(httpshead->type.empty()))                  rehead->append(httpshead->type).append(" ");
	if (!(httpshead->path.empty()))                  rehead->append(httpshead->path);
	if (!(httpshead->parametric.empty()))            rehead->append(tyname->parametric)     .append(httpshead->parametric);

	rehead->append(" ");

	if (!(httpshead->httpversion.empty()))           rehead->append(httpshead->httpversion) .append("\r\n");
	if (!(httpshead->host.empty()))                  rehead->append(tyname->host)           .append(httpshead->host)           .append("\r\n");
	if (!(httpshead->UserAgent.empty()))             rehead->append(tyname->UserAgent)		.append(httpshead->UserAgent)	   .append("\r\n");
	if (!(httpshead->Referer.empty()))               rehead->append(tyname->Referer)		.append(httpshead->Referer)		   .append("\r\n");
	if (!(httpshead->Accept.empty()))                rehead->append(tyname->Accept)			.append(httpshead->Accept)		   .append("\r\n");
	if (!(httpshead->AcceptLanguage.empty()))        rehead->append(tyname->AcceptLanguage)	.append(httpshead->AcceptLanguage) .append("\r\n");
	if (!(httpshead->ContentType.empty()))           rehead->append(tyname->ContentType)	.append(httpshead->ContentType)	   .append("\r\n");
	if (!(httpshead->Cookie.empty()))                rehead->append(tyname->Cookie)			.append(httpshead->Cookie)		   .append("\r\n");
	if (!(httpshead->Connection.empty()))            rehead->append(tyname->Connection)     .append(httpshead->Connection)     .append("\r\n");

	rehead->append("\r\n");
	
	//post����ϲ�
	if (!(httpshead->postdata.empty()))     rehead->append(httpshead->postdata);

		//��������
	

	return SSL_write(ssl, rehead->c_str(), rehead->length());
}

//��ȡhttps����
int NETWORK::HttpsRead(RIIERU_FILEIO* file) {
	//�����ַ������
	if (networkbuffer == NULL) {
		printf("�����ַ���δ��ʼ��");
		return 0;
	}

	if (netdata == NULL) {
		printf("�����ַ���δ��ʼ��");
		return 0;
	}

	netdata->clear();

	//ѭ����ȡ
	while (true) {
		int received = SSL_read(ssl, networkbuffer, 1024 - 1);
		if (received == SOCKET_ERROR) {
			std::cerr << "Receive error. Error Code: " << WSAGetLastError() << std::endl;
			break;
		}
		else if (received == 0) {
			break; // ���ӹر�
		}
		networkbuffer[received] = '\0'; // ȷ���ַ����� null ��β

	//	std::cout << networkbuffer;
		//����
		netdata->append(networkbuffer);
 	}

	if (file != NULL) file->Write(netdata);
	if ((file == NULL) && (RFile != NULL)) RFile->Write(netdata);
	//����Ƿ񱨴������ض�λ,����޷����ʣ����ر�����Ϣ

	return Review(requesttemp, file);
}





//��utf-8�ַ�������Ϊurlʶ���ʽ     ����1����Ҫ��url    ����2����ŵĿ�����  ����3���Ƿ���Ҫ�����ַ�
NETWORK* NETWORK::SetfortRul(std::string&& url, std::string&& newurl, bool flag) {

	if (!newurl.empty()) {
		printf("Ŀ���ַ�����Ϊ�գ���SetfortRul������");
		return NULL;
	}
	if (flag && (reservationschar == NULL)) {
		printf("δ������Ҫ�������ַ�����SetfortRul������");
		return NULL;
	}


	auto data = url | std::views::chunk_by([](auto elm1, auto elm2) {
		return (elm2 & 0xC0) == 0x80;
		});

		for (auto e1 : data) {

			//����ǵ��ֽڣ��ж��Ƿ�Ϊ�����ַ�
			if (e1.size() == 1) {
				//�ж��Ƿ���Ҫ����
				if (isalnum(e1.begin()[0]) || e1.begin()[0] == '-' || e1.begin()[0] == '_' || e1.begin()[0] == '.' || e1.begin()[0] == '~') {
					//��Ҫ����
					newurl.push_back(e1.begin()[0]);
					continue;
				}

				//�ж϶����ַ�
				if (flag && ((reservationschar != NULL) && (reservationschar->find(e1.begin()[0]) >= 0))) {
					//����
					newurl.push_back(e1.begin()[0]);
					continue;
				}
			}
			//��Ҫ����
			for (auto e2 : e1) {
				newurl.append(std::format("%{0:02X}", e2));
			}

		}
		return this;
}


//��ȡ��Ϣ���
int NETWORK::Review(request* httpshead,RIIERU_FILEIO* file) {
	//���ݷǿ��ж�
	if ((netdata == NULL) || netdata->empty()) {
		printf("������δ�������ݻ��ʼ��ʧ�ܣ���NETWORK");
		return NULL;
	}

	std::string temp;

	//ƥ������----�ж��Ƿ�ɹ�����
	match->SetSource(netdata)->SetPurpose(&regex->netcondition)->MatchMo(&temp);

	//δ�ɹ����ӣ������޸�
	//��ѯ�ڲ�
	if (match->SetSource(&temp)->SetPurpose(&regex->statuscode)->MatchMo(&temp)) {
		//�ж�״̬��
		if (temp == "200") return 1;
		if (temp == "302") {
			printf("ԭ��������ʧ�ܣ������ض�λ������");
			//�ض���
			if (match->SetSource(netdata)->SetPurpose(&regex->location)->MatchMo(&temp)) {
				//����������������
				int strindex = temp.rfind("/");
				if (strindex < 0) {
					printf("url��ѯʧ��");
					return NULL;
				}

				temp = temp.substr(strindex+1, temp.size() - 1);
				NetRestart(temp);
				httpshead->host = temp;
				HttpsWrite(httpshead,false, "utf-8");

				HttpsRead(file);
				
			}
			return 1;
			
		}
		printf("δ֪����");
		return NULL;

	}
	
	
	
}



//��������������
NETWORK* NETWORK::NetRestart(socketdata* data) {
	//����socket
	if (!data->host.empty()) {
		socket->SetUrl(std::move(data->host));
	}
	socket->SetSocket(data->af, data->type, data->protocol);
	socket->SetServerSocket(data->serveraf, data->port);

	socket->Connect();

	ResetNetwork();
	return this;
}

//��������������
NETWORK* NETWORK::NetRestart(std::string data) {
	socketdata redata;
	redata.host = data;
	return NetRestart(&redata);
}

