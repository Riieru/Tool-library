#pragma once
#include<filesystem>
//�ļ����ܼ�ǿ

class Riieru_FILEEX {
	//������
private:
	Riieru_FILEEX() = default;
	~Riieru_FILEEX() = default;
public:
	//����ָ��Ŀ¼���Ƿ������Ҫ���ļ�
	static int ForEachFile(std::filesystem::path* fp,const std::string* exstr);
};