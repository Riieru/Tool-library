
#include"Riierufiletail.h"

//����ָ��Ŀ¼���Ƿ������Ҫ���ļ�
int Riieru_FILEEX::ForEachFile(std::filesystem::path* fp, const std::string* exstr) {
    //����
    std::filesystem::recursive_directory_iterator aqw(*fp);
    for (auto w : aqw) {
        if (w.path().string().find(*exstr) != exstr->npos) {
            *fp = w.path();
            return 1;
        }
    }
    return 0;
}