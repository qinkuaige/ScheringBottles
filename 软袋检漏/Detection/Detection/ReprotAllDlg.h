#pragma once
#include "afxcmn.h"


// CReprotAllDlg �Ի���
class CDetectionDlg;
class CReprotAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprotAllDlg)

public:
	CReprotAllDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReprotAllDlg();

// �Ի�������
	enum { IDD = IDD_REPORT_ALL };
	enum{
		L_Num = 0,//�б�ؼ�����
		L_Name = 1
	};
public:
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
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
	CListCtrl m_rList;
};
