#pragma once
#include "Control.h"
// CMReportDlg 对话框
class CDetectionDlg;
class CMReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMReportDlg)

public:
	CMReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMReportDlg();

// 对话框数据
	enum { IDD = IDD_MENU_REPORT };
public:
	INT initDialog(CDetectionDlg* parent, CPoint point =CPoint(0,200));
	INT showDialog(INT dlgID);
public:
	CDetectionDlg* m_pDlg;//父窗口指针
	CControl* m_control;//主逻辑控制指针
	CRect m_rect;//保存窗口位置
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickRReslut();
	void ClickRErr();
};
