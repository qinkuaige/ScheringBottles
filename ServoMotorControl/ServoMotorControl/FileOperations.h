#pragma once
#include <stdio.h>

class FileOperations
{
public:
	static FileOperations* getInstance(const char* file_name = "UserInformation");
private:
	FileOperations(const char* file_name);
	~FileOperations();

	static FileOperations* instance;

private:
	FILE* m_file;
};

FileOperations* FileOperations::instance = NULL;