#pragma once
#include "Control.h"
#include "afxcmn.h"

// CRecipeDlg �Ի���
class CDetectionDlg;
class CRecipeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeDlg)

public:
	CRecipeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecipeDlg();

// �Ի�������
	enum { IDD = IDD_RECIPE };
	enum{
		L_Num = 0,//�б�ؼ�����
		L_Name = 1
	};
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//��ʼ���б�ؼ�
	INT loadRecipeName();//�����䷽����
public:
	CDetectionDlg* m_pDlg;//������ 
	CControl* m_pControl;//���߼���
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rList;
	DECLARE_EVENTSINK_MAP()
	void LButtonUpReLoad(long ID, LPCTSTR addr, long other);
	void LButtonUpReAdd(long ID, LPCTSTR addr, long other);
	void LButtonUpReDelete(long ID, LPCTSTR addr, long other);
	afx_msg void OnEnSetfocusReName();
};
