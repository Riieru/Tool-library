#pragma once
#include"head.h"

//������ʽƥ��

class RETRIEVE {

private:
	//ƥ���ı� --- Դ
	std::string* sourcetext = NULL;

	//ƥ���ʶ������  --- Ŀ��
	std::regex* purpose = NULL;
	std::smatch* match = NULL;

public:
	RETRIEVE();
	RETRIEVE(std::string* fsourcetext, std::string* fpurposetext);

	~RETRIEVE();

public:
	//Set
	RETRIEVE* SetSource(std::string* fsourcetext);


	RETRIEVE* SetPurpose(std::string* fpurposetext, std::regex_constants::syntax_option_type Flags = std::regex_constants::ECMAScript);

	RETRIEVE* SetTextAll(std::string* fsourcetext, std::string* fpurposetext);

public:
	//����

	//����ƥ�䣬��ʹ�ô��ݽ����������洢ƥ�������
	RETRIEVE* MatchMo(std::vector<std::string>* vedata);

	//����ƥ�䣬
	RETRIEVE* MatchMo(std::string* data,int index = 0);

};


