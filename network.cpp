#include"head.h"

//初始化
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



//设置url保留字符
NETWORK* NETWORK::SetReservationsChar(std::string&& word) {
	if (reservationschar == NULL) {
		//创建
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



//设置log文本路径
void NETWORK::SetTextPath(RIIERU_FILEIO* file) {
	RFile = file;
}



//设置Socket对象
void NETWORK::SetSocket(RNSocket* socket_c) {
	//如果重新设置，之前的要释放
	if (socket != NULL) {
		delete(openssl);
		openssl = NULL;
	}
	socket = socket_c;
}

//创建网络连接
int NETWORK::CreateNetwork() {
	if (socket == NULL) {
		printf("NETWORK尚未初始化");
		return 0;
	}
	if (openssl == NULL) {
		openssl = new OpenSSL;
		//创建OPENSSL连接
		ssl = openssl->SetSocketObject(socket->GetSocket())->startopenssl();
	}
	return 1;
}


//获取服务器返回数据
std::string* NETWORK::GetNetData() {
	return netdata;
}


//重置socket数据(更新)
NETWORK* NETWORK::ResetNetwork() {
	//如果重新设置，之前的要释放
	if (socket != NULL) {
		delete(openssl);
		openssl = NULL;
	}
	//更新
	CreateNetwork();
	return this;
}


//发送https请求 --- 需要原字符串编码格式 和 目标字符串编码格式 目标字符串编码格式默认utf-8
int NETWORK::HttpsWrite(request* httpshead, bool flag,std::string&& mode, UConverterType salgorithmicType) {
	if (rehead == NULL) {
		printf("NETWORK实例中未初始化请求头");
		return 0;
	}
	if (httpshead == NULL) {
		printf("请求头组传递错误");
		return NULL;
	}
	requesttemp = httpshead;
	//对参数进行编码
	if (!(httpshead->parametric.empty()) && flag) {
		//转换utf-8
		std::string temp;
		icu->SetConverter(std::move(mode))->CdConversion(salgorithmicType, std::move(httpshead->parametric), std::move(temp));
		httpshead->parametric.clear();
		//编码为url
		SetfortRul(std::move(temp), std::move(httpshead->parametric),reservationschar);


	}

	rehead->clear();
	//组合请求头

	//参数判断
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
	
	//post请求合并
	if (!(httpshead->postdata.empty()))     rehead->append(httpshead->postdata);

		//发送请求
	

	return SSL_write(ssl, rehead->c_str(), rehead->length());
}

//读取https返回
int NETWORK::HttpsRead(RIIERU_FILEIO* file) {
	//缓冲字符串检查
	if (networkbuffer == NULL) {
		printf("缓冲字符串未初始化");
		return 0;
	}

	if (netdata == NULL) {
		printf("数据字符串未初始化");
		return 0;
	}

	netdata->clear();

	//循环读取
	while (true) {
		int received = SSL_read(ssl, networkbuffer, 1024 - 1);
		if (received == SOCKET_ERROR) {
			std::cerr << "Receive error. Error Code: " << WSAGetLastError() << std::endl;
			break;
		}
		else if (received == 0) {
			break; // 连接关闭
		}
		networkbuffer[received] = '\0'; // 确保字符串以 null 结尾

	//	std::cout << networkbuffer;
		//保存
		netdata->append(networkbuffer);
 	}

	if (file != NULL) file->Write(netdata);
	if ((file == NULL) && (RFile != NULL)) RFile->Write(netdata);
	//检查是否报错，尝试重定位,如果无法访问，返回报错信息

	return Review(requesttemp, file);
}





//将utf-8字符串编码为url识别格式     参数1：需要的url    参数2：存放的空容器  参数3：是否需要保留字符
NETWORK* NETWORK::SetfortRul(std::string&& url, std::string&& newurl, bool flag) {

	if (!newurl.empty()) {
		printf("目标字符串不为空，在SetfortRul函数中");
		return NULL;
	}
	if (flag && (reservationschar == NULL)) {
		printf("未设置需要保留的字符，在SetfortRul函数中");
		return NULL;
	}


	auto data = url | std::views::chunk_by([](auto elm1, auto elm2) {
		return (elm2 & 0xC0) == 0x80;
		});

		for (auto e1 : data) {

			//如果是单字节，判断是否为特殊字符
			if (e1.size() == 1) {
				//判断是否需要保留
				if (isalnum(e1.begin()[0]) || e1.begin()[0] == '-' || e1.begin()[0] == '_' || e1.begin()[0] == '.' || e1.begin()[0] == '~') {
					//需要保留
					newurl.push_back(e1.begin()[0]);
					continue;
				}

				//判断额外字符
				if (flag && ((reservationschar != NULL) && (reservationschar->find(e1.begin()[0]) >= 0))) {
					//保留
					newurl.push_back(e1.begin()[0]);
					continue;
				}
			}
			//需要编码
			for (auto e2 : e1) {
				newurl.append(std::format("%{0:02X}", e2));
			}

		}
		return this;
}


//读取信息检查
int NETWORK::Review(request* httpshead,RIIERU_FILEIO* file) {
	//数据非空判断
	if ((netdata == NULL) || netdata->empty()) {
		printf("服务器未返回数据或初始化失败，于NETWORK");
		return NULL;
	}

	std::string temp;

	//匹配数据----判断是否成功连接
	match->SetSource(netdata)->SetPurpose(&regex->netcondition)->MatchMo(&temp);

	//未成功连接，尝试修改
	//查询内部
	if (match->SetSource(&temp)->SetPurpose(&regex->statuscode)->MatchMo(&temp)) {
		//判断状态码
		if (temp == "200") return 1;
		if (temp == "302") {
			printf("原域名访问失败，正在重定位新链接");
			//重定向
			if (match->SetSource(netdata)->SetPurpose(&regex->location)->MatchMo(&temp)) {
				//重新设置网络连接
				int strindex = temp.rfind("/");
				if (strindex < 0) {
					printf("url查询失败");
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
		printf("未知错误");
		return NULL;

	}
	
	
	
}



//重设置网络连接
NETWORK* NETWORK::NetRestart(socketdata* data) {
	//重置socket
	if (!data->host.empty()) {
		socket->SetUrl(std::move(data->host));
	}
	socket->SetSocket(data->af, data->type, data->protocol);
	socket->SetServerSocket(data->serveraf, data->port);

	socket->Connect();

	ResetNetwork();
	return this;
}

//重设置网络连接
NETWORK* NETWORK::NetRestart(std::string data) {
	socketdata redata;
	redata.host = data;
	return NetRestart(&redata);
}

