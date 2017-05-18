// RecipeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "RecipeDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CRecipeDlg �Ի���

IMPLEMENT_DYNAMIC(CRecipeDlg, CDialogEx)

CRecipeDlg::CRecipeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecipeDlg::IDD, pParent)
{

}

CRecipeDlg::~CRecipeDlg()
{
}

void CRecipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RE_LIST, m_rList);
}


BEGIN_MESSAGE_MAP(CRecipeDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_RE_NAME, &CRecipeDlg::OnEnSetfocusReName)
END_MESSAGE_MAP()


// CRecipeDlg ��Ϣ�������
INT CRecipeDlg::initDialog(CDetectionDlg* parent)
{
	m_pDlg = parent;
	m_pControl = &m_pDlg->m_control;
	Create(IDD, m_pDlg);
	initList();
	loadRecipeName();
	return TRUE;
}

INT CRecipeDlg::showDialog(INT dlgID)
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
INT CRecipeDlg::initList()
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
INT CRecipeDlg::loadRecipeName()
{
	m_rList.DeleteAllItems();
	CSQLRecipe_CH recipe;
	try
	{
		if (recipe.Open())
		{
			INT count = 0;//������
			CString str;
			while (!recipe.IsEOF())
			{
				str.Format(_T("%d"), count + 1);
				m_rList.InsertItem(count, str);//�����к�
				m_rList.SetItemText(count, L_Name, recipe.m_NAME);//�����䷽����
				++count;
				recipe.MoveNext();
			}
		}
	}
	catch (...)
	{
		AfxMessageBox(_T("�����䷽ʧ�ܣ�"));
	}


	return TRUE;
}

BEGIN_EVENTSINK_MAP(CRecipeDlg, CDialogEx)
ON_EVENT(CRecipeDlg, IDC_RE_LOAD, 2, CRecipeDlg::LButtonUpReLoad, VTS_I4 VTS_BSTR VTS_I4)
ON_EVENT(CRecipeDlg, IDC_RE_ADD, 2, CRecipeDlg::LButtonUpReAdd, VTS_I4 VTS_BSTR VTS_I4)
ON_EVENT(CRecipeDlg, IDC_RE_DELETE, 2, CRecipeDlg::LButtonUpReDelete, VTS_I4 VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()


void CRecipeDlg::LButtonUpReLoad(long ID, LPCTSTR addr, long other)
{
	if (m_pControl->m_motor.m_isRun == TRUE)
	{
		AfxMessageBox(_T("�豸�������в��������¼����䷽"));
		return;
	}
	//��ȡѡ����б�����
	INT count = m_rList.GetSelectionMark();
	if (count < 0)
	{
		AfxMessageBox(_T("δѡ���䷽��"));
		return;
	}
	//��ȡ��ѡ����䷽����
	CString name;
	name = m_rList.GetItemText(count, L_Name);
	if (AfxMessageBox(_T("�Ƿ�����䷽��") + name, MB_YESNO) != IDYES)
	{
		return;
	}
	//�����䷽
	for (INT i = 0; i < m_pControl->ModBus_Num; ++i)
	{
		m_pControl->m_modbus[i].ComSetRecipe(name);
	}
	
}


void CRecipeDlg::LButtonUpReAdd(long ID, LPCTSTR addr, long other)
{
	CString name;
	GetDlgItemText(IDC_RE_NAME, name);
	if (name.GetLength() <= 0)
	{
		AfxMessageBox(_T("���������䷽����!"));
		return;
	}
	//������
	INT num = m_rList.GetItemCount();
	{
		CString nOld;
		for (INT i = 0; i < num; ++i)
		{
			nOld = m_rList.GetItemText(i, L_Name);
			if (name == nOld)
			{
				AfxMessageBox(_T("Ҫ��ӵ��䷽���Ѵ��������ظ����!"));
				return;
			}
		}
	}
	if (AfxMessageBox(_T("ȷ��Ҫ����䷽��") + name + _T(" ?"), MB_YESNO) != IDYES)
	{
		return;
	}

	//����䷽
	for (INT i = 0; i < m_pControl->ModBus_Num; ++i)
	{
		m_pControl->m_modbus[i].ComAddRecipe(name);
	}
	loadRecipeName();
}


void CRecipeDlg::LButtonUpReDelete(long ID, LPCTSTR addr, long other)
{
	if (m_pControl->m_motor.m_isRun == TRUE)
	{
		AfxMessageBox(_T("�豸�������в��������¼����䷽"));
		return;
	}
	//��ȡѡ����б�����
	INT count = m_rList.GetSelectionMark();
	if (count < 0)
	{
		AfxMessageBox(_T("δѡ���䷽��"));
		return;
	}
	//��ȡ��ѡ����䷽����
	CString name;
	name = m_rList.GetItemText(count, L_Name);
	if (name == _T("ͨ��"))
	{
		AfxMessageBox(_T("ͨ�� �䷽������ɾ����"));
		return;
	}
	if (AfxMessageBox(_T("�Ƿ�����䷽��") + name, MB_YESNO) != IDYES)
	{
		return;
	}

	//ɾ���䷽
	for (INT i = 0; i < m_pControl->ModBus_Num; ++i)
	{
		m_pControl->m_modbus[i].ComRemoveRecipe(name);
	}
	loadRecipeName();
}


void CRecipeDlg::OnEnSetfocusReName()
{
	//m_pDlg->showKey(CRect(200, 400, 600, 600));
}
