#pragma once

#include "Control.h"
#include "afxwin.h"

enum {
	r_Null = 0,//空权限
	r_User = 1,//操作员
	r_Motor = 2,//机修人员
	r_Control = 3,//管理员
	r_Code = 4,//程序员
};

// CUserDlg 对话框
class CDetectionDlg;
class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDlg();

// 对话框数据
	enum { IDD = IDD_USER };
	
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID = 0);
private:
	INT PriReadIni();//读取配置文件
	INT PriReadSQL();//读取数据库数据
	INT PriOut();//退出程序
	INT PriPassWord();//验证密码是否正确
	virtual void OnOK(){};
	virtual void OnCancel(){};
private:
	CControl* m_pControl;//主逻辑指针
	CDetectionDlg* m_pDlg;//主窗口指针
	CSQLUser m_sqlUser;//登录用户表
	CString m_path;//当前程序路径
	INT m_isShow;//是否显示登录窗口

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CComboBox m_nameList;
	DECLARE_EVENTSINK_MAP()
	void ClickUOut();
	afx_msg void OnEnSetfocusUPw();
	void ClickUOk();
	afx_msg void OnEnChangeUPw();
};
