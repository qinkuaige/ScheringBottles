#pragma once

#include "SetValueDlg.h"
#include "MotorSL.h"
#include "CDLF_Button.h"

class CDetectionDlg;
class CMotorRDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorRDDlg)

public:
	CMotorRDDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotorRDDlg();

// 对话框数据
	enum { IDD = IDD_MOTOR_RD };
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID);
	//INT buttonChange(CDLF_Button& button, CString addr);//按钮取反
	//INT showState(CDLF_Button& button, INT value);//显示按钮状态
	INT getValue(LONG* data);//计算伺服获取的数据结果
	//INT setDengValue(INT ID, LONG value);//
	//INT showDeng();//指示灯显示
	INT ChSpeed(INT speed);//改变速度
	INT ClearData();//清空数据

public:
	CDetectionDlg* m_pDlg;
	CMotorSL* m_pMotor;
	CSetValueDlg m_setValue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
