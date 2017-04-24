#pragma once
#include "afxwin.h"
#include <map>
#include "ClickEdit.h"
#include "UserInformation.h"

using namespace std;


// 登录对话框
class LoginScreen : public CDialogEx
{
	DECLARE_DYNAMIC(LoginScreen)
	static const UINT MessageNumberBase = 10000;
public:
	LoginScreen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginScreen();
	enum { IDD = IDD_DIALOG2 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	DECLARE_MESSAGE_MAP()

private:
	CDialogEx* m_childWindows; // 子窗口
	POINT   m_windowSize;      //窗口大小
	CComboBox m_userNameBox;
	ClickEdit m_passwordEdit;// 密码输入框
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void ManageUsers();
	afx_msg void Login();
	afx_msg void Quit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
};
