#pragma once

#include "SetValueDlg.h"
#include "MotorSL.h"
#include "CDLF_Button.h"

class CDetectionDlg;
class CMotorRDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorRDDlg)

public:
	CMotorRDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMotorRDDlg();

// �Ի�������
	enum { IDD = IDD_MOTOR_RD };
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID);
	//INT buttonChange(CDLF_Button& button, CString addr);//��ťȡ��
	//INT showState(CDLF_Button& button, INT value);//��ʾ��ť״̬
	INT getValue(LONG* data);//�����ŷ���ȡ�����ݽ��
	//INT setDengValue(INT ID, LONG value);//
	//INT showDeng();//ָʾ����ʾ
	INT ChSpeed(INT speed);//�ı��ٶ�
	INT ClearData();//�������

public:
	CDetectionDlg* m_pDlg;
	CMotorSL* m_pMotor;
	CSetValueDlg m_setValue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void LButtonDownUp1(long ID, LPCTSTR addr, long other);
	void LButtonUpUp1(long ID, LPCTSTR addr, long other);
	CDLF_Button m_tongbu;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedChSpeed();
	void ClickTongBu();
	CDLF_Button m_tongBuBT;
	void ClickStart();
	void ClickTestMotor();
	CDLF_Button m_testMotorBT;
	void ClickDiYa();
	CDLF_Button m_diYa;
};
