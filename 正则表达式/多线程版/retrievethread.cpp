#include"retrievethread.h"

//数据体初始化
RIIERURETRIEVE::RETRIEVEDATA::RETRIEVEDATA(
	std::string p_purpose,
	std::string p_sourcetext,
	bool p_matchflag,
	std::regex_constants::syntax_option_type p_Flags) 
	:
	matchFlag{ p_matchflag },
	purpose{ p_purpose },
	sourcetext{ p_sourcetext },
	Flags{ p_Flags } {}



RIIERURETRIEVE::RetrieveThread::RetrieveThread(unsigned short threadsize) : 
	threadpool{std::make_shared<RIIERUTHREAD::RThreadmanage>(threadsize)} 
{

}
RIIERURETRIEVE::RetrieveThread::~RetrieveThread() {

}

//参数初始化
bool RIIERURETRIEVE::RetrieveThread::InitializeRetrieveData(RETRIEVEDATA& retrievedata) {

	retrievedata.matchFlag = false;
	//参数可行性判断
	if (
		retrievedata.purpose.empty() ||
		retrievedata.sourcetext.empty()
		)
	{
		return false;
	}
	return true;
}


//添加匹配项
bool RIIERURETRIEVE::RetrieveThread::AddPject(RETRIEVEDATA& retrievedata) {
	//匹配数据初始化
	if (!InitializeRetrieveData(retrievedata)) return false;
	//向线程池提交任务
	 threadpool->commitobj(&RIIERURETRIEVE::RetrieveThread::MatchText, this, retrievedata);
	return true;
}



//执行正则表达式匹配
bool RIIERURETRIEVE::RetrieveThread::MatchText(RETRIEVEDATA& retrievedata) {

	std::smatch match;
	//表达式
	std::regex regextext(retrievedata.sourcetext, retrievedata.Flags);
	//匹配文本
	if (retrievedata.data.resultFlag) {
		std::string t_purpose = retrievedata.purpose;
		while (std::regex_search(t_purpose, match, regextext)) {
			if (match[0].str().empty()) return false;
			//添加匹配结果
			retrievedata.data.data_ALL.emplace_back(std::vector<std::string>());
			for (auto matchelm : match)
			{
				retrievedata.data.data_ALL.back().emplace_back(matchelm.str());	
			}
			//重新初始化
			 t_purpose = match.suffix().str();
			match = std::smatch{};
			
		}
	}
	else {
		int flag = std::regex_search(retrievedata.purpose, match, regextext);
		if (match[0].str().empty()) return false;
		if (!flag) {
			printf("未找到匹配项");
			return false;
		}
		//添加匹配结果
		retrievedata.data.data_ALL.emplace_back(std::vector<std::string>());
		for (auto matchelm : match)
		{
			retrievedata.data.data_ALL.back().emplace_back(matchelm.str());
		}
	}

	retrievedata.matchFlag = true;
	return 1;
}