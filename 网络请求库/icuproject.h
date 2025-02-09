#pragma once
#include"head.h"


class ICUMAIN {

private:

	//ICU
	UErrorCode errorCode = U_ZERO_ERROR;
	//�ַ�ת����
	UConverter* ICUpurpose = NULL;
	//���������ַ���
	char* destination = NULL;
	int destinationlength = 0;

public:
	ICUMAIN();
	~ICUMAIN();

public:
	//����ICU�����ַ���
	ICUMAIN* SetICUBuffer(int buffersize = 1024);

	//����ICU�ַ�ת����
	ICUMAIN* SetConverter(std::string&& mode);

	//ICU����ת��     ��������Ҫת�����ַ���    ||    ת�����ŵ�����
	ICUMAIN* CdConversion(UConverterType salgorithmicType, std::string&& source, std::string&& purpose);





};