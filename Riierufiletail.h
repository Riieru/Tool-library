#pragma once
#include<filesystem>
//文件功能加强

class Riieru_FILEEX {
	//工具类
private:
	Riieru_FILEEX() = default;
	~Riieru_FILEEX() = default;
public:
	//遍历指定目录中是否存在需要的文件
	static int ForEachFile(std::filesystem::path* fp,const std::string* exstr);
};