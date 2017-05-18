// SetValueDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "SetValueDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CSetValueDlg �Ի���

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


// CSetValueDlg ��Ϣ�������

//��ʼ������
INT CSetValueDlg::initDlg(CDetectionDlg* pDlg, CRect& rect)
{
	m_pDlg = pDlg;
	return TRUE;
}

//��ʾ����
INT CSetValueDlg::showDlg(ParamStruct& value)
{
	m_value = &value;
	return DoModal();//��ʾ����;
}

//�������õ�ֵ
ParamStruct CSetValueDlg::GetValue()
{
	return *m_value;
}

//���õ�ǰ����
INT CSetValueDlg::PriSetValue(CString value)
{
	CString data;
	GetDlgItemText(IDC_SV_VALUE, data);
	//�����һ��С����������һ��С����ֱ�ӷ���
	if (value == _T(".") && data.Find(_T(".")) != -1)
	{
		return FALSE;
	}
	//����λ���ܶ���6λ
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
			if (data.Find(_T("-")) != -1)//��Ӹ���
			{
				data = data.Right(data.GetLength() - 1);
			}
			else//������еĸ���
			{
				data = _T("-") + data;
			}
		}
	}
	//�����ǰ����0 ���������ֵ����С�����򸲸ǵ���ǰֵ
	else if (data == _T("0") && value != _T("."))
	{
		data = value;
	}
	//������ø���������������������ֵ
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
			AfxMessageBox(_T("��������ݳ���Χ,����������!"));
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

