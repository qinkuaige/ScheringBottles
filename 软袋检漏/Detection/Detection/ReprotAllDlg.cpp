// ReprotAllDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "ReprotAllDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CReprotAllDlg �Ի���

IMPLEMENT_DYNAMIC(CReprotAllDlg, CDialogEx)

CReprotAllDlg::CReprotAllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReprotAllDlg::IDD, pParent)
{

}

CReprotAllDlg::~CReprotAllDlg()
{
}

void CReprotAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_R_LIST, m_rList);
}


BEGIN_MESSAGE_MAP(CReprotAllDlg, CDialogEx)
END_MESSAGE_MAP()


// CRecipeDlg ��Ϣ�������
INT CReprotAllDlg::initDialog(CDetectionDlg* parent)
{
	m_pDlg = parent;
	m_pControl = &m_pDlg->m_control;
	Create(IDD, m_pDlg);
	initList();
	loadRecipeName();
	return TRUE;
}

INT CReprotAllDlg::showDialog(INT dlgID)
{
	if (dlgID == IDD)
	{

		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}

//��ʼ���б�ؼ�
INT CReprotAllDlg::initList()
{
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	m_rList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������  

	m_rList.InsertColumn(L_Num, _T("���"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(L_Name, _T("�䷽��"), LVCFMT_CENTER, rect.Width() - 50, 0);

	return TRUE;
}

//�����䷽����
INT CReprotAllDlg::loadRecipeName()
{
	
	return TRUE;
}

// CReprotAllDlg ��Ϣ�������
BEGIN_EVENTSINK_MAP(CReprotAllDlg, CDialogEx)
	ON_EVENT(CReprotAllDlg, IDC_R_FIND, DISPID_CLICK, CReprotAllDlg::ClickRFind, VTS_NONE)
END_EVENTSINK_MAP()


void CReprotAllDlg::ClickRFind()
{
	
}
