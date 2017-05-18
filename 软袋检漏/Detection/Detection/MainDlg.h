#pragma once
#include"Control.h"
#include "afxcmn.h"
#include "CDLF_Button.h"
#include "resource.h"

// CMainDlg �Ի���
class CDetectionDlg;
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAIN };
public:
	INT initDlg(CDetectionDlg* parentdlg);//��������
	INT showDlg(UINT dialogID);//��ʾ����
	INT initList();//��ʼ���б�ռ�
	INT startSetTime(INT start = TRUE);//��ʼ/������ʱ��
public:
	INT updataList(INT sub[]);//����ؼ��������
	INT updataTongJi();//��ʱ��ˢ��ͳ��
	INT updataList();//��ʱ��ˢ�� ��ѹ�����
	INT showState(CDLF_Button& button, INT value
		, CString name1, CString name2);//��ʾ��ť״̬
public:
	CControl* m_pControl;
	CDetectionDlg* m_pDlg;//������ָ��
	INT m_runTime;//����ʱ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CListCtrl m_rList;
	afx_msg void OnBnClickedClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()
	void ClickMRun();
	CDLF_Button m_start;
	void DblClickMRun();
	void ClickMSpeed();
	void ClickMRestor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedTest();
};
