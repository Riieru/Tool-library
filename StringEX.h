#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
#include<utility>



class String_EX_Riieru {
private:
	//���յ��ַ���������
	const std::string* Str_R = NULL;
	std::vector<std::string*>* Stvr_R = NULL;
	//�����ַ������������
	const std::string** Str_pointers = NULL;
	int Str_pointers_length = 0;

public:
	//����Ŀ���ַ���������
	String_EX_Riieru(const std::string* str, std::vector<std::string*>* stvr);
	//�����ַ�������ָ�������
	String_EX_Riieru(const std::string** str_pointers, const int length);
	~String_EX_Riieru();

	//�и��ַ���  �������ַ����и� 
	void Split(const std::string* notation);
	//�и��ַ���  �������ַ��������и�
	void Split(const int length);
	

	//�����ַ�������
	static void StrPrint(const std::string** str_pointers, const int length);

	//�����ַ�������Ҫ������
	static void StrCopy(const std::string** str_pointers,int length, std::vector<std::string*>* str_v);

	////���ַ���·������
	//static void FixTail(std::string* str);
	
	//ת�����ַ�
	static void StrToWstr(const std::string&& temp_str,wchar_t* a);


};

