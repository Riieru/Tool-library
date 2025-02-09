#pragma once
#include"head.h"

//正则表达式匹配

class RETRIEVE {

private:
	//匹配文本 --- 源
	std::string* sourcetext = NULL;

	//匹配标识符内容  --- 目标
	std::regex* purpose = NULL;
	std::smatch* match = NULL;

public:
	RETRIEVE();
	RETRIEVE(std::string* fsourcetext, std::string* fpurposetext);

	~RETRIEVE();

public:
	//Set
	RETRIEVE* SetSource(std::string* fsourcetext);


	RETRIEVE* SetPurpose(std::string* fpurposetext, std::regex_constants::syntax_option_type Flags = std::regex_constants::ECMAScript);

	RETRIEVE* SetTextAll(std::string* fsourcetext, std::string* fpurposetext);

public:
	//功能

	//批量匹配，并使用传递进来的容器存储匹配的内容
	RETRIEVE* MatchMo(std::vector<std::string>* vedata);

	//单个匹配，
	RETRIEVE* MatchMo(std::string* data,int index = 0);

};


