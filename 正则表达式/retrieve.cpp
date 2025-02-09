#include"head.h"

//初始化

RETRIEVE::RETRIEVE() {
	match = new std::smatch;
}
RETRIEVE::RETRIEVE(std::string* fsourcetext, std::string* fpurposetext) : sourcetext(fsourcetext){
	match = new std::smatch;
	SetPurpose(fpurposetext);
}

RETRIEVE::~RETRIEVE() {
	if (match != NULL) delete(match);
	if (purpose != NULL) delete(purpose);
}



//Set
RETRIEVE* RETRIEVE::SetSource(std::string* fsourcetext) {
	sourcetext = fsourcetext;
	return this;
}

RETRIEVE* RETRIEVE::SetPurpose(std::string* fpurposetext, std::regex_constants::syntax_option_type Flags) {
	if (purpose != NULL) {
		delete(purpose);
		purpose = NULL;
	}

	purpose = new std::regex(*fpurposetext, Flags);
	return this;
}

RETRIEVE* RETRIEVE::SetTextAll(std::string* fsourcetext, std::string* fpurposetext) {
	sourcetext = fsourcetext;
	SetPurpose(fpurposetext);
	return this;
}


//批量匹配，并使用传递进来的容器存储匹配的内容
RETRIEVE* RETRIEVE::MatchMo(std::vector<std::string>* vedata) {

	//非空判断
	if ((sourcetext == NULL) || (purpose == NULL)) {
		printf("匹配参数未设置");
		return NULL;
	}
	std::string temp = *sourcetext;

	//循环匹配
	while (std::regex_search(temp, *match, *purpose)) {

		//处理匹配文本
		vedata->push_back(match[0].str());
		temp = match->suffix().str();
	}
	return this;
}


//单个匹配，
RETRIEVE* RETRIEVE::MatchMo(std::string* data, int index) {
	//非空判断
	if ((sourcetext == NULL) || (purpose == NULL)) {
		printf("匹配参数未设置");
		return NULL;
	}

	

	//循环匹配
	int flag = std::regex_search(*sourcetext, *match, *purpose);

	if (!flag) {
		printf("未找到匹配项");
		return NULL;
	}
	if ((data != NULL) && (!data->empty())) data->clear();
		//处理匹配文本
		data->append((*match)[index].str());
		

	return this;
}