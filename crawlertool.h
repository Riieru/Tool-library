#pragma once

#include"head.h"

namespace Web{
	using Searchresults = struct Searchresults {
		//搜索结果主体
		std::string main = "<main[\\s\\S]*</main>";
		//匹配搜索结果数量
		std::string Searchcount = "(<span class=\"sb_count\">[^0-9]*)(\\d+(?:,\\d+)*)([^0-9]*</span>)";
	};


	using WebData = struct WebData {
		//搜索对象名
		std::string webname;
		//搜索对象文本
		std::string webtext;
		//搜索对象图片
		std::string webImage;
		//搜索对象url
		std::string weburl;
	};

	using WebSearch = struct WebSearch {
		//搜索结果数量
		std::string count;
		//搜索结果
		WebData data;
	};
}

//爬取网页资源
class CRAWLERTOOL
{
private:
	//请求头
	request* quest = NULL;
	//正则表达式匹配
	RETRIEVE* match = NULL;
	//网页正则表达式匹配标志
	Web::Searchresults* searchdex = NULL;
	//网页搜索数据
	Web::WebSearch* websearch = NULL;

public:
	CRAWLERTOOL();
	~CRAWLERTOOL();

	//初始化
	void Initialization();

public:
	//Set设置网页请求信息 
	CRAWLERTOOL* SetRequest(request* head);

public:
	//获取搜索引擎网页链接
	int SetWebPage(NETWORK* net);
	
};

