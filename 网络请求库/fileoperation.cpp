#include"head.h"



//��ʼ��
RIIERU_FILEIO::RIIERU_FILEIO(int size ) {
	initialize(size);
}
//��ʼ���ļ�
RIIERU_FILEIO::RIIERU_FILEIO(std::string&& fpath,const char* mode, int size ) {
	initialize(size);
	firstfile = fopen(fpath.c_str(), mode);
}

//����
RIIERU_FILEIO::~RIIERU_FILEIO() {
	    if(firstfile != NULL) fclose(firstfile);
		if (ftemp != NULL) delete(ftemp);
		ftemp = NULL;
}


//�����ļ�
RIIERU_FILEIO* RIIERU_FILEIO::SetFile(std::string fpath, const char* mode) {
	if (firstfile != NULL) fclose(firstfile);

	firstfile = fopen(fpath.c_str(), mode);
	return this;
}

//�����ڴ潻������
RIIERU_FILEIO* RIIERU_FILEIO::SetContainers(std::string* containers) {
	fcontainers = containers;
	return this;
}

//���û�������С
void RIIERU_FILEIO::initialize(int size ) {
	if (ftemp != NULL) {
		delete(ftemp);
		ftemp = NULL;
	}
	ftemp = new char[size];
	ftempsize = size;
}


//��ȡ�ļ���С
int RIIERU_FILEIO::GetFileSize() {
	if (firstfile == NULL) {
		printf("��ǰ����δ�����ļ���,λ��RIIERU_FILEIO��");
		return NULL;
	}
	if (filesize == 0) {
		//��ȡ�ļ���С
		filesize = Move(SEEK_END);
	}
	Move(SEEK_SET);
	return filesize;
}

//�ƶ��ļ���ָ�뵽ѡ��λ�� Ĭ��ƫ�Ƴ���Ϊ0
int RIIERU_FILEIO::Move(int coordinate , long size) {
	if (fseek(firstfile, size, coordinate) == 0) {
		printf("�ļ�ָ��ƫ�ƴ���λ��RIIERU_FILEIO��");
		return NULL;
	}
	return ftell(firstfile);
}

//���ļ� ��ͷ��ʼ�� ��ѡ���������ݼ��ؽ�ѡ������
RIIERU_FILEIO* RIIERU_FILEIO::Read(std::string* containers ) {
	//�������ж�
	if (firstfile == NULL) return NULL;
	//�����ȡ�ֽ���
	int readsize = 0;
	int readcount = 0;
	//ָ������Ϊ��ʼ��
	Move(SEEK_SET);

	//���δ�����κ�����
	if (containers == NULL && fcontainers == NULL) {
		printf("\n");
		//ѭ����ȡ�ļ�
		while ((readsize = fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//��ȡ�ֽ���
			printf("�ļ���ȡ��...  ��ǰ���ȣ�( %d / %d )\r", readcount += readsize, filesize);
		}
	}

	//�����������������ָ������
	if (containers) {
		printf("\n");
		//ѭ����ȡ�ļ�
		while ((readsize += fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//��ȡ�ֽ���
			printf("�ļ���ȡ��...  ��ǰ���ȣ�( %d / %d )\r", readcount += readsize, filesize);
			//д������
			containers->append(ftemp, readsize);
		}
	}
	else if ((containers == NULL) && (fcontainers)) {
		printf("\n");
		//ѭ����ȡ�ļ�
		while ((readsize += fread(ftemp, sizeof(char), ftempsize, firstfile)) != 0) {
			//��ȡ�ֽ���
			printf("�ļ���ȡ��...  ��ǰ���ȣ�( %d / %d )\r", readcount += readsize, filesize);
			//д������
			fcontainers->append(ftemp, readsize);
		}
	}

	if (feof(firstfile)) printf("\n�ļ���ȡ���\n");

	


}


//д�ļ�
RIIERU_FILEIO* RIIERU_FILEIO::Write(std::string* containers ) {
	//�������ж�
	if (firstfile == NULL) return NULL;
	//����д���ֽ���
	int readsize = 0;
	int writesize = ftempsize;

	//��ȡָ�������ַ���
	int subsize = 0;


	//���δ�����κ�����
	if (containers == NULL && fcontainers == NULL) {
		printf("δ������Ҫд�������");
		return NULL;
	}

	//�����������������ָ������
	if (containers) {
		printf("\n");
		//��д�뻺��
		//ѭ��д���ļ�
       while (true) {
		   std::string tempstr = containers->substr(subsize, ftempsize);
		   const char* temp = tempstr.c_str();
			//�жϽ�ȡ���ַ����Ƿ�ĩβ
			if ((subsize + ftempsize) > containers->size()) {
				//��ǰ������������������
				writesize = containers->size() - subsize;
			}
				subsize += ftempsize;
			readsize += fwrite(temp, sizeof(char), writesize, firstfile);
			//д���ֽ���
			printf("�ļ�д����...  ��ǰ���ȣ�( %d / %d )\r", readsize, containers->size());
			if (subsize >= containers->length()) break;
		}
	}
	else if ((containers == NULL) && (fcontainers)) {
		printf("\n");
		//��д�뻺��
		//ѭ��д���ļ�
		while (true) {
			std::string tempstr = containers->substr(subsize, ftempsize);
			const char* temp = tempstr.c_str();
			//�жϽ�ȡ���ַ����Ƿ�ĩβ
			if ((subsize + ftempsize) > fcontainers->size()) {
				//��ǰ������������������
				writesize = fcontainers->size() - subsize;
			}
			subsize += ftempsize;
			readsize += fwrite(temp, sizeof(char), writesize, firstfile);
			//д���ֽ���
			printf("�ļ�д����...  ��ǰ���ȣ�( %d / %d )\r", readsize, fcontainers->size());
			if (subsize >= fcontainers->length()) break;
		}
	}
	 printf("\n�ļ�д�����\n");
}


//д�ļ�
RIIERU_FILEIO* RIIERU_FILEIO::Write(const char* data,int size) {
	//�������ж�
	if (firstfile == NULL) return NULL;
	if (data == NULL || size == 0) return NULL;

	printf("\n");

        fwrite(data, sizeof(char), size, firstfile);

	
}



