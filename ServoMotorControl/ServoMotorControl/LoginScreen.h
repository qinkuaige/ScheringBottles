#pragma once
#include "afxwin.h"
#include <map>
#include "ClickEdit.h"
#include "UserInformation.h"

using namespace std;


// ��¼�Ի���
class LoginScreen : public CDialogEx
{
	DECLARE_DYNAMIC(LoginScreen)
	static const UINT MessageNumberBase = 10000;
public:
	LoginScreen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginScreen();
	enum { IDD = IDD_DIALOG2 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	DECLARE_MESSAGE_MAP()

private:
	CDialogEx* m_childWindows; // �Ӵ���
	POINT   m_windowSize;      //���ڴ�С
	CComboBox m_userNameBox;
	ClickEdit m_passwordEdit;// ���������
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void ManageUsers();
	afx_msg void Login();
	afx_msg void Quit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
};
