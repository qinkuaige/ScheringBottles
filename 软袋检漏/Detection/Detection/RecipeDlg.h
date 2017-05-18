#pragma once
#include "Control.h"
#include "afxcmn.h"

// CRecipeDlg 对话框
class CDetectionDlg;
class CRecipeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecipeDlg)

public:
	CRecipeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecipeDlg();

// 对话框数据
	enum { IDD = IDD_RECIPE };
	enum{
		L_Num = 0,//列表控件的列
		L_Name = 1
	};
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
	CListCtrl m_rList;
	DECLARE_EVENTSINK_MAP()
	void LButtonUpReLoad(long ID, LPCTSTR addr, long other);
	void LButtonUpReAdd(long ID, LPCTSTR addr, long other);
	void LButtonUpReDelete(long ID, LPCTSTR addr, long other);
	afx_msg void OnEnSetfocusReName();
};
