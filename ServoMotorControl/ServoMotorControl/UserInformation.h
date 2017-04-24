#pragma once

#include <map>
#include <stdio.h>

using namespace std;

const char* const Permissions[] = { "�����û�", "����Ա", "����Ա" };

struct User  //�û�
{
	CString name; //�û���
	CString password; //����
	CString permissions; // �û�Ȩ��

	User() :name(_T("")), password(_T("")), permissions(_T(""))
	{

	}
};


class UserInformation
{
public:
	static UserInformation* getInstance();//���һ��ʵ��
	UINT addUser(User* &);//����û�
	int deleteUser(CString user_name);//ɾ���û�
	int changePassword(CString newPasword);
	int  set_user(CString name);//���õ�ǰ�û�
	bool verifyPassword(CString);//ȷ������
	int get_level(const CString &permissions);//��ȡ�û��ȼ�
//��������
	inline User* get_user(){ return m_user; } //��õ�ǰ�û���Ϣ
	inline map<CString, User*>* get_allUser(){ return &m_allUser; }//��������û���Ϣ
private:
	UserInformation();
	~UserInformation();
	void init();//��ʼ��
	void userToChar(User* user, char* &buff); //�ϲ��û���ϢΪ ���֣����룬Ȩ�� ��ʽ
private:
	FILE* m_file;//�û���Ϣ�ļ�ָ��
	const char* const m_fileName;//�û���Ϣ�ļ���
	User*  m_user;         //��ǰ�û�
	map<CString, User*> m_allUser; //�����û�	
};
