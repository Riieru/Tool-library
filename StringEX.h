#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
#include<utility>



class String_EX_Riieru {
private:
	//接收的字符串和容器
	const std::string* Str_R = NULL;
	std::vector<std::string*>* Stvr_R = NULL;
	//接收字符串数组和索引
	const std::string** Str_pointers = NULL;
	int Str_pointers_length = 0;

public:
	//接收目标字符串和容器
	String_EX_Riieru(const std::string* str, std::vector<std::string*>* stvr);
	//接收字符串数组指针和索引
	String_EX_Riieru(const std::string** str_pointers, const int length);
	~String_EX_Riieru();

	//切割字符串  按给定字符串切割 
	void Split(const std::string* notation);
	//切割字符串  按给定字符串长度切割
	void Split(const int length);
	

	//遍历字符串数组
	static void StrPrint(const std::string** str_pointers, const int length);

	//拷贝字符串至需要的容器
	static void StrCopy(const std::string** str_pointers,int length, std::vector<std::string*>* str_v);

	////将字符串路径修正
	//static void FixTail(std::string* str);
	
	//转换宽字符
	static void StrToWstr(const std::string&& temp_str,wchar_t* a);


};

