#pragma once
#include "afxwin.h"


// 添加用户对话框

class AddUser : public CDialogEx
{
	DECLARE_DYNAMIC(AddUser)

public:
	AddUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddUser();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };
private:
	POINT m_windowSize;
	CComboBox m_permisBox;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OK();
};
