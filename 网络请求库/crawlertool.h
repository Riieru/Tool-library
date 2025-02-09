#pragma once

#include"head.h"

namespace Web{
	using Searchresults = struct Searchresults {
		//�����������
		std::string main = "<main[\\s\\S]*</main>";
		//ƥ�������������
		std::string Searchcount = "(<span class=\"sb_count\">[^0-9]*)(\\d+(?:,\\d+)*)([^0-9]*</span>)";
	};


	using WebData = struct WebData {
		//����������
		std::string webname;
		//���������ı�
		std::string webtext;
		//��������ͼƬ
		std::string webImage;
		//��������url
		std::string weburl;
	};

	using WebSearch = struct WebSearch {
		//�����������
		std::string count;
		//�������
		WebData data;
	};
}

//��ȡ��ҳ��Դ
class CRAWLERTOOL
{
private:
	//����ͷ
	request* quest = NULL;
	//������ʽƥ��
	RETRIEVE* match = NULL;
	//��ҳ������ʽƥ���־
	Web::Searchresults* searchdex = NULL;
	//��ҳ��������
	Web::WebSearch* websearch = NULL;

public:
	CRAWLERTOOL();
	~CRAWLERTOOL();

	//��ʼ��
	void Initialization();

public:
	//Set������ҳ������Ϣ 
	CRAWLERTOOL* SetRequest(request* head);

public:
	//��ȡ����������ҳ����
	int SetWebPage(NETWORK* net);
	
};

