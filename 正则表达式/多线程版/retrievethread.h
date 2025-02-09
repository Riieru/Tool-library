#include"Rthreadpool.h"
#include<iostream>
#include<regex>

namespace RIIERURETRIEVE {


		


	//返回数据项
	struct RESULTDATA {
		//判断是否是循环匹配
		//0:仅匹配一次
		//1:循环匹配
		bool resultFlag;

		//数据 
		std::vector<std::vector<std::string>> data_ALL;

	};

	//匹配结构体
	struct RETRIEVEDATA
	{

		RETRIEVEDATA(std::string purpose,
			         std::string sourcetext,
			         bool matchflag = false, 
			         std::regex_constants::syntax_option_type Flags = std::regex_constants::ECMAScript);

		//匹配进度标识符
		bool matchFlag;

		//目标文本(需要被匹配的原始数据)
		std::string purpose;

		//匹配项(正则表达式)
	    std::string sourcetext;
		//匹配项（行为控制选项）
		std::regex_constants::syntax_option_type Flags;


		//返回数据项
		RESULTDATA data;
	};








	//正则表达式-多线程
	class RetrieveThread {

	private:
		//线程池
		std::shared_ptr<RIIERUTHREAD::RThreadmanage> threadpool;
 

	public:
		RetrieveThread(unsigned short threadsize = 2);
		~RetrieveThread();

	private:
		//参数初始化
		bool InitializeRetrieveData(RETRIEVEDATA& retrievedata);
	public:
		//添加匹配项 --- 默认单次匹配
		bool AddPject(RETRIEVEDATA& retrievedata);

		//执行正则表达式匹配
		bool MatchText(RETRIEVEDATA& retrievedata);

	};


}