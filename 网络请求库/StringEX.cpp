
#include"StringEX.h"
//����
String_EX_Riieru::String_EX_Riieru(const std::string* str, std::vector<std::string*>* stvr) :Str_R(str), Stvr_R(stvr){}
//�����ַ�������ָ�������
String_EX_Riieru::String_EX_Riieru(const std::string** str_pointers, const int length):Str_pointers(str_pointers),Str_pointers_length(length){}
String_EX_Riieru::~String_EX_Riieru() {
	if (Str_R != NULL) Str_R = NULL;
	if (Stvr_R != NULL) Stvr_R = NULL;
	if (Str_pointers != NULL) Str_pointers = NULL;
}
		


//�ַ����и�
void String_EX_Riieru::Split(const std::string* notation) {
	
	int Str_begin = 0;
	int Str_index = 0;
	//����find�����ҵ���һ��ƥ����ŵ�����
	while (true)
	{		
			//ѭ�������ַ���,��ȡ��һ���и����
			Str_index = Str_R->find(*notation, Str_begin);
			if (Str_index == Str_R->npos) {
				//����ǰ�ַ�����������
				Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, Str_R->length() - Str_begin)));
				break;
			}
			//��ȡ��һ���ҵ����ַ���,����ӵ���Ҫ������
			Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, Str_index-Str_begin)));
			//�������ַ���
			Str_begin = Str_index + notation->length();
			if (Str_begin >= Str_R->length() - 1) break;
		}
}


void String_EX_Riieru::Split(const int length) {
	int Str_begin = 0;
	int Str_index = 0;
	//��ȡ�������ȵ��ַ���
	while (true)
	{
		if (Str_R->length() - length <= 0) break;
		Stvr_R->push_back(new std::string(Str_R->substr(Str_begin, length)));
		//�����ַ���λ��
		Str_begin += length;
		if (Str_begin >= Str_R->length() - 1) break;
	}
}


//�����ַ�������
void String_EX_Riieru::StrPrint(const std::string** str_pointers, const int length) {
	for (size_t i = 0; i < length; i++)
	{
		//��ӡÿ���ַ���
		std::printf((*(str_pointers[i])).c_str());
	}
}

//�����ַ�������Ҫ������
void String_EX_Riieru::StrCopy(const std::string** str_pointers, int length, std::vector<std::string*>* str_v) {
	if (str_v->size() != 0) return;
	for (size_t i = 0; i < length; i++)
	{
	str_v->push_back(new std::string(*(str_pointers[i])));
	}
}

//ת�����ַ�
void String_EX_Riieru::StrToWstr(const std::string&& temp_str, wchar_t* str_tp) {
	int count = MultiByteToWideChar(CP_ACP, 0, temp_str.c_str(), temp_str.size(), str_tp, temp_str.size() * sizeof(wchar_t) + 1);
	str_tp[count] = '\0';
}

////���ַ���·������
//static void FixTail(std::string* str) {
//	if (str == NULL) return;
//	//��ʼ������
//	int index_begin = 0;
//	std::string str_temp("\\");
//	while (true)
//	{
//		index_begin = str->find(str_temp, index_begin);
//		if (index_begin == str->npos) break;
//		//�滻
//		str->at(index_begin) = '/';
//	}
//}