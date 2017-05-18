#pragma once
#include "afxcmn.h"
#include "Control.h"
#include <vector>
#include "afxdtctl.h"
using namespace std;

// CErrInfoDlg �Ի���
class CDetectionDlg;
class CErrInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrInfoDlg)

public:
	CErrInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CErrInfoDlg();

// �Ի�������
	enum { IDD = IDD_ERR_INFO };
public:
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//��ʼ���б�ؼ�
	INT initTime();//��ʼ��ʱ��ؼ�
	INT insertList(LONGLONG startT, LONGLONG endT);//��������
public:
	CDetectionDlg* m_dlg;
	CControl* m_control;
	vector<LONGLONG> m_data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rList;
	CDateTimeCtrl m_sTime1;
	CDateTimeCtrl m_eTime1;
	CDateTimeCtrl m_sTime2;
	CDateTimeCtrl m_eTime2;
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
};
