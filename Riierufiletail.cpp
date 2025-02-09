
#include"Riierufiletail.h"

//遍历指定目录中是否存在需要的文件
int Riieru_FILEEX::ForEachFile(std::filesystem::path* fp, const std::string* exstr) {
    //遍历
    std::filesystem::recursive_directory_iterator aqw(*fp);
    for (auto w : aqw) {
        if (w.path().string().find(*exstr) != exstr->npos) {
            *fp = w.path();
            return 1;
        }
    }
    return 0;
}