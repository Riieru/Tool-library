#include"head.h"

ICUMAIN::ICUMAIN() {
	SetICUBuffer();
}
ICUMAIN::~ICUMAIN() {
	delete(destination);
	ucnv_close(ICUpurpose);
}



//设置ICU缓冲字符串
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

//设置ICU字符转换器 转换前的原始类型
ICUMAIN* ICUMAIN::SetConverter(std::string&& mode) {
	if (ICUpurpose != NULL) {
		ucnv_close(ICUpurpose);
	}
      	ICUpurpose = ucnv_open(mode.c_str(), &errorCode);
	return this;
}


//ICU编码转换     参数：需要转换的字符串    ||    转换后存放的容器
ICUMAIN* ICUMAIN::CdConversion(UConverterType salgorithmicType, std::string&& source, std::string&& purpose) {

	//源字符串分割点
	int mark = 0;
	//分割字符串长度
	int marklength = destinationlength;
	char* tempstring = const_cast<char*>(source.c_str());

	//编码转换实际长度
	int converterlength;

	//先判断需要转换的字符串是否超过缓冲区大小
	while (true) {

		//需要分割循环执行
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