// ReprotAllDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ReprotAllDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CReprotAllDlg 对话框

IMPLEMENT_DYNAMIC(CReprotAllDlg, CDialogEx)

CReprotAllDlg::CReprotAllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReprotAllDlg::IDD, pParent)
{

}

CReprotAllDlg::~CReprotAllDlg()
{
}

void CReprotAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_R_LIST, m_rList);
}


BEGIN_MESSAGE_MAP(CReprotAllDlg, CDialogEx)
END_MESSAGE_MAP()


// CRecipeDlg 消息处理程序
INT CReprotAllDlg::initDialog(CDetectionDlg* parent)
{
	m_pDlg = parent;
	m_pControl = &m_pDlg->m_control;
	Create(IDD, m_pDlg);
	initList();
	loadRecipeName();
	return TRUE;
}

INT CReprotAllDlg::showDialog(INT dlgID)
{
	if (dlgID == IDD)
	{

		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}

//初始化列表控件
INT CReprotAllDlg::initList()
{
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小  
	m_rList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列  

	m_rList.InsertColumn(L_Num, _T("序号"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(L_Name, _T("配方名"), LVCFMT_CENTER, rect.Width() - 50, 0);

	return TRUE;
}

//加载配方名称
INT CReprotAllDlg::loadRecipeName()
{
	
	return TRUE;
}

// CReprotAllDlg 消息处理程序
BEGIN_EVENTSINK_MAP(CReprotAllDlg, CDialogEx)
	ON_EVENT(CReprotAllDlg, IDC_R_FIND, DISPID_CLICK, CReprotAllDlg::ClickRFind, VTS_NONE)
END_EVENTSINK_MAP()


void CReprotAllDlg::ClickRFind()
{
	
}
