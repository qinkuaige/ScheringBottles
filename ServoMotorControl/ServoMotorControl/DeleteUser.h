#pragma once
#include "afxwin.h"


// DeleteUser 对话框

class DeleteUser : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteUser)

public:
	DeleteUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DeleteUser();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void ok();
	CComboBox m_deleteUserBox;
};
