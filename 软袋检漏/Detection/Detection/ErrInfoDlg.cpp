// ErrInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ErrInfoDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CErrInfoDlg 对话框

IMPLEMENT_DYNAMIC(CErrInfoDlg, CDialogEx)

CErrInfoDlg::CErrInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrInfoDlg::IDD, pParent)
{

}

CErrInfoDlg::~CErrInfoDlg()
{
}

void CErrInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_R_LIST, m_rList);
	DDX_Control(pDX, IDC_S_TIME1, m_sTime1);
	DDX_Control(pDX, IDC_S_TIME2, m_eTime1);
	DDX_Control(pDX, IDC_E_TIME1, m_sTime2);
	DDX_Control(pDX, IDC_E_TIME2, m_eTime2);
}


BEGIN_MESSAGE_MAP(CErrInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CErrInfoDlg 消息处理程序
// CReprotDlg 消息处理程序

INT CErrInfoDlg::initDialog(CDetectionDlg* parent)
{
	m_dlg = parent;
	m_control = &parent->m_control;
	Create(IDD, parent);
	initList();
	return TRUE;
}

INT CErrInfoDlg::showDialog(INT dlgID)
{
	if (dlgID == IDD)
	{
		CTime time = CTime::GetCurrentTime();
		m_eTime1.SetTime(&time);
		m_eTime2.SetTime(&time);
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}

//初始化列表控件
INT CErrInfoDlg::initList()
{
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小  
	m_rList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列  

	m_rList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 250, 0);
	m_rList.InsertColumn(2, _T("操作员"), LVCFMT_CENTER, 100, 0);
	m_rList.InsertColumn(3, _T("错误信息"), LVCFMT_CENTER, rect.Width() - 400, 0);
	
	return TRUE;
}

//初始化时间控件
INT CErrInfoDlg::initTime()
{
	
	return TRUE;
}

//插入数据
INT CErrInfoDlg::insertList(LONGLONG startT, LONGLONG endT)
{
	CSQLErr err;
	CString str = _T("SELECT * FROM ") + err.m_tableName;
	CString tiS, tiE;
	tiS.Format(_T(" WHERE TI >= %ld AND"), startT);
	tiE.Format(_T(" TI <= %ld;"), endT);
	str = str + tiS + tiE;
	if (err.Open(NULL, str))
	{
		m_rList.DeleteAllItems();//清空列表
		INT count = 0;//计数器
		CString str;
		while (!err.IsEOF())
		{
			INT sub = 1;//列号
			//序号
			str.Format(_T("%ld"), count + 1);
			m_rList.InsertItem(count, str);
			CTime time(err.m_TI);
			str = time.Format(_T("%Y年%m月%d日%H:%M:%S"));
			m_rList.SetItemText(count, sub++, str);//日期
			m_rList.SetItemText(count, sub++, err.m_NAME);//操作员
			m_rList.SetItemText(count, sub++, err.m_INFO);//错误信息
			++count;
			err.MoveNext();
		}
	}
	return TRUE;
}
BEGIN_EVENTSINK_MAP(CErrInfoDlg, CDialogEx)
	ON_EVENT(CErrInfoDlg, IDC_R_FIND, DISPID_CLICK, CErrInfoDlg::ClickRFind, VTS_NONE)
END_EVENTSINK_MAP()


void CErrInfoDlg::ClickRFind()
{
	CTime time1;
	CTime time2;
	//开始时间
	m_sTime1.GetTime(time1);
	m_sTime2.GetTime(time2);
	CTime timeStart(time1.GetYear(), time1.GetMonth(), time1.GetDay(),
		time2.GetHour(), time2.GetMinute(), time2.GetSecond());

	//结束时间
	m_eTime1.GetTime(time1);
	m_eTime2.GetTime(time2);
	CTime timeEnd(time1.GetYear(), time1.GetMonth(), time1.GetDay(),
		time2.GetHour(), time2.GetMinute(), time2.GetSecond());

	//获取数据
	insertList(timeStart.GetTime(), timeEnd.GetTime());
}
