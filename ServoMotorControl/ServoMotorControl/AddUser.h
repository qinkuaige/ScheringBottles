#pragma once
#include "afxwin.h"


// ����û��Ի���

class AddUser : public CDialogEx
{
	DECLARE_DYNAMIC(AddUser)

public:
	AddUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddUser();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };
private:
	POINT m_windowSize;
	CComboBox m_permisBox;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OK();
};
