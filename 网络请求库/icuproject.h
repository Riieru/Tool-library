#pragma once
#include"head.h"


class ICUMAIN {

private:

	//ICU
	UErrorCode errorCode = U_ZERO_ERROR;
	//字符转换器
	UConverter* ICUpurpose = NULL;
	//缓冲输入字符串
	char* destination = NULL;
	int destinationlength = 0;

public:
	ICUMAIN();
	~ICUMAIN();

public:
	//设置ICU缓冲字符串
	ICUMAIN* SetICUBuffer(int buffersize = 1024);

	//设置ICU字符转换器
	ICUMAIN* SetConverter(std::string&& mode);

	//ICU编码转换     参数：需要转换的字符串    ||    转换后存放的容器
	ICUMAIN* CdConversion(UConverterType salgorithmicType, std::string&& source, std::string&& purpose);





};