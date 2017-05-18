#pragma once
#include "resource.h"
#include "Control.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include <vector>
using namespace std;
// CReprotDlg 对话框
class CDetectionDlg;
class CReprotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprotDlg)

public:
	CReprotDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReprotDlg();

// 对话框数据
	enum { IDD = IDD_REPORT };
public:
	INT initDialog(CDetectionDlg* parent);
	INT showDialog(INT dlgID);
	INT initList();//初始化列表控件
	INT initTime();//初始化时间控件
	INT insertList(vector<LONGLONG>& data);//插入数据
	INT insertList(LONGLONG startT, LONGLONG endT);//插入数据
	static UINT listThread(LPVOID lParam);
public:
	CDetectionDlg* m_dlg;
	CControl* m_control;
	vector<LONGLONG> m_data;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_rList;
	DECLARE_EVENTSINK_MAP()
	void ClickRFind();
	CDateTimeCtrl m_sTime1;
	CDateTimeCtrl m_sTime2;
	CDateTimeCtrl m_eTime1;
	CDateTimeCtrl m_eTime2;
};
