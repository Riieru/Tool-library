#include"head.h"



//初始化
RIIERU_FILEIO::RIIERU_FILEIO(int size ) {
	initialize(size);
}
//初始化文件
RIIERU_FILEIO::RIIERU_FILEIO(std::string&& fpath,const char* mode, int size ) {
	initialize(size);
	firstfile = fopen(fpath.c_str(), mode);
}

//析构
RIIERU_FILEIO::~RIIERU_FILEIO() {
	    if(firstfile != NULL) fclose(firstfile);
		if (ftemp != NULL) delete(ftemp);
		ftemp = NULL;
}


//传递文件
RIIERU_FILEIO* RIIERU_FILEIO::SetFile(std::string fpath, const char* mode) {
	if (firstfile != NULL) fclose(firstfile);

	firstfile = fopen(fpath.c_str(), mode);
	return this;
}

//传递内存交互容器
RIIERU_FILEIO* RIIERU_FILEIO::SetContainers(std::string* containers) {
	fcontainers = containers;
	return this;
}

//设置缓冲区大小
void RIIERU_FILEIO::initialize(int size ) {
	if (ftemp != NULL) {
		delete(ftemp);
		ftemp = NULL;
	}
	ftemp = new char[size];
	ftempsize = size;
}


//获取文件大小
int RIIERU_FILEIO::GetFileSize() {
	if (firstfile == NULL) {
		printf("当前类中未定义文件流,位于RIIERU_FILEIO中");
		return NULL;
	}
	if (filesize == 0) {
		//获取文件大小
		filesize = Move(SEEK_END);
	}
	Move(SEEK_SET);
	return filesize;
}

//移动文件流指针到选定位置 默认偏移长度为0
int RIIERU_FILEIO::Move(int coordinate , long size) {
	if (fseek(firstfile, size, coordinate) == 0) {
		printf("文件指针偏移错误，位于RIIERU_FILEIO中");
		return NULL;
	}
	return ftell(firstfile);
}

//读文件 从头开始读 可选参数：数据加载进选定容器
RIIERU_FILEIO* RIIERU_FILEIO::Read(std::string* containers ) {
	//可行性判断
	if (firstfile == NULL) return NULL;
	//定义读取字节数
	int readsize = 0;
	int readcount = 0;
	//指针设置为开始处
	Move(SEEK_SET);

	//如果未设置任何容器
	if (containers == NULL && fcontainers == NULL) {
		printf("\n");
		//循环读取文件
		while ((readsize = fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//读取字节数
			printf("文件读取中...  当前进度：( %d / %d )\r", readcount += readsize, filesize);
		}
	}

	//如果设置容器，优先指定容器
	if (containers) {
		printf("\n");
		//循环读取文件
		while ((readsize += fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//读取字节数
			printf("文件读取中...  当前进度：( %d / %d )\r", readcount += readsize, filesize);
			//写入容器
			containers->append(ftemp, readsize);
		}
	}
	else if ((containers == NULL) && (fcontainers)) {
		printf("\n");
		//循环读取文件
		while ((readsize += fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//读取字节数
			printf("文件读取中...  当前进度：( %d / %d )\r", readcount += readsize, filesize);
			//写入容器
			fcontainers->append(ftemp, readsize);
		}
	}

	if (feof(firstfile)) printf("\n文件读取完毕\n");

	


}


//写文件
RIIERU_FILEIO* RIIERU_FILEIO::Write(std::string* containers ) {
	//可行性判断
	if (firstfile == NULL) return NULL;
	//定义写入字节数
	int readsize = 0;
	int writesize = ftempsize;

	//截取指定数量字符串
	int subsize = 0;


	//如果未设置任何容器
	if (containers == NULL && fcontainers == NULL) {
		printf("未设置需要写入的数据");
		return NULL;
	}

	//如果设置容器，优先指定容器
	if (containers) {
		printf("\n");
		//先写入缓存
		//循环写入文件
       while (true) {
		   std::string tempstr = containers->substr(subsize, ftempsize);
		   const char* temp = tempstr.c_str();
			//判断截取的字符串是否到末尾
			if ((subsize + ftempsize) > containers->size()) {
				//当前数量不足填满缓冲区
				writesize = containers->size() - subsize;
			}
				subsize += ftempsize;
			readsize += fwrite(temp, sizeof(char), writesize, firstfile);
			//写入字节数
			printf("文件写入中...  当前进度：( %d / %d )\r", readsize, containers->size());
			if (subsize >= containers->length()) break;
		}
	}
	else if ((containers == NULL) && (fcontainers)) {
		printf("\n");
		//先写入缓存
		//循环写入文件
		while (true) {
			std::string tempstr = containers->substr(subsize, ftempsize);
			const char* temp = tempstr.c_str();
			//判断截取的字符串是否到末尾
			if ((subsize + ftempsize) > fcontainers->size()) {
				//当前数量不足填满缓冲区
				writesize = fcontainers->size() - subsize;
			}
			subsize += ftempsize;
			readsize += fwrite(temp, sizeof(char), writesize, firstfile);
			//写入字节数
			printf("文件写入中...  当前进度：( %d / %d )\r", readsize, fcontainers->size());
			if (subsize >= fcontainers->length()) break;
		}
	}
	 printf("\n文件写入完毕\n");
}


//写文件
RIIERU_FILEIO* RIIERU_FILEIO::Write(const char* data,int size) {
	//可行性判断
	if (firstfile == NULL) return NULL;
	if (data == NULL || size == 0) return NULL;

	printf("\n");

        fwrite(data, sizeof(char), size, firstfile);

	
}



