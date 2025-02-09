#include"head.h"


//����
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


//��ʼ��
void CRAWLERTOOL::Initialization() {
	//��������ͷ
	quest = new request;
	quest->type = "GET";
	quest->path = "/";
	quest->httpversion = "HTTP/1.1";
	quest->UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/132.0.0.0 Safari/537.36 Edg/132.0.0.0";
	quest->AcceptLanguage = "zh-CN, zh;q=0.9, en;q=0.8, en-GB;q=0.7, en-US;q=0.6";
	quest->Connection = "close";
	quest->ContentType = "text/html; charset=utf-8";
}


//Set������ҳ������Ϣ 
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


//��ȡ����������ҳ����
int CRAWLERTOOL::SetWebPage(NETWORK* net) {

	std::string data;
	std::string temp;

	net->SetReservationsChar("=&");

	if (!net->HttpsWrite(quest, true, "GBK")) {
		printf("��ҳ������Ϣ������������ͷ�����������");
		return NULL;
	}

	;
	if (!net->HttpsRead()) {
		printf("�������޷�����");
		return NULL;
	}
	//��ȡ��ҳ����  ���������������
	match->SetSource(net->GetNetData())->SetPurpose(&searchdex->main, std::regex_constants::ECMAScript | std::regex_constants::icase)->MatchMo(&data);
	//��ȡ�������
	match->SetSource(&data)->SetPurpose(&searchdex->Searchcount)->MatchMo(&websearch->count,2);
	printf("�������һ���У�%s��", websearch->count.c_str());


	//������������δ洢
	//�����������





	RIIERU_FILEIO file("C:\\Users\\ColdWine\\Desktop\\�½��ı��ĵ� (3).TXT", "w+", 4096);
	file.Write(&data);



}