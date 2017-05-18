#pragma once
#include "afxcmn.h"
#include "Control.h"
#include <vector>
#include "afxdtctl.h"
using namespace std;

// CErrInfoDlg 对话框
class CDetectionDlg;
class CErrInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrInfoDlg)

public:
	CErrInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CErrInfoDlg();

// 对话框数据
	enum { IDD = IDD_ERR_INFO };
public:
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//初始化列表控件
	INT initTime();//初始化时间控件
	INT insertList(LONGLONG startT, LONGLONG endT);//插入数据
public:
	CDetectionDlg* m_dlg;
	CControl* m_control;
	vector<LONGLONG> m_data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rList;
	CDateTimeCtrl m_sTime1;
	CDateTimeCtrl m_eTime1;
	CDateTimeCtrl m_sTime2;
	CDateTimeCtrl m_eTime2;
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
};
