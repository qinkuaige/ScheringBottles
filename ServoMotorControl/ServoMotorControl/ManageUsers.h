#pragma once

#include <map>
using namespace std;
//管理用户对话框

class ManageUsers : public CDialogEx
{
	DECLARE_DYNAMIC(ManageUsers)
public:
	ManageUsers(CWnd* pParent = NULL);   
	virtual ~ManageUsers();
	enum { IDD = IDD_DIALOG3 };
private:
	POINT m_windowSize;
	map<UINT,CDialogEx*> m_chidWindow;
	CRect  m_DialogChild;
	map<UINT, CDialogEx*>::iterator m_childWindow_itor;
private:
	void change_childWindow(UINT wind_id); //切换子窗口
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void add_user();
	afx_msg void delete_user();
	afx_msg void change_password();
	virtual void OnOK();
	virtual void OnCancel();
};
