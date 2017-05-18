
// DetectionDlg.h : ͷ�ļ�
//

#pragma once
#include "MainDlg.h"
#include "Control.h"
#include "ReprotDlg.h"
#include "MotorLpDlg.h"
#include "MotorRDDlg.h"
#include "ParamDlg.h"
#include "SetValueDlg.h"
#include "UserDlg.h"
#include "ErrInfoDlg.h"
#include "MReportDlg.h"
#include "RecipeDlg.h"
// CDetectionDlg �Ի���
class CDetectionDlg : public CDialogEx
{
// ����
public:
	CDetectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	
public:
	INT initDlg();//��ʼ���Ӵ���
	INT showDialog(INT dlgID);//��ʾ����
	INT showMenu(INT dlgID);//��ʾ�˵�
	INT showKey(CRect rect);//��ʾ��Ļ����
public:
	CMainDlg m_mainDlg;
	CReprotDlg m_reportDlg;
	CControl m_control;//���߼���
	CMotorRDDlg m_motorDlg;//�ŷ����ƴ���
	CParamDlg m_paramDlg;//�����޸Ĵ���
	CSetValueDlg m_setValueDlg;//�����޸Ĵ���
	CUserDlg m_userDlg;//��¼����
	CErrInfoDlg m_errInfoDlg;//������Ϣ����
	CMReportDlg m_mReportDLg;//��ʷ���ݲ˵�����
	CWnd* m_pKey;//��Ļ����
	CRecipeDlg m_recipeDlg;//�䷽�޸Ĵ���
	CString m_path;//���浱ǰ�ļ�·��
	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickOnline1();
	void ClickMain3();
	void ClickMotor6();
	void ClickOut10();
	afx_msg void OnDestroy();
	void ClickParam5();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void LButtonUpReport4(long ID, LPCTSTR addr, long other);
};
