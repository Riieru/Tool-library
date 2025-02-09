#include"head.h"


//构造
CRAWLERTOOL::CRAWLERTOOL() {
	Initialization();
	match = new RETRIEVE;
	searchdex = new Web::Searchresults;
	websearch = new Web::WebSearch;
}
CRAWLERTOOL::~CRAWLERTOOL() {
	delete(quest);
	delete(match);
	delete(searchdex);
	delete(websearch);
}


//初始化
void CRAWLERTOOL::Initialization() {
	//设置请求头
	quest = new request;
	quest->type = "GET";
	quest->path = "/";
	quest->httpversion = "HTTP/1.1";
	quest->UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/132.0.0.0 Safari/537.36 Edg/132.0.0.0";
	quest->AcceptLanguage = "zh-CN, zh;q=0.9, en;q=0.8, en-GB;q=0.7, en-US;q=0.6";
	quest->Connection = "close";
	quest->ContentType = "text/html; charset=utf-8";
}


//Set设置网页请求信息 
CRAWLERTOOL* CRAWLERTOOL::SetRequest(request* head) {

	if (!(head->type.empty()))               quest->type = head->type;
	if (!(head->path.empty()))				 quest->path = head->path;
	if (!(head->parametric.empty()))		 quest->parametric = head->parametric;
	if (!(head->httpversion.empty()))		 quest->httpversion = head->httpversion;
	if (!(head->host.empty()))				 quest->host = head->host;
	if (!(head->UserAgent.empty()))			 quest->UserAgent = head->UserAgent;
	if (!(head->Referer.empty()))			 quest->Referer = head->Referer;
	if (!(head->Accept.empty()))			 quest->Accept = head->Accept;
	if (!(head->AcceptLanguage.empty()))	 quest->AcceptLanguage = head->AcceptLanguage;
	if (!(head->ContentType.empty()))		 quest->ContentType = head->ContentType;
	if (!(head->Cookie.empty()))			 quest->Cookie = head->Cookie;
	if (!(head->Connection.empty()))		 quest->Connection = head->Connection;
	if (!(head->postdata.empty()))           quest->postdata = head->postdata;

	return this;
}


//获取搜索引擎网页链接
int CRAWLERTOOL::SetWebPage(NETWORK* net) {

	std::string data;
	std::string temp;

	net->SetReservationsChar("=&");

	if (!net->HttpsWrite(quest, true, "GBK")) {
		printf("网页请求信息有误，请检查请求头或请求体错误");
		return NULL;
	}

	;
	if (!net->HttpsRead()) {
		printf("该链接无法访问");
		return NULL;
	}
	//爬取网页链接  返回搜索结果主体
	match->SetSource(net->GetNetData())->SetPurpose(&searchdex->main, std::regex_constants::ECMAScript | std::regex_constants::icase)->MatchMo(&data);
	//读取结果数量
	match->SetSource(&data)->SetPurpose(&searchdex->Searchcount)->MatchMo(&websearch->count,2);
	printf("搜索结果一共有：%s个", websearch->count.c_str());


	//将搜索结果依次存储
	//捕获搜索结果





	RIIERU_FILEIO file("C:\\Users\\ColdWine\\Desktop\\新建文本文档 (3).TXT", "w+", 4096);
	file.Write(&data);



}