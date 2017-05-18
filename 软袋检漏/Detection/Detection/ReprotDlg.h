#pragma once
#include "resource.h"
#include "Control.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include <vector>
using namespace std;
// CReprotDlg �Ի���
class CDetectionDlg;
class CReprotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprotDlg)

public:
	CReprotDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReprotDlg();

// �Ի�������
	enum { IDD = IDD_REPORT };
public:
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//��ʼ���б�ؼ�
	INT initTime();//��ʼ��ʱ��ؼ�
	INT insertList(vector<LONGLONG>& data);//��������
	INT insertList(LONGLONG startT, LONGLONG endT);//��������
	static UINT listThread(LPVOID lParam);
public:
	CDetectionDlg* m_dlg;
	CControl* m_control;
	vector<LONGLONG> m_data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rList;
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
	CDateTimeCtrl m_sTime1;
	CDateTimeCtrl m_sTime2;
	CDateTimeCtrl m_eTime1;
	CDateTimeCtrl m_eTime2;
};
