// ParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "ParamDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CParamDlg 对话框

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


// CParamDlg 消息处理程序

//创建窗口
INT CParamDlg::initDialog(CDetectionDlg* parentdlg)
{
	Create(IDD, parentdlg);//创建窗口
	m_pDlg = parentdlg;
	m_pControl = &parentdlg->m_control;
	return TRUE;
}

//显示窗口
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
		//高压设定值
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US1, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US2, str);
		//高压
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U1, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U2, str);
		//泄漏电压
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL1, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL2, str);
		//泄漏上限
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp1, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp2, str);
		//泄漏下限
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown1, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown2, str);
		//放大倍数
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD1, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD2, str);
	}

	{
		data = m_pControl->m_modbus[1].m_data;
		//高压设定值
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US3, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US4, str);
		//高压
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U3, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U4, str);
		//泄漏电压
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL3, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL4, str);
		//泄漏上限
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp3, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp4, str);
		//泄漏下限
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown3, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown4, str);
		//放大倍数
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD3, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD4, str);
	}
	{
		data = m_pControl->m_modbus[2].m_data;
		//高压设定值
		str.Format(_T("%.2f KV"), data[U_SET1] * 1.0 / 100);
		SetDlgItemText(IDC_P_US5, str);
		str.Format(_T("%.2f KV"), data[U_SET2] * 1.0 / 100);
		SetDlgItemText(IDC_P_US6, str);
		//高压
		str.Format(_T("%.2f KV"), data[U1] * 1.0 / 100);
		SetDlgItemText(IDC_P_U5, str);
		str.Format(_T("%.2f KV"), data[U2] * 1.0 / 100);
		SetDlgItemText(IDC_P_U6, str);
		//泄漏电压
		str.Format(_T("%.2f V"), data[Lou1] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL5, str);
		str.Format(_T("%.2f V"), data[Lou2] * 1.0 / 100);
		SetDlgItemText(IDC_P_UL6, str);
		//泄漏上限
		str.Format(_T("%.2f V"), data[UpLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp5, str);
		str.Format(_T("%.2f V"), data[UpLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LUp6, str);
		//泄漏下限
		str.Format(_T("%.2f V"), data[DownLine1] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown5, str);
		str.Format(_T("%.2f V"), data[DownLine2] * 1.0 / 100);
		SetDlgItemText(IDC_P_LDown6, str);
		//放大倍数
		str.Format(_T("%d"), data[LMD1]);
		SetDlgItemText(IDC_P_LMD5, str);
		str.Format(_T("%d"), data[LMD2]);
		SetDlgItemText(IDC_P_LMD6, str);
	}
	return TRUE;
}

//修改参数
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
	changParam(_T("CH1设置电压"), 0, U_SET1);
}

void CParamDlg::OnStnClickedPUs2()
{
	changParam(_T("CH2设置电压"), 0, U_SET2);
}


void CParamDlg::OnStnClickedPUs3()
{
	changParam(_T("CH3设置电压"), 1, U_SET1);
}


void CParamDlg::OnStnClickedPUs4()
{
	changParam(_T("CH4设置电压"), 1, U_SET2);
}


void CParamDlg::OnStnClickedPUs5()
{
	changParam(_T("CH5设置电压"), 2, U_SET1);
}

void CParamDlg::OnStnClickedPUs6()
{
	changParam(_T("CH6设置电压"), 2, U_SET2);
}


void CParamDlg::OnStnClickedPLup1()
{
	changParam(_T("CH1泄漏电压上限"), 0, UpLine1);
}


void CParamDlg::OnStnClickedPLup2()
{
	changParam(_T("CH2泄漏电压上限"), 0, UpLine2);
}


void CParamDlg::OnStnClickedPLup3()
{
	changParam(_T("CH3泄漏电压上限"), 1, UpLine1);
}


void CParamDlg::OnStnClickedPLup4()
{
	changParam(_T("CH3泄漏电压上限"), 1, UpLine2);
}

void CParamDlg::OnStnClickedPLup5()
{
	changParam(_T("CH4泄漏电压上限"), 2, UpLine1);
}


void CParamDlg::OnStnClickedPLup6()
{
	changParam(_T("CH4泄漏电压上限"), 2, UpLine2);
}



void CParamDlg::OnStnClickedPLdown1()
{
	changParam(_T("CH1泄漏电压下限"), 0, DownLine1);
}


void CParamDlg::OnStnClickedPLdown2()
{
	changParam(_T("CH2泄漏电压下限"), 0, DownLine2);
}


void CParamDlg::OnStnClickedPLdown3()
{
	changParam(_T("CH3泄漏电压下限"), 1, DownLine1);
}


void CParamDlg::OnStnClickedPLdown4()
{
	changParam(_T("CH4泄漏电压下限"), 1, DownLine2);
}


void CParamDlg::OnStnClickedPLdown5()
{
	changParam(_T("CH5泄漏电压下限"), 2, DownLine1);
}


void CParamDlg::OnStnClickedPLdown6()
{
	changParam(_T("CH6泄漏电压下限"), 2, DownLine2);
}


void CParamDlg::OnStnClickedPLmd1()
{
	changParam(_T("CH1泄漏电压下限"), 0, LMD1,1);
}

void CParamDlg::OnStnClickedPLmd2()
{
	changParam(_T("CH2泄漏电压下限"), 0, LMD2,1);
}


void CParamDlg::OnStnClickedPLmd3()
{
	changParam(_T("CH3泄漏电压下限"), 1, LMD1,1);
}


void CParamDlg::OnStnClickedPLmd4()
{
	changParam(_T("CH4泄漏电压下限"), 1, LMD2,1);
}

void CParamDlg::OnStnClickedPLmd5()
{
	changParam(_T("CH5泄漏电压下限"), 2, LMD1,1);
}


void CParamDlg::OnStnClickedPLmd6()
{
	changParam(_T("CH6泄漏电压下限"), 2, LMD2,1);
}

void CParamDlg::OnBnClickedRecipeDlg()
{
	m_pDlg->showDialog(CRecipeDlg::IDD);
}



