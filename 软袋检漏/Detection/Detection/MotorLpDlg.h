#pragma once
#include "SetValueDlg.h"
#include "CDLF_Button.h"
#include "MotorSL.h"
// CMotorLpDlg �Ի���
class CDetectionDlg;
class CMotorLpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorLpDlg)

public:
	CMotorLpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMotorLpDlg();

// �Ի�������
	enum { IDD = IDD_MOTOR_LP };
public:
	enum{
		Sleep_Time = 200,//�ŷ��㱣��ʱ��
	};
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID);
	INT buttonChange(CDLF_Button& button, CString addr);//��ťȡ��
	INT showState(CDLF_Button& button, INT value);//��ʾ��ť״̬
	INT getValue(LONG* data);//�����ŷ���ȡ�����ݽ��
	INT setDengValue(INT ID, LONG value);//
	INT showDeng();//ָʾ����ʾ
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
	void ClickStart();
	void ClickZiDong();
	void ClickChSpeed();
	void ClickClear();
	void ClickWangDai();
	void ClickTiaoShi();
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	CDLF_Button m_tiaoShi;
	CDLF_Button m_tongBu;
	void ClickTongBu();
	void LButtonUpStart(long ID, LPCTSTR addr, long other);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void LButtonDownStart(long ID, LPCTSTR addr, long other);
	void LButtonDownZiDong(long ID, LPCTSTR addr, long other);
	void LButtonUpZiDong(long ID, LPCTSTR addr, long other);
	afx_msg void OnBnClickedChSpeed();
};
