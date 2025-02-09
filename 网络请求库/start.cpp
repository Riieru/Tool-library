#include"head.h"

void work(NETWORK* net);

void main() {

	//设置控制台为utf-8
	//SetConsoleOutputCP(65001);

	//创建Socket
	RNSocket socket;
	//设置域名及设置
	socket.SetUrl("www.bilibili.com");
	socket.SetSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.SetServerSocket(AF_INET, 443);
	socket.Connect();

	

	//创建连接
	NETWORK* net = new NETWORK;
	net->SetSocket(&socket);
	net->CreateNetwork();

	RIIERU_FILEIO file("C:\\Users\\ColdWine\\Desktop\\新建文本文档 (2).TXT", "w+", 4096);
	net->SetTextPath(&file);

	work(net);






	











    
	////设置匹配正则
	//std::vector<std::string> ve;
	//std::string aa("HTTP/1.1 302 Found\nCache - Control: private");
	//
	//RETRIEVE* re = new RETRIEVE();
	//re->SetSource(&aa);
	//re->SetPurpose(&Link);
	//re->MatchMo(&ve);


	//net->NetRestart("www.baidu.com");

	////设置请求头
	//request* rq1 = new request;
	//rq1->type = "GET";
	//rq1->httpversion = "HTTP/1.1";
	//rq1->path = "/";
	//rq1->host = "www.baidu.com";
	//rq1->UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36 Edg/131.0.0.0";
	//rq1->AcceptLanguage = "zh-CN, zh;q=0.9, en;q=0.8, en-GB;q=0.7, en-US;q=0.6";
	//rq1->Connection = "close";

	//net->HttpsWrite(rq1,true,"GBK");
	//net->HttpsRead(&file);

	//ICUMAIN* im = new ICUMAIN;
	//std::string aaq;
	//std::string bbq;
 //	im->SetConverter("GBK")->CdConversion(UCNV_UTF8, "ab22色的非常所谓的e/ d", std::move(aaq));
	//net->SetfortRul(std::move(aaq), std::move(bbq));
	//

}



void work(NETWORK* net) {
	//请求头
	request quest;
//	quest.parametric = "vd_source=25b345409db89cd824ba8fd850020814";
//	quest.path = "/video/av708644144/";
	quest.host = "www.bilibili.com";

	CRAWLERTOOL* crawe = new CRAWLERTOOL;

	crawe->SetRequest(&quest)->SetWebPage(net);






}