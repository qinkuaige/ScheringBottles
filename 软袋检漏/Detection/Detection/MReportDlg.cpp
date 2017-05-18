// MReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "MReportDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CMReportDlg 对话框

IMPLEMENT_DYNAMIC(CMReportDlg, CDialogEx)

CMReportDlg::CMReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMReportDlg::IDD, pParent)
{

}

CMReportDlg::~CMReportDlg()
{
}

void CMReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMReportDlg, CDialogEx)
END_MESSAGE_MAP()


// CMReportDlg 消息处理程序
INT CMReportDlg::initDialog(CDetectionDlg* parent, CPoint point)
{
	m_pDlg = parent;
	m_control = &parent->m_control;
	Create(IDD, parent);
	CRect rect;
	GetClientRect(&rect);
	//获取主窗口位置
	CRect rectW;
	m_pDlg->GetWindowRect(&rectW);
	point.x += rectW.left;
	point.y += rectW.top;

	CRect rectM(point.x, point.y - rect.Height(), point.x + rect.Width(), point.y);
	MoveWindow(rectM);
	m_rect = rectM;

	
	return TRUE;
}

INT CMReportDlg::showDialog(INT dlgID)
{
	static INT sub = 0;
	if (dlgID == IDD)
	{
		sub = !sub;
		if (sub)
		{
			ShowWindow(SW_SHOW);
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
		
	}
	else
	{
		sub = 0;
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}

BEGIN_EVENTSINK_MAP(CMReportDlg, CDialogEx)
ON_EVENT(CMReportDlg, IDC_R_RESLUT, DISPID_CLICK, CMReportDlg::ClickRReslut, VTS_NONE)
ON_EVENT(CMReportDlg, IDC_R_ERR, DISPID_CLICK, CMReportDlg::ClickRErr, VTS_NONE)
END_EVENTSINK_MAP()


void CMReportDlg::ClickRReslut()
{
	m_pDlg->showDialog(CReprotDlg::IDD);
}


void CMReportDlg::ClickRErr()
{
	m_pDlg->showDialog(CErrInfoDlg::IDD);
}
