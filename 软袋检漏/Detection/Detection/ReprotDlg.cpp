// ReprotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "ReprotDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CReprotDlg �Ի���

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


// CReprotDlg ��Ϣ�������

INT CReprotDlg::initDialog(CDetectionDlg* parent)
{
	m_dlg = parent;
	m_control = &parent->m_control;
	Create(IDD, parent);
	initList();
	//initTime();//��ʼ��ʱ��ؼ�
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

//��ʼ���б�ؼ�
INT CReprotDlg::initList()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	m_rList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������  
	
	m_rList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(1, _T("ʱ��"), LVCFMT_CENTER, 250, 0);
	m_rList.InsertColumn(2, _T("����"), LVCFMT_CENTER, 100, 0);
	INT width = rect.Width() - 400;
	INT cNum = 7;//9��
	INT add = 3;
	CString str;
	INT i = 0;
	for (; i < 6; ++i)
	{
		str.Format(_T("CH%d"), i + 1);
		m_rList.InsertColumn(i + add, str, LVCFMT_CENTER, width / cNum, i + add);
	}
	m_rList.InsertColumn(i + add, _T("���"), LVCFMT_CENTER, width / cNum, i + add);
	
	return TRUE;
}

//��ʼ��ʱ��ؼ�
INT CReprotDlg::initTime()
{
	CTime time = CTime::GetCurrentTime();
	LONGLONG timeL = 30 * 3 * 24 * 60 * 60;
	CTime timeMin(time.GetTime() - timeL);//�ܲ�ѯǰ������
	CTime timeMax(time.GetTime() + 24 * 60 * 60);//�ܲ�ѯ��һ��
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
	//m_data.clear();
	//m_control->m_access.ComGetData(timeStart, timeEnd, m_data);
	//insertList(m_data);
	insertList(timeStart.GetTime(), timeEnd.GetTime());
}

//��������
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
		m_rList.DeleteAllItems();//����б�
		INT count = 0;//������
		CString str;
		while (!res.IsEOF())
		{
			//���
			str.Format(_T("%ld"), count + 1);
			m_rList.InsertItem(count, str);
			CTime time(res.m_TI);
			str = time.Format(_T("%Y��%m��%d��%H:%M:%S"));
			m_rList.SetItemText(count, 1, str);//����
			//������Ϊ��20���ַ���
			//������Զ����ɿո�����ȥ������Ŀո�
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

//��������
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
		str = time.Format(_T("%Y��%m��%d��%H:%M:%S"));
		m_rList.SetItemText(i, 1, str);
		for (INT j = 1; j < 6; ++j)
		{
			if (data[i * 6 + j] < -1)
			{
				str = _T("��");
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