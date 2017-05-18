// ReprotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ReprotDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CReprotDlg 对话框

IMPLEMENT_DYNAMIC(CReprotDlg, CDialogEx)

CReprotDlg::CReprotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReprotDlg::IDD, pParent)
{
	m_dlg = NULL;
	m_control = NULL;
}

CReprotDlg::~CReprotDlg()
{
}

void CReprotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_R_LIST, m_rList);
	DDX_Control(pDX, IDC_S_TIME1, m_sTime1);
	DDX_Control(pDX, IDC_S_TIME2, m_sTime2);
	DDX_Control(pDX, IDC_E_TIME1, m_eTime1);
	DDX_Control(pDX, IDC_E_TIME2, m_eTime2);
}


BEGIN_MESSAGE_MAP(CReprotDlg, CDialogEx)
END_MESSAGE_MAP()


// CReprotDlg 消息处理程序

INT CReprotDlg::initDialog(CDetectionDlg* parent)
{
	m_dlg = parent;
	m_control = &parent->m_control;
	Create(IDD, parent);
	initList();
	//initTime();//初始化时间控件
	return TRUE;
}

INT CReprotDlg::showDialog(INT dlgID)
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
INT CReprotDlg::initList()
{
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小  
	m_rList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列  
	
	m_rList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 250, 0);
	m_rList.InsertColumn(2, _T("批号"), LVCFMT_CENTER, 100, 0);
	INT width = rect.Width() - 400;
	INT cNum = 7;//9列
	INT add = 3;
	CString str;
	INT i = 0;
	for (; i < 6; ++i)
	{
		str.Format(_T("CH%d"), i + 1);
		m_rList.InsertColumn(i + add, str, LVCFMT_CENTER, width / cNum, i + add);
	}
	m_rList.InsertColumn(i + add, _T("结果"), LVCFMT_CENTER, width / cNum, i + add);
	
	return TRUE;
}

//初始化时间控件
INT CReprotDlg::initTime()
{
	CTime time = CTime::GetCurrentTime();
	LONGLONG timeL = 30 * 3 * 24 * 60 * 60;
	CTime timeMin(time.GetTime() - timeL);//能查询前三个月
	CTime timeMax(time.GetTime() + 24 * 60 * 60);//能查询后一天
	m_sTime1.SetRange(&timeMin, &timeMax);
	//m_sTime2.SetRange(&timeMin, &timeMax);
	m_eTime1.SetRange(&timeMin, &timeMax);
	//m_eTime2.SetRange(&timeMin, &timeMax);
	return TRUE;
}

BEGIN_EVENTSINK_MAP(CReprotDlg, CDialogEx)
ON_EVENT(CReprotDlg, IDC_R_FIND, DISPID_CLICK, CReprotDlg::ClickRFind, VTS_NONE)
END_EVENTSINK_MAP()


void CReprotDlg::ClickRFind()
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
	//m_data.clear();
	//m_control->m_access.ComGetData(timeStart, timeEnd, m_data);
	//insertList(m_data);
	insertList(timeStart.GetTime(), timeEnd.GetTime());
}

//插入数据
INT CReprotDlg::insertList(LONGLONG startT, LONGLONG endT)
{
	CSQLResultRD res;
	CString str = _T("SELECT * FROM ") + res.m_tableName;
	CString tiS, tiE;
	tiS.Format(_T(" WHERE TI >= %ld AND"), startT);
	tiE.Format(_T(" TI <= %ld;"), endT);
	str = str + tiS + tiE;

	if (res.Open(NULL, str))
	{
		m_rList.DeleteAllItems();//清空列表
		INT count = 0;//计数器
		CString str;
		while (!res.IsEOF())
		{
			//序号
			str.Format(_T("%ld"), count + 1);
			m_rList.InsertItem(count, str);
			CTime time(res.m_TI);
			str = time.Format(_T("%Y年%m月%d日%H:%M:%S"));
			m_rList.SetItemText(count, 1, str);//日期
			//批号因为有20个字符，
			//后面会自动补成空格所以去掉多余的空格
			INT sub = res.m_PH.Find(_T(" "));
			res.m_PH = res.m_PH.Left(sub);
			m_rList.SetItemText(count, 2, res.m_PH);

			str.Format(_T("%.2f"), res.m_CH1*1.0/100);
			m_rList.SetItemText(count, 3, str);//CH1
			str.Format(_T("%.2f"), res.m_CH2*1.0 / 100);
			m_rList.SetItemText(count, 4, str);//CH2
			str.Format(_T("%.2f"), res.m_CH3*1.0 / 100);
			m_rList.SetItemText(count, 5, str);//CH3
			str.Format(_T("%.2f"), res.m_CH4*1.0 / 100);
			m_rList.SetItemText(count, 6, str);//CH4
			str.Format(_T("%.2f"), res.m_CH5*1.0 / 100);
			m_rList.SetItemText(count, 6, str);//CH5
			str.Format(_T("%.2f"), res.m_CH6*1.0 / 100);
			m_rList.SetItemText(count, 6, str);//CH5

			str.Format(_T("%.2f"), res.m_NG*1.0 / 100);
			m_rList.SetItemText(count, 7, str);//NG
			++count;
			res.MoveNext();
		}
	}
	return TRUE;
}

//插入数据
INT CReprotDlg::insertList(vector<LONGLONG>& data)
{
	m_rList.DeleteAllItems();
	UINT num = data.size();
	CString str;
	for (UINT i = 0; i < num / 6; ++i)
	{
		str.Format(_T("%ld"), i + 1);
		m_rList.InsertItem(i, str);
		CTime time(data[i * 6]);
		str = time.Format(_T("%Y年%m月%d日%H:%M:%S"));
		m_rList.SetItemText(i, 1, str);
		for (INT j = 1; j < 6; ++j)
		{
			if (data[i * 6 + j] < -1)
			{
				str = _T("空");
			}
			else
			{
				if (j == 5)
				{
					str.Format(_T("%d"), data[i * 6 + j]);
				}
				else
				{
					str.Format(_T("%.2f V"), data[i * 6 + j] * 1.0 / 100);
				}
				
			}
			m_rList.SetItemText(i, j + 1, str);
		}
	}
	
	return TRUE;
}