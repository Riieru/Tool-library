#pragma once

#include"head.h"

class RIIERU_FILEIO {
	//可有多个对象
private:
	//一号文件
	FILE* firstfile = NULL;

	//交互容器
	std::string* fcontainers = NULL;


	//缓冲区
	char* ftemp = NULL;
	//缓冲区大小
	int ftempsize = NULL;

	//文件大小
	int filesize = 0;

public:
	//初始化
	RIIERU_FILEIO(int size = 1024);
	//初始化文件
	RIIERU_FILEIO(std::string&& fpath, const char* mode, int size = 1024);
	~RIIERU_FILEIO();

public:

	//传递文件
	RIIERU_FILEIO* SetFile(std::string fpath, const char* mode);
	//传递内存交互容器
	RIIERU_FILEIO* SetContainers(std::string* containers);
	//设置缓冲区大小
	void initialize(int size = 1024);

public:

	//移动文件流指针到选定位置 默认偏移长度为0
	int Move(int coordinate, long size = 0);
	//读文件
	RIIERU_FILEIO* Read(std::string* containers = NULL);
	//写文件
	RIIERU_FILEIO* Write(std::string* containers = NULL);
	//写文件
	RIIERU_FILEIO* Write(const char* data, int size);
	//获取文件大小
	int GetFileSize();

};