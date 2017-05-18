// SetValueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "SetValueDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CSetValueDlg 对话框

IMPLEMENT_DYNAMIC(CSetValueDlg, CDialogEx)

CSetValueDlg::CSetValueDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetValueDlg::IDD, pParent)
{

}

CSetValueDlg::~CSetValueDlg()
{
}

void CSetValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetValueDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SV_POINT, &CSetValueDlg::OnBnClickedSvPoint)
	ON_BN_CLICKED(IDC_SV_0, &CSetValueDlg::OnBnClickedSv0)
	ON_BN_CLICKED(IDC_SV_1, &CSetValueDlg::OnBnClickedSv1)
	ON_BN_CLICKED(IDC_SV_2, &CSetValueDlg::OnBnClickedSv2)
	ON_BN_CLICKED(IDC_SV_3, &CSetValueDlg::OnBnClickedSv3)
	ON_BN_CLICKED(IDC_SV_4, &CSetValueDlg::OnBnClickedSv4)
	ON_BN_CLICKED(IDC_SV_5, &CSetValueDlg::OnBnClickedSv5)
	ON_BN_CLICKED(IDC_SV_6, &CSetValueDlg::OnBnClickedSv6)
	ON_BN_CLICKED(IDC_SV_7, &CSetValueDlg::OnBnClickedSv7)
	ON_BN_CLICKED(IDC_SV_8, &CSetValueDlg::OnBnClickedSv8)
	ON_BN_CLICKED(IDC_SV_9, &CSetValueDlg::OnBnClickedSv9)
	ON_BN_CLICKED(IDC_SV_B, &CSetValueDlg::OnBnClickedSvB)
	ON_BN_CLICKED(IDC_SV_C, &CSetValueDlg::OnBnClickedSvC)
	ON_BN_CLICKED(IDC_SV_YES, &CSetValueDlg::OnBnClickedSvYes)
	ON_BN_CLICKED(IDC_SV_NO, &CSetValueDlg::OnBnClickedSvNo)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SV_SUB, &CSetValueDlg::OnBnClickedSvSub)
END_MESSAGE_MAP()


// CSetValueDlg 消息处理程序

//初始化窗口
INT CSetValueDlg::initDlg(CDetectionDlg* pDlg, CRect& rect)
{
	m_pDlg = pDlg;
	return TRUE;
}

//显示窗口
INT CSetValueDlg::showDlg(ParamStruct& value)
{
	m_value = &value;
	return DoModal();//显示窗口;
}

//返回设置的值
ParamStruct CSetValueDlg::GetValue()
{
	return *m_value;
}

//设置当前数据
INT CSetValueDlg::PriSetValue(CString value)
{
	CString data;
	GetDlgItemText(IDC_SV_VALUE, data);
	//如果有一个小数点又输入一个小数点直接返回
	if (value == _T(".") && data.Find(_T(".")) != -1)
	{
		return FALSE;
	}
	//数字位不能多余6位
	INT strLen = data.GetLength();
	if (data.Find(_T("-")))
	{
		strLen -= 1;
	}
	if (data.Find(_T(".")))
	{
		strLen -= 1;
	}
	if (strLen > 6 && value != _T("-"))
	{
		return TRUE;
	}
	INT test = _ttoi(data);
	test = data.GetLength();
	if (value == _T("-"))
	{
		if (_ttof(data) != 0 && data.GetLength() > 0)
		{
			if (data.Find(_T("-")) != -1)//添加负号
			{
				data = data.Right(data.GetLength() - 1);
			}
			else//清除已有的负号
			{
				data = _T("-") + data;
			}
		}
	}
	//如果当前数是0 并且输入的值不是小数点则覆盖掉当前值
	else if (data == _T("0") && value != _T("."))
	{
		data = value;
	}
	//如果不用覆盖则在输入后面加入输入值
	else
	{
		data = data + value;
	}
	SetDlgItemText(IDC_SV_VALUE, data);
	return TRUE;
}

void CSetValueDlg::OnBnClickedSvPoint()
{
	PriSetValue(_T("."));
}

void CSetValueDlg::OnBnClickedSvSub()
{
	PriSetValue(_T("-"));
}


void CSetValueDlg::OnBnClickedSv0()
{
	PriSetValue(_T("0"));
}


void CSetValueDlg::OnBnClickedSv1()
{
	PriSetValue(_T("1"));
}


void CSetValueDlg::OnBnClickedSv2()
{
	PriSetValue(_T("2"));
}


void CSetValueDlg::OnBnClickedSv3()
{
	PriSetValue(_T("3"));
}

void CSetValueDlg::OnBnClickedSv4()
{
	PriSetValue(_T("4"));
}

void CSetValueDlg::OnBnClickedSv5()
{
	PriSetValue(_T("5"));
}

void CSetValueDlg::OnBnClickedSv6()
{
	PriSetValue(_T("6"));
}

void CSetValueDlg::OnBnClickedSv7()
{
	PriSetValue(_T("7"));
}

void CSetValueDlg::OnBnClickedSv8()
{
	PriSetValue(_T("8"));
}

void CSetValueDlg::OnBnClickedSv9()
{
	PriSetValue(_T("9"));
}

void CSetValueDlg::OnBnClickedSvB()
{
	CString data;
	GetDlgItemText(IDC_SV_VALUE, data);
	if (data.GetLength() <= 1)
	{
		data = _T("");
	}
	else
	{
		data = data.Left(data.GetLength() - 1);
	}
	SetDlgItemText(IDC_SV_VALUE, data);
}

void CSetValueDlg::OnBnClickedSvC()
{
	SetDlgItemText(IDC_SV_VALUE, _T("0"));
}

void CSetValueDlg::OnBnClickedSvYes()
{
	CString data;
	GetDlgItemText(IDC_SV_VALUE, data);
	if (m_value->m_max <= m_value->m_min)
	{
		*m_value = data;
	}
	else
	{
		DOUBLE value = _ttof(data);
		if (value <= m_value->m_max && value >= m_value->m_min)
		{
			*m_value = data;
		}
		else
		{
			AfxMessageBox(_T("输入的数据超范围,请重新输入!"));
			SetDlgItemText(IDC_SV_VALUE, _T("0"));
			return;
		}
	}
	EndDialog(IDYES);
}

void CSetValueDlg::OnBnClickedSvNo()
{
	EndDialog(IDNO);
}

void CSetValueDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		CString str = m_value->m_name;
		if (m_value->m_max <= m_value->m_min)
		{
			str.Format(m_value->m_name + _T(" %d~%d"), m_value->m_min, m_value->m_max);
		}
		SetDlgItemText(IDC_SV_TEXT, str);
	}
}

