#pragma once

#include"head.h"

class RIIERU_FILEIO {
	//���ж������
private:
	//һ���ļ�
	FILE* firstfile = NULL;

	//��������
	std::string* fcontainers = NULL;


	//������
	char* ftemp = NULL;
	//��������С
	int ftempsize = NULL;

	//�ļ���С
	int filesize = 0;

public:
	//��ʼ��
	RIIERU_FILEIO(int size = 1024);
	//��ʼ���ļ�
	RIIERU_FILEIO(std::string&& fpath, const char* mode, int size = 1024);
	~RIIERU_FILEIO();

public:

	//�����ļ�
	RIIERU_FILEIO* SetFile(std::string fpath, const char* mode);
	//�����ڴ潻������
	RIIERU_FILEIO* SetContainers(std::string* containers);
	//���û�������С
	void initialize(int size = 1024);

public:

	//�ƶ��ļ���ָ�뵽ѡ��λ�� Ĭ��ƫ�Ƴ���Ϊ0
	int Move(int coordinate, long size = 0);
	//���ļ�
	RIIERU_FILEIO* Read(std::string* containers = NULL);
	//д�ļ�
	RIIERU_FILEIO* Write(std::string* containers = NULL);
	//д�ļ�
	RIIERU_FILEIO* Write(const char* data, int size);
	//��ȡ�ļ���С
	int GetFileSize();

};