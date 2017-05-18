
// DetectionDlg.h : 头文件
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
// CDetectionDlg 对话框
class CDetectionDlg : public CDialogEx
{
// 构造
public:
	CDetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	
public:
	INT initDlg();//初始化子窗口
	INT showDialog(INT dlgID);//显示窗口
	INT showMenu(INT dlgID);//显示菜单
	INT showKey(CRect rect);//显示屏幕键盘
public:
	CMainDlg m_mainDlg;
	CReprotDlg m_reportDlg;
	CControl m_control;//主逻辑类
	CMotorRDDlg m_motorDlg;//伺服控制窗口
	CParamDlg m_paramDlg;//参数修改窗口
	CSetValueDlg m_setValueDlg;//数据修改窗口
	CUserDlg m_userDlg;//登录窗口
	CErrInfoDlg m_errInfoDlg;//错误信息窗口
	CMReportDlg m_mReportDLg;//历史数据菜单窗口
	CWnd* m_pKey;//屏幕键盘
	CRecipeDlg m_recipeDlg;//配方修改窗口
	CString m_path;//保存当前文件路径
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
