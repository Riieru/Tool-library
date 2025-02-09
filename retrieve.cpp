#include"head.h"

//��ʼ��

RETRIEVE::RETRIEVE() {
	match = new std::smatch;
}
RETRIEVE::RETRIEVE(std::string* fsourcetext, std::string* fpurposetext) : sourcetext(fsourcetext){
	match = new std::smatch;
	SetPurpose(fpurposetext);
}

RETRIEVE::~RETRIEVE() {
	if (match != NULL) delete(match);
	if (purpose != NULL) delete(purpose);
}



//Set
RETRIEVE* RETRIEVE::SetSource(std::string* fsourcetext) {
	sourcetext = fsourcetext;
	return this;
}

RETRIEVE* RETRIEVE::SetPurpose(std::string* fpurposetext, std::regex_constants::syntax_option_type Flags) {
	if (purpose != NULL) {
		delete(purpose);
		purpose = NULL;
	}

	purpose = new std::regex(*fpurposetext, Flags);
	return this;
}

RETRIEVE* RETRIEVE::SetTextAll(std::string* fsourcetext, std::string* fpurposetext) {
	sourcetext = fsourcetext;
	SetPurpose(fpurposetext);
	return this;
}


//����ƥ�䣬��ʹ�ô��ݽ����������洢ƥ�������
RETRIEVE* RETRIEVE::MatchMo(std::vector<std::string>* vedata) {

	//�ǿ��ж�
	if ((sourcetext == NULL) || (purpose == NULL)) {
		printf("ƥ�����δ����");
		return NULL;
	}
	std::string temp = *sourcetext;

	//ѭ��ƥ��
	while (std::regex_search(temp, *match, *purpose)) {

		//����ƥ���ı�
		vedata->push_back(match[0].str());
		temp = match->suffix().str();
	}
	return this;
}


//����ƥ�䣬
RETRIEVE* RETRIEVE::MatchMo(std::string* data, int index) {
	//�ǿ��ж�
	if ((sourcetext == NULL) || (purpose == NULL)) {
		printf("ƥ�����δ����");
		return NULL;
	}

	

	//ѭ��ƥ��
	int flag = std::regex_search(*sourcetext, *match, *purpose);

	if (!flag) {
		printf("δ�ҵ�ƥ����");
		return NULL;
	}
	if ((data != NULL) && (!data->empty())) data->clear();
		//����ƥ���ı�
		data->append((*match)[index].str());
		

	return this;
}