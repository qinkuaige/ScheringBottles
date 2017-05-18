// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"


// CMainDlg �Ի���

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_runTime(FALSE)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_M_RUN, m_start);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CLEAR, &CMainDlg::OnBnClickedClear)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TEST, &CMainDlg::OnBnClickedTest)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������

//��������
INT CMainDlg::initDlg(CDetectionDlg* parentdlg)
{
	Create(IDD, parentdlg);
	m_pControl = &parentdlg->m_control;
	m_pDlg = parentdlg;
	SetTimer(2000, 200, NULL);
	//initList();//��ʼ���б�ؼ�
	return TRUE;
}

//��ʾ����
INT CMainDlg::showDlg(UINT dialogID)
{
	if (dialogID == IDD)
	{
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	
	return TRUE;
}

//��ʼ���б�ռ�
INT CMainDlg::initList()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	m_rList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������  
	INT cNum = 6;//6��
	m_rList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() / cNum, 0);
	CString str;
	for (INT i = 1; i < cNum - 1; ++i)
	{
		str.Format(_T("CH%d"),i);
		m_rList.InsertColumn(i, str, LVCFMT_CENTER, rect.Width() / cNum, i);
	}
	m_rList.InsertColumn(cNum - 1, _T("���"), LVCFMT_CENTER, rect.Width() / cNum, cNum);
	return TRUE;
}

//��ʼ/������ʱ��
INT CMainDlg::startSetTime(INT start)
{
	//SetTimer(2000, 300, NULL);
	return TRUE;
}

//����ؼ��������
INT CMainDlg::updataList(INT res[])
{
	static INT count = 0;//������
	++count;
	INT chNum = CControl::CH_Num;
	CString str;
	str.Format(_T("%d"), count);
	m_rList.InsertItem(0, str);
	for (INT i = 0; i < CControl::CH_Num; ++i)
	{
		if (res[i] < 0)
		{
			str = _T("��");
		}
		else
		{
			str.Format(_T("%.2f"), res[i] * 1.0 / 100);
		}
		
		m_rList.SetItemText(0, i + 1, str);
	}
	if (res[chNum] == Res_OK)
	{
		str = _T("OK");
	}
	else if (chNum == Res_NG)
	{
		str = _T("NG");
	}
	else
	{
		str = _T("��");
	}
	m_rList.SetItemText(0, CControl::CH_Num + 1, str);
	return TRUE;
}

//��ʱ��ˢ��ͳ��
INT CMainDlg::updataTongJi()
{
	/*
	{
		CString str;
		INT all = 0, bad = 0, good = 0;//���� ��Ʒ�� ��Ʒ��
		INT num = CControl::ModBus_Num;
		//ͳ��
		all = m_pControl->m_resT.m_allNum;
		SetDlgItemInt(IDC_ALL_NUM, all);
		good = m_pControl->m_resT.m_goodNum;
		SetDlgItemInt(IDC_GOOD_NUM, good);
		bad = m_pControl->m_resT.m_badNum;
		SetDlgItemInt(IDC_BAD_NUM, bad);
		if (all == 0)
		{
			str = _T("0.00%");
		}
		else{
			str.Format(_T("%.2f%%"), good * 100.0 / all);
		}
		SetDlgItemText(IDC_PERCENT, str);
		//ͨ��
		for (INT i = 0; i < num; ++i)
		{
			//1#
			all = m_pControl->m_modbus[i].m_res1.m_allNum;
			SetDlgItemInt(IDC_ALL_NUM1 + i * 2, all);
			good = m_pControl->m_modbus[i].m_res1.m_goodNum;
			SetDlgItemInt(IDC_GOOD_NUM1 + i * 2, good);
			bad = m_pControl->m_modbus[i].m_res1.m_badNum;
			SetDlgItemInt(IDC_BAD_NUM1 + i * 2, bad);
			if (all == 0)
			{
				str = _T("0.00%");
			}
			else{
				str.Format(_T("%.2f"), good * 100.0 / all);
			}
			SetDlgItemText(IDC_PERCENT1 + i * 2, str);
			//2#
			all = m_pControl->m_modbus[i].m_res2.m_allNum;
			SetDlgItemInt(IDC_ALL_NUM1 + i * 2 + 1, all);
			good = m_pControl->m_modbus[i].m_res2.m_goodNum;
			SetDlgItemInt(IDC_GOOD_NUM1 + i * 2 + 1, good);
			bad = m_pControl->m_modbus[i].m_res2.m_badNum;
			SetDlgItemInt(IDC_BAD_NUM1 + i * 2 + 1, bad);
			if (all == 0)
			{
				str = _T("0.00%");
			}
			else{
				str.Format(_T("%.2f"), good * 100.0 / all);
			}
			SetDlgItemText(IDC_PERCENT1 + i * 2 + 1, str);
		}
	}
	*/
	return TRUE;
}

void CMainDlg::OnPaint()
{
	CDialogEx::OnPaint();
	/*
	CPaintDC   dc(this);
	CRect   rect;
	GetClientRect(&rect);
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_MAIN);
	//IDB_BITMAP�����Լ���ͼ��Ӧ��ID   
	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		rect.Width(), rect.Height(), SRCCOPY);
	*/
	
}


void CMainDlg::OnBnClickedClear()
{
	m_pDlg->m_motorDlg.ClearData();//���ͳ������
	m_pControl->ComClearData();//�������
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 2000)
	{
		CString str;
		INT all = 0, bad = 0, good = 0;//���� ��Ʒ�� ��Ʒ��
		INT num = CControl::ModBus_Num;
		LONG* data = m_pControl->m_motor.m_data;
		//ͳ��
		//����
		all = (USHORT)m_pControl->m_motor.m_data[P_AllNum] + (USHORT)m_pControl->m_motor.m_data[P_AllNum + 1] * 65536;
		SetDlgItemInt(IDC_M_ALL_NUM, all);
		//��Ʒ��
		bad = (USHORT)m_pControl->m_motor.m_data[P_BadNum] + (USHORT)m_pControl->m_motor.m_data[P_BadNum] * 65536;
		SetDlgItemInt(IDC_M_BAD_NUM, bad);
		if (all == 0)
		{
			str = _T("0.00%");
		}
		else{
			str.Format(_T("%.2f%%"), (all - bad) * 100.0 / all);
		}
		SetDlgItemText(IDC_M_PERCENT, str);
		//�ٶ�
		str.Format(_T("%d��/����"), m_pControl->m_motor.m_speed);
		SetDlgItemText(IDC_M_SPEED, str);

		//ˢ�¸�ѹ���ź�
		updataList();

		//����״̬
		static LONG value[3] = { 0 };
		LONG PData = m_pControl->m_motor.m_isRun;
		if (value[0] != PData)
		{
			value[0] = PData;
			showState(m_start, PData, _T("ֹͣ���"),_T("��ʼ���"));
		}
	}
	if (nIDEvent == 3000)
	{
		++m_runTime;
		CString str;
		str.Format(_T("%d:%d:%d"), m_runTime/3600, (m_runTime%3600)/60, m_runTime % 60);
		SetDlgItemText(IDC_M_TIE2, str);
	}
	CDialogEx::OnTimer(nIDEvent);
}

INT CMainDlg::updataList()
{
	CString str;
	INT* data = NULL;
	//CH1
	{
		data = m_pControl->m_modbus[0].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2fKV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_M_US1, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_M_US2, str);
		//��ѹ
		str.Format(_T("%.2fKV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_M_U1, str);
		str.Format(_T("%.2fKV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_M_U2, str);
		//й©��ѹ
		str.Format(_T("%.2fV"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL1, str);
		str.Format(_T("%.2fV"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL2, str);
		//й©����
		str.Format(_T("%.2fV"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp1, str);
		str.Format(_T("%.2fV"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp2, str);
		//й©����
		str.Format(_T("%.2fV"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown1, str);
		str.Format(_T("%.2fV"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown2, str);
		//������
		SetDlgItemInt(IDC_M_OUT1, m_pControl->m_modbus[0].m_res1.m_badNum);
		SetDlgItemInt(IDC_M_OUT2, m_pControl->m_modbus[0].m_res2.m_badNum);
	}
	//CH2
	{
		data = m_pControl->m_modbus[1].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2fKV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_M_US3, str);
		str.Format(_T("%.2fKV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_M_US4, str);
		//��ѹ
		str.Format(_T("%.2fKV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_M_U3, str);
		str.Format(_T("%.2fKV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_M_U4, str);
		//й©��ѹ
		str.Format(_T("%.2fV"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL3, str);
		str.Format(_T("%.2fV"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL4, str);
		//й©����
		str.Format(_T("%.2fV"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp3, str);
		str.Format(_T("%.2fV"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp4, str);
		//й©����
		str.Format(_T("%.2fV"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown3, str);
		str.Format(_T("%.2fV"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown4, str);
		//������
		SetDlgItemInt(IDC_M_OUT3, m_pControl->m_modbus[1].m_res1.m_badNum);
		SetDlgItemInt(IDC_M_OUT4, m_pControl->m_modbus[1].m_res2.m_badNum);
	}
	//CH3
	{
		data = m_pControl->m_modbus[2].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2fKV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_M_US5, str);
		str.Format(_T("%.2fKV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_M_US6, str);
		//��ѹ
		str.Format(_T("%.2fKV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_M_U5, str);
		str.Format(_T("%.2fKV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_M_U6, str);
		//й©��ѹ
		str.Format(_T("%.2fV"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL5, str);
		str.Format(_T("%.2fV"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_M_UL6, str);
		//й©����
		str.Format(_T("%.2fV"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp5, str);
		str.Format(_T("%.2fV"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LUp6, str);
		//й©����
		str.Format(_T("%.2fV"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown5, str);
		str.Format(_T("%.2fV"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_M_LDown6, str);

		//������
		SetDlgItemInt(IDC_M_OUT5, m_pControl->m_modbus[2].m_res1.m_badNum);
		SetDlgItemInt(IDC_M_OUT6, m_pControl->m_modbus[2].m_res2.m_badNum);
	}
	return TRUE;
}

BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
	ON_EVENT(CMainDlg, IDC_M_RUN, DISPID_CLICK, CMainDlg::ClickMRun, VTS_NONE)
	ON_EVENT(CMainDlg, IDC_M_RUN, DISPID_DBLCLICK, CMainDlg::DblClickMRun, VTS_NONE)
	ON_EVENT(CMainDlg, IDC_M_SPEED, DISPID_CLICK, CMainDlg::ClickMSpeed, VTS_NONE)
	ON_EVENT(CMainDlg, IDC_M_RESTOR, DISPID_CLICK, CMainDlg::ClickMRestor, VTS_NONE)
END_EVENTSINK_MAP()

//��ʾ��ť״̬
INT CMainDlg::showState(CDLF_Button& button,
	INT value, CString name1, CString name2)
{
	BSTR bstrText;
	if (value == TRUE)
	{
		bstrText = ::SysAllocString(_T("ˮ��_��"));
		button.SetBackName(&bstrText);
		button.SetWindowTextW(name1);
	}
	else if (value == FALSE)
	{
		bstrText = ::SysAllocString(_T("ˮ��_��"));
		button.SetBackName(&bstrText);
		button.SetWindowTextW(name2);
	}
	return TRUE;
}

void CMainDlg::ClickMRun()
{
	BSTR test = _T("1");
	CTime tiStart = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("%02d:%02d:%02d"), tiStart.GetHour(), tiStart.GetMinute(), tiStart.GetSecond());
	INT ID = 0;
	if (m_pControl->m_isStart == FALSE)
	{
		if (m_pControl->ComStart())
		{
			
			test = _T("ˮ��_��");
			m_start.SetBackName(&test);
			m_start.SetWindowText(_T("ֹͣ���"));
			SetDlgItemText(IDC_M_TIS, str);
			
			m_runTime = 0;//����ʱ��
			SetTimer(3000, 1000, NULL);
		}
	}
	else
	{
		if (m_pControl->ComStop())
		{
			
			test = _T("ˮ��_��");
			m_start.SetBackName(&test);
			m_start.SetWindowText(_T("��ʼ���"));
			SetDlgItemText(IDC_M_TIE, str);	
			KillTimer(3000);
		}
	}
	//::SysFreeString(test);
}


void CMainDlg::DblClickMRun()
{
	ClickMRun();
}



void CMainDlg::ClickMSpeed()
{
	ParamStruct data;
	data.m_max = 120;
	CSetValueDlg setDlg;
	if (setDlg.showDlg(data) == IDYES)
	{
		LONG speed = data;
		m_pDlg->m_motorDlg.ChSpeed(speed);
	}
}


void CMainDlg::ClickMRestor()
{
	m_pControl->m_motor.ComResetErr();
}


HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetBkMode(TRANSPARENT);
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMainDlg::OnBnClickedTest()
{
	for (INT i = 0; i < 3; ++i)
	{
		m_pControl->m_modbus[i].m_startFlag = TRUE;
	}
}
