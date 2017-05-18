// ErrInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "ErrInfoDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CErrInfoDlg �Ի���

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


// CErrInfoDlg ��Ϣ�������
// CReprotDlg ��Ϣ�������

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

//��ʼ���б�ؼ�
INT CErrInfoDlg::initList()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	m_rList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������  

	m_rList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(1, _T("ʱ��"), LVCFMT_CENTER, 250, 0);
	m_rList.InsertColumn(2, _T("����Ա"), LVCFMT_CENTER, 100, 0);
	m_rList.InsertColumn(3, _T("������Ϣ"), LVCFMT_CENTER, rect.Width() - 400, 0);
	
	return TRUE;
}

//��ʼ��ʱ��ؼ�
INT CErrInfoDlg::initTime()
{
	
	return TRUE;
}

//��������
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
		m_rList.DeleteAllItems();//����б�
		INT count = 0;//������
		CString str;
		while (!err.IsEOF())
		{
			INT sub = 1;//�к�
			//���
			str.Format(_T("%ld"), count + 1);
			m_rList.InsertItem(count, str);
			CTime time(err.m_TI);
			str = time.Format(_T("%Y��%m��%d��%H:%M:%S"));
			m_rList.SetItemText(count, sub++, str);//����
			m_rList.SetItemText(count, sub++, err.m_NAME);//����Ա
			m_rList.SetItemText(count, sub++, err.m_INFO);//������Ϣ
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
	//��ʼʱ��
	m_sTime1.GetTime(time1);
	m_sTime2.GetTime(time2);
	CTime timeStart(time1.GetYear(), time1.GetMonth(), time1.GetDay(),
		time2.GetHour(), time2.GetMinute(), time2.GetSecond());

	//����ʱ��
	m_eTime1.GetTime(time1);
	m_eTime2.GetTime(time2);
	CTime timeEnd(time1.GetYear(), time1.GetMonth(), time1.GetDay(),
		time2.GetHour(), time2.GetMinute(), time2.GetSecond());

	//��ȡ����
	insertList(timeStart.GetTime(), timeEnd.GetTime());
}
