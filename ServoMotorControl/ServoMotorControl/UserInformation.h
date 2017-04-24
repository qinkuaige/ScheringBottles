#pragma once

#include <map>
#include <stdio.h>

using namespace std;

const char* const Permissions[] = { "超级用户", "管理员", "调试员" };

struct User  //用户
{
	CString name; //用户名
	CString password; //密码
	CString permissions; // 用户权限

	User() :name(_T("")), password(_T("")), permissions(_T(""))
	{

	}
};


class UserInformation
{
public:
	static UserInformation* getInstance();//获得一个实例
	UINT addUser(User* &);//添加用户
	int deleteUser(CString user_name);//删除用户
	int changePassword(CString newPasword);
	int  set_user(CString name);//设置当前用户
	bool verifyPassword(CString);//确认密码
	int get_level(const CString &permissions);//获取用户等级
//内联函数
	inline User* get_user(){ return m_user; } //获得当前用户信息
	inline map<CString, User*>* get_allUser(){ return &m_allUser; }//获得所有用户信息
private:
	UserInformation();
	~UserInformation();
	void init();//初始化
	void userToChar(User* user, char* &buff); //合并用户信息为 名字，密码，权限 形式
private:
	FILE* m_file;//用户信息文件指针
	const char* const m_fileName;//用户信息文件名
	User*  m_user;         //当前用户
	map<CString, User*> m_allUser; //所有用户	
};
