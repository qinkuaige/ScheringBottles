// ParamDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "ParamDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CParamDlg �Ի���

IMPLEMENT_DYNAMIC(CParamDlg, CDialogEx)
 
CParamDlg::CParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParamDlg::IDD, pParent)
{

}

CParamDlg::~CParamDlg()
{
}

void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialogEx)
	ON_STN_CLICKED(IDC_P_US1, &CParamDlg::OnStnClickedPUs1)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_P_US2, &CParamDlg::OnStnClickedPUs2)
	ON_STN_CLICKED(IDC_P_US3, &CParamDlg::OnStnClickedPUs3)
	ON_STN_CLICKED(IDC_P_US4, &CParamDlg::OnStnClickedPUs4)
	ON_STN_CLICKED(IDC_P_LUp1, &CParamDlg::OnStnClickedPLup1)
	ON_STN_CLICKED(IDC_P_LUp2, &CParamDlg::OnStnClickedPLup2)
	ON_STN_CLICKED(IDC_P_LUp3, &CParamDlg::OnStnClickedPLup3)
	ON_STN_CLICKED(IDC_P_LUp4, &CParamDlg::OnStnClickedPLup4)
	ON_STN_CLICKED(IDC_P_LDown1, &CParamDlg::OnStnClickedPLdown1)
	ON_STN_CLICKED(IDC_P_LDown2, &CParamDlg::OnStnClickedPLdown2)
	ON_STN_CLICKED(IDC_P_LDown3, &CParamDlg::OnStnClickedPLdown3)
	ON_STN_CLICKED(IDC_P_LDown4, &CParamDlg::OnStnClickedPLdown4)
	ON_STN_CLICKED(IDC_P_LMD1, &CParamDlg::OnStnClickedPLmd1)
	ON_STN_CLICKED(IDC_P_LMD2, &CParamDlg::OnStnClickedPLmd2)
	ON_STN_CLICKED(IDC_P_LMD3, &CParamDlg::OnStnClickedPLmd3)
	ON_STN_CLICKED(IDC_P_LMD4, &CParamDlg::OnStnClickedPLmd4)
	ON_BN_CLICKED(IDC_RECIPE_DLG, &CParamDlg::OnBnClickedRecipeDlg)
	ON_STN_CLICKED(IDC_P_US6, &CParamDlg::OnStnClickedPUs6)
	ON_STN_CLICKED(IDC_P_US5, &CParamDlg::OnStnClickedPUs5)
	ON_STN_CLICKED(IDC_P_LUp5, &CParamDlg::OnStnClickedPLup5)
	ON_STN_CLICKED(IDC_P_LUp6, &CParamDlg::OnStnClickedPLup6)
	ON_STN_CLICKED(IDC_P_LDown5, &CParamDlg::OnStnClickedPLdown5)
	ON_STN_CLICKED(IDC_P_LDown6, &CParamDlg::OnStnClickedPLdown6)
	ON_STN_CLICKED(IDC_P_LMD5, &CParamDlg::OnStnClickedPLmd5)
	ON_STN_CLICKED(IDC_P_LMD6, &CParamDlg::OnStnClickedPLmd6)
END_MESSAGE_MAP()


// CParamDlg ��Ϣ�������

//��������
INT CParamDlg::initDialog(CDetectionDlg* parentdlg)
{
	Create(IDD, parentdlg);//��������
	m_pDlg = parentdlg;
	m_pControl = &parentdlg->m_control;
	return TRUE;
}

//��ʾ����
INT CParamDlg::showDialog(UINT dialogID)
{
	if (dialogID == IDD)
	{
		SetTimer(2000, 300, NULL);
		ShowWindow(SW_SHOW);
	}
	else
	{
		KillTimer(2000);
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}


void CParamDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 2000)
	{
		updataList();
	}
	CDialogEx::OnTimer(nIDEvent);
}

INT CParamDlg::updataList()
{
	CString str;
	INT* data = NULL;
	//CH1
	{
		data = m_pControl->m_modbus[0].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US1, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US2, str);
		//��ѹ
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U1, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U2, str);
		//й©��ѹ
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL1, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL2, str);
		//й©����
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp1, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp2, str);
		//й©����
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown1, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown2, str);
		//�Ŵ���
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD1, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD2, str);
	}

	{
		data = m_pControl->m_modbus[1].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US3, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US4, str);
		//��ѹ
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U3, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U4, str);
		//й©��ѹ
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL3, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL4, str);
		//й©����
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp3, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp4, str);
		//й©����
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown3, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown4, str);
		//�Ŵ���
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD3, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD4, str);
	}
	{
		data = m_pControl->m_modbus[2].m_data;
		//��ѹ�趨ֵ
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US5, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US6, str);
		//��ѹ
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U5, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U6, str);
		//й©��ѹ
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL5, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL6, str);
		//й©����
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp5, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp6, str);
		//й©����
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown5, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown6, str);
		//�Ŵ���
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD5, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD6, str);
	}
	return TRUE;
}

//�޸Ĳ���
INT CParamDlg::changParam(CString name, INT sub, INT ParamID, const UINT coefficient)
{
	ParamStruct data;
	data.m_name = name;
	CSetValueDlg setDlg;
	if (setDlg.showDlg(data) == IDYES)
	{
		LONG value = (double)data  * (LONG)coefficient;
		m_pControl->m_modbus[sub].ComSetParam(ParamID, value);
	}
	return TRUE;
}

void CParamDlg::OnStnClickedPUs1()
{
	changParam(_T("CH1���õ�ѹ"), 0, U_SET1);
}

void CParamDlg::OnStnClickedPUs2()
{
	changParam(_T("CH2���õ�ѹ"), 0, U_SET2);
}


void CParamDlg::OnStnClickedPUs3()
{
	changParam(_T("CH3���õ�ѹ"), 1, U_SET1);
}


void CParamDlg::OnStnClickedPUs4()
{
	changParam(_T("CH4���õ�ѹ"), 1, U_SET2);
}


void CParamDlg::OnStnClickedPUs5()
{
	changParam(_T("CH5���õ�ѹ"), 2, U_SET1);
}

void CParamDlg::OnStnClickedPUs6()
{
	changParam(_T("CH6���õ�ѹ"), 2, U_SET2);
}


void CParamDlg::OnStnClickedPLup1()
{
	changParam(_T("CH1й©��ѹ����"), 0, UpLine1);
}


void CParamDlg::OnStnClickedPLup2()
{
	changParam(_T("CH2й©��ѹ����"), 0, UpLine2);
}


void CParamDlg::OnStnClickedPLup3()
{
	changParam(_T("CH3й©��ѹ����"), 1, UpLine1);
}


void CParamDlg::OnStnClickedPLup4()
{
	changParam(_T("CH3й©��ѹ����"), 1, UpLine2);
}

void CParamDlg::OnStnClickedPLup5()
{
	changParam(_T("CH4й©��ѹ����"), 2, UpLine1);
}


void CParamDlg::OnStnClickedPLup6()
{
	changParam(_T("CH4й©��ѹ����"), 2, UpLine2);
}



void CParamDlg::OnStnClickedPLdown1()
{
	changParam(_T("CH1й©��ѹ����"), 0, DownLine1);
}


void CParamDlg::OnStnClickedPLdown2()
{
	changParam(_T("CH2й©��ѹ����"), 0, DownLine2);
}


void CParamDlg::OnStnClickedPLdown3()
{
	changParam(_T("CH3й©��ѹ����"), 1, DownLine1);
}


void CParamDlg::OnStnClickedPLdown4()
{
	changParam(_T("CH4й©��ѹ����"), 1, DownLine2);
}


void CParamDlg::OnStnClickedPLdown5()
{
	changParam(_T("CH5й©��ѹ����"), 2, DownLine1);
}


void CParamDlg::OnStnClickedPLdown6()
{
	changParam(_T("CH6й©��ѹ����"), 2, DownLine2);
}


void CParamDlg::OnStnClickedPLmd1()
{
	changParam(_T("CH1й©��ѹ����"), 0, LMD1,1);
}

void CParamDlg::OnStnClickedPLmd2()
{
	changParam(_T("CH2й©��ѹ����"), 0, LMD2,1);
}


void CParamDlg::OnStnClickedPLmd3()
{
	changParam(_T("CH3й©��ѹ����"), 1, LMD1,1);
}


void CParamDlg::OnStnClickedPLmd4()
{
	changParam(_T("CH4й©��ѹ����"), 1, LMD2,1);
}

void CParamDlg::OnStnClickedPLmd5()
{
	changParam(_T("CH5й©��ѹ����"), 2, LMD1,1);
}


void CParamDlg::OnStnClickedPLmd6()
{
	changParam(_T("CH6й©��ѹ����"), 2, LMD2,1);
}

void CParamDlg::OnBnClickedRecipeDlg()
{
	m_pDlg->showDialog(CRecipeDlg::IDD);
}



