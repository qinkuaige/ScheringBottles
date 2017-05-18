#pragma once
#include "SetValueDlg.h"
#include "CDLF_Button.h"
#include "MotorSL.h"
// CMotorLpDlg 对话框
class CDetectionDlg;
class CMotorLpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorLpDlg)

public:
	CMotorLpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotorLpDlg();

// 对话框数据
	enum { IDD = IDD_MOTOR_LP };
public:
	enum{
		Sleep_Time = 200,//伺服点保持时间
	};
public:
	INT initDialog(CDetectionDlg* parentDlg);
	INT showDialog(INT dlgID);
	INT buttonChange(CDLF_Button& button, CString addr);//按钮取反
	INT showState(CDLF_Button& button, INT value);//显示按钮状态
	INT getValue(LONG* data);//计算伺服获取的数据结果
	INT setDengValue(INT ID, LONG value);//
	INT showDeng();//指示灯显示
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
