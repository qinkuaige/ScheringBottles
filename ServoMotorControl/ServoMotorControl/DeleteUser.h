#pragma once
#include "afxwin.h"


// DeleteUser �Ի���

class DeleteUser : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteUser)

public:
	DeleteUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeleteUser();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void ok();
	CComboBox m_deleteUserBox;
};
