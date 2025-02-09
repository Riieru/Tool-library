
#include"StringEX.h"
//构造
String_EX_Riieru::String_EX_Riieru(const std::string* str, std::vector<std::string*>* stvr) :Str_R(str), Stvr_R(stvr){}
//接收字符串数组指针和索引
String_EX_Riieru::String_EX_Riieru(const std::string** str_pointers, const int length):Str_pointers(str_pointers),Str_pointers_length(length){}
String_EX_Riieru::~String_EX_Riieru() {
	if (Str_R != NULL) Str_R = NULL;
	if (Stvr_R != NULL) Stvr_R = NULL;
	if (Str_pointers != NULL) Str_pointers = NULL;
}
		


//字符串切割
void String_EX_Riieru::Split(const std::string* notation) {
	
	int Str_begin = 0;
	int Str_index = 0;
	//先用find方法找到第一个匹配符号的索引
	while (true)
	{		
			//循环遍历字符串,获取第一个切割处索引
			Str_index = Str_R->find(*notation, Str_begin);
			if (Str_index == Str_R->npos) {
				//将当前字符串传给容器
				Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, Str_R->length() - Str_begin)));
				break;
			}
			//获取第一个找到的字符串,并添加到需要的容器
			Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, Str_index-Str_begin)));
			//更新新字符串
			Str_begin = Str_index + notation->length();
			if (Str_begin >= Str_R->length() - 1) break;
		}
}


void String_EX_Riieru::Split(const int length) {
	int Str_begin = 0;
	int Str_index = 0;
	//获取给定长度的字符串
	while (true)
	{
		if (Str_R->length() - length <= 0) break;
		Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, length)));
		//更新字符串位置
		Str_begin += length;
		if (Str_begin >= Str_R->length() - 1) break;
	}
}


//遍历字符串数组
void String_EX_Riieru::StrPrint(const std::string** str_pointers, const int length) {
	for (size_t i = 0; i < length; i++)
	{
		//打印每个字符串
		std::printf((*(str_pointers[i])).c_str());
	}
}

//拷贝字符串至需要的容器
void String_EX_Riieru::StrCopy(const std::string** str_pointers, int length, std::vector<std::string*>* str_v) {
	if (str_v->size() != 0) return;
	for (size_t i = 0; i < length; i++)
	{
	str_v->push_back(new std::string(*(str_pointers[i])));
	}
}

//转换宽字符
void String_EX_Riieru::StrToWstr(const std::string&& temp_str, wchar_t* str_tp) {
	int count = MultiByteToWideChar(CP_ACP, 0, temp_str.c_str(), temp_str.size(), str_tp, temp_str.size() * sizeof(wchar_t) + 1);
	str_tp[count] = '\0';
}

////将字符串路径修正
//static void FixTail(std::string* str) {
//	if (str == NULL) return;
//	//初始化索引
//	int index_begin = 0;
//	std::string str_temp("\\");
//	while (true)
//	{
//		index_begin = str->find(str_temp, index_begin);
//		if (index_begin == str->npos) break;
//		//替换
//		str->at(index_begin) = '/';
//	}
//}