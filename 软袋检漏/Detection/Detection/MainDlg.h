#pragma once
#include"Control.h"
#include "afxcmn.h"
#include "CDLF_Button.h"
#include "resource.h"

// CMainDlg 对话框
class CDetectionDlg;
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN };
public:
	INT initDlg(CDetectionDlg* parentdlg);//创建窗口
	INT showDlg(UINT dialogID);//显示窗口
	INT initList();//初始化列表空间
	INT startSetTime(INT start = TRUE);//开始/结束定时器
public:
	INT updataList(INT sub[]);//报表控件添加数据
	INT updataTongJi();//定时器刷新统计
	INT updataList();//定时器刷新 高压箱参数
	INT showState(CDLF_Button& button, INT value
		, CString name1, CString name2);//显示按钮状态
public:
	CControl* m_pControl;
	CDetectionDlg* m_pDlg;//主窗口指针
	INT m_runTime;//运行时间
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
