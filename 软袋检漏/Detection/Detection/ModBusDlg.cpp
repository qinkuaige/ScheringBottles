// ModBusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ModBusDlg.h"
#include "afxdialogex.h"
#include"ModBus.h"

// CModBusDlg 对话框

IMPLEMENT_DYNAMIC(CModBusDlg, CDialogEx)

CModBusDlg::CModBusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModBusDlg::IDD, pParent)
{

}

CModBusDlg::~CModBusDlg()
{
  
}

void CModBusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_com);
}


BEGIN_MESSAGE_MAP(CModBusDlg, CDialogEx)
END_MESSAGE_MAP()


// CModBusDlg 消息处理程序
BEGIN_EVENTSINK_MAP(CModBusDlg, CDialogEx)
	ON_EVENT(CModBusDlg, IDC_MSCOMM1, 1, CModBusDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CModBusDlg::OnCommMscomm1()
{
	if (m_modBus != NULL)
	{
		//m_modBus->PriGetData();
	}
}
