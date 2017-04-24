#pragma once


// ChangePassword 对话框

class ChangePassword : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePassword)

public:
	ChangePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangePassword();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void ok();
};
