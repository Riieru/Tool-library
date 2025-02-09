#include"head.h"

ICUMAIN::ICUMAIN() {
	SetICUBuffer();
}
ICUMAIN::~ICUMAIN() {
	delete(destination);
	ucnv_close(ICUpurpose);
}



//����ICU�����ַ���
ICUMAIN* ICUMAIN::SetICUBuffer(int buffersize) {
	if (destination != NULL) {
		delete(destination);
		destination = NULL;
	}

	destination = new char[buffersize];
	destination[buffersize - 1] = '\0';
	destinationlength = buffersize - 1;
	return this;
}

//����ICU�ַ�ת���� ת��ǰ��ԭʼ����
ICUMAIN* ICUMAIN::SetConverter(std::string&& mode) {
	if (ICUpurpose != NULL) {
		ucnv_close(ICUpurpose);
	}
      	ICUpurpose = ucnv_open(mode.c_str(), &errorCode);
	return this;
}


//ICU����ת��     ��������Ҫת�����ַ���    ||    ת�����ŵ�����
ICUMAIN* ICUMAIN::CdConversion(UConverterType salgorithmicType, std::string&& source, std::string&& purpose) {

	//Դ�ַ����ָ��
	int mark = 0;
	//�ָ��ַ�������
	int marklength = destinationlength;
	char* tempstring = const_cast<char*>(source.c_str());

	//����ת��ʵ�ʳ���
	int converterlength;

	//���ж���Ҫת�����ַ����Ƿ񳬹���������С
	while (true) {

		//��Ҫ�ָ�ѭ��ִ��
		if (source.length() - mark > destinationlength) {
			converterlength = ucnv_toAlgorithmic(salgorithmicType, ICUpurpose, destination, destinationlength, tempstring, marklength, &errorCode);
			mark += destinationlength;
			tempstring += marklength;

			purpose.append(destination, converterlength);
		}
		else {
			converterlength = ucnv_toAlgorithmic(salgorithmicType, ICUpurpose, destination, destinationlength, tempstring, source.length() - mark, &errorCode);

			purpose.append(destination, converterlength);
			break;
		}
	}


	return this;

}