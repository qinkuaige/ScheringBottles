#pragma once
#include "Control.h"
// CMReportDlg �Ի���
class CDetectionDlg;
class CMReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMReportDlg)

public:
	CMReportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMReportDlg();

// �Ի�������
	enum { IDD = IDD_MENU_REPORT };
public:
	INT initDialog(CDetectionDlg* parent, CPoint point =CPoint(0,200));
	INT showDialog(INT dlgID);
public:
	CDetectionDlg* m_pDlg;//������ָ��
	CControl* m_control;//���߼�����ָ��
	CRect m_rect;//���洰��λ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickRReslut();
	void ClickRErr();
};
