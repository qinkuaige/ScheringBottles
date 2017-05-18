#pragma once

#include "Control.h"
#include "afxwin.h"

enum {
	r_Null = 0,//��Ȩ��
	r_User = 1,//����Ա
	r_Motor = 2,//������Ա
	r_Control = 3,//����Ա
	r_Code = 4,//����Ա
};

// CUserDlg �Ի���
class CDetectionDlg;
class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserDlg();

// �Ի�������
	enum { IDD = IDD_USER };
	
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID = 0);
private:
	INT PriReadIni();//��ȡ�����ļ�
	INT PriReadSQL();//��ȡ���ݿ�����
	INT PriOut();//�˳�����
	INT PriPassWord();//��֤�����Ƿ���ȷ
	virtual void OnOK(){};
	virtual void OnCancel(){};
private:
	CControl* m_pControl;//���߼�ָ��
	CDetectionDlg* m_pDlg;//������ָ��
	CSQLUser m_sqlUser;//��¼�û���
	CString m_path;//��ǰ����·��
	INT m_isShow;//�Ƿ���ʾ��¼����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
