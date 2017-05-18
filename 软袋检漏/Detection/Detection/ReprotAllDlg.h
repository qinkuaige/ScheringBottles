#pragma once
#include "afxcmn.h"


// CReprotAllDlg 对话框
class CDetectionDlg;
class CReprotAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprotAllDlg)

public:
	CReprotAllDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReprotAllDlg();

// 对话框数据
	enum { IDD = IDD_REPORT_ALL };
	enum{
		L_Num = 0,//列表控件的列
		L_Name = 1
	};
public:
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//初始化列表控件
	INT loadRecipeName();//加载配方名称
public:
	CDetectionDlg* m_pDlg;//主界面 
	CControl* m_pControl;//主逻辑类
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
	CListCtrl m_rList;
};
