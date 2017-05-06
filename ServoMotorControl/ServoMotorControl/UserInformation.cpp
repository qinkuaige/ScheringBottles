#include "stdafx.h"
#include "UserInformation.h"
#include "Encryption.h"

#include <string.h>
#include <afxpriv.h>

const  size_t Size = 128;


UserInformation::UserInformation() :m_file(NULL), m_user(NULL), m_fileName("UserInformation")
{
	m_allUser.clear();
}


UserInformation::~UserInformation()
{
	for (auto pItor = m_allUser.begin(); pItor != m_allUser.end(); pItor++)
	{
		delete  pItor->second;
		m_allUser.erase(pItor);
	}
	m_allUser.clear();

	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
	if (m_user != NULL)
	{
		m_user = NULL;
	}

}


UserInformation* UserInformation::getInstance()
{
	static UserInformation* instance;
	if (instance == NULL)
	{
		instance = new UserInformation;
		instance->init();
	}
	return instance;
}

void UserInformation::init()
{
	
	m_file = fopen(m_fileName, "a+");
	char str[128] = { 0 };
	char* buff = fgets(str, sizeof str, m_file);
	if(buff == NULL)
	{
		User* user = new User;
		char  str[20] = "root";
		user->name = str;
		Encryption::getInstance()->encryption(str);
		str[strlen(str)] = ',';
		fwrite(str, strlen(str), 1, m_file);

		memset(str, 0, sizeof str);
		strcpy(str, "zz2016");
		user->password = str;
		Encryption::getInstance()->encryption(str);
		str[strlen(str)] = ',';
		fwrite(str, strlen(str), 1, m_file);

		memset(str, 0, sizeof str);
		strcpy(str, Permissions[0]);
		user->permissions = str;
		Encryption::getInstance()->encryption(str);
		str[strlen(str)] = '\n';
		fwrite(str, strlen(str), 1, m_file);
		m_allUser[user->name] = user;

	}
	else
	{
		while(buff != NULL)
		{
			char s[32] = { 0 };
			int j = 0;
			int k = 0;
			User* user = NULL;
			for (size_t i = 0; k < 3; i++)
			{
				if (str[i] == ',' || str[i + 1] == '\0')
				{
					Encryption::getInstance()->decryption(s);
					switch (k)
					{
					case 0:
						user = new User;
						user->name = s;
						k++;
						i++;
						j = 0;
						memset(s, 0,sizeof s);
						break;
					case 1:
						user->password = s;
						k++;
						i++;
						j = 0;
						memset(s, 0, sizeof s);
						break;
					case 2:
						user->permissions = s;
						m_allUser[user->name] = user;
						i++;
						j = 0;
						k++;
						memset(s, 0, sizeof s);
						break;
					}

				}
				s[j] = str[i];
				j++;
			}
			memset(str, 0, sizeof str);
			buff = fgets(str, sizeof str, m_file);
		}
		
	}
}

UINT UserInformation::addUser(User* &user)
{
	if (user == NULL || user->name == _T(""))
	{
		return  1;
	}
	auto pItor = m_allUser.find(user->name);
	if (pItor != m_allUser.end())
	{
		delete  user;
		user = NULL;
		return  2;
	}
	if (m_user == NULL)
	{
		return 3;
	}
	if(get_level(m_user->permissions) <= get_level(user->permissions))
	{
		return 3;
	}

	m_allUser[user->name] = user;
	fseek(m_file, SEEK_END, 0);
	char str[32] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, user->name, -1, str, user->name.GetLength()*2, NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = ',';
	fwrite(str, strlen(str), 1, m_file);

	memset(str, 0, sizeof str);
	WideCharToMultiByte(CP_ACP, 0, user->password, -1, str, user->password.GetLength()*2, NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = ',';
	fwrite(str, strlen(str), 1, m_file);

	memset(str, 0, sizeof str);
	WideCharToMultiByte(CP_ACP, 0, user->permissions, -1, str, user->permissions.GetLength()*2, NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = '\n';
	fwrite(str, strlen(str), 1, m_file);
}

int UserInformation::deleteUser(CString user_name)
{
	auto pItor = m_allUser.find(user_name);
	if (pItor == m_allUser.end())
	{
		return 1;
	}
	
	if (get_level(pItor->second->permissions) >= get_level(m_user->permissions) )
	{
		return 2;
	}

	char str[Size] = { 0 };
	char* buff = new char[Size];
	memset(buff, 0, Size);
	userToChar(pItor->second, buff);
	
	fseek(m_file, SEEK_SET, 0);
	FILE *file = NULL;
	file = fopen("Excessive", "w");//写打开临时文件tmp.txt
	if (file == NULL)
	{
		return 3;
	}
	while (fgets(str, sizeof str, m_file))//从原文件读取一行
	{
		if (strcmp(buff,str))
		{
			fwrite(str, strlen(str), 1, file);
		}
		memset(str, 0, sizeof str);
	}
	
	fclose(file);
	fclose(m_file);
	remove(m_fileName);
	rename("Excessive", m_fileName);
	m_file = fopen(m_fileName, "a+");
	m_allUser.erase(pItor);
	delete[] buff;
	return 0;
}

int UserInformation::set_user(CString name)
{
	auto pItor = m_allUser.find(name);
	if (pItor == m_allUser.end())
	{
		return -1;
	}
	m_user = pItor->second;
	return 0;
}

bool UserInformation::verifyPassword(CString password)
{
	if (m_user == NULL)
	{
		return false;
	}
	if (password == m_user->password)
	{
		return true;
	}
	return false;
}

int UserInformation::get_level(const CString &permissions)
{
	char str[32] = {0};  
	size_t size = sizeof   Permissions / sizeof Permissions[0];
	WideCharToMultiByte(CP_ACP, 0, permissions, -1, str,permissions.GetLength()*2, NULL, NULL);
	for (size_t i = 0; i < size; i++)
	{
		if (0 == strcmp(str, Permissions[i]))
		{
			return size - i;
		}
	}
	return 0;
}

int UserInformation::changePassword(CString newPasword)
{
	char str[128] = { 0 };
	char* buff = new char[128];
	memset(buff, 0, Size);
	userToChar(m_user, buff);
	fseek(m_file, SEEK_SET, 0);
	FILE *file = NULL;
	file = fopen("Excessive", "w");//写打开临时文件tmp.txt
	if (file == NULL)
	{
		return -1;
	}
	while (fgets(str, sizeof str, m_file))//从原文件读取一行
	{
		if (strcmp(buff, str))
		{
			fwrite(str, strlen(str), 1, file);
		}
		else
		{
			m_user->password = newPasword;
			memset(buff, 0, 128);
			userToChar(m_user, buff);
			fwrite(buff, strlen(str), 1, file);
		}
		memset(str, 0, sizeof str);
	}

	fclose(file);
	fclose(m_file);
	remove(m_fileName);
	rename("Excessive", m_fileName);
	m_file = fopen(m_fileName, "a+");
	delete[] buff;
	return 0;
}

void UserInformation::userToChar(User* user, char* &buff)
{
	char str[32] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, user->name, -1, str, user->name.GetLength(), NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = ',';
	strcat(buff, str);

	memset(str, 0, sizeof str);
	WideCharToMultiByte(CP_ACP, 0, user->password, -1, str, user->password.GetLength(), NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = ',';
	strcat(buff, str);

	memset(str, 0, sizeof str);
	WideCharToMultiByte(CP_ACP, 0, user->permissions, -1, str, user->permissions.GetLength() * 2, NULL, NULL);
	Encryption::getInstance()->encryption(str);
	str[strlen(str)] = '\n';
	strcat(buff, str);
}