// RecipeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "RecipeDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CRecipeDlg 对话框

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


// CRecipeDlg 消息处理程序
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

//初始化列表控件
INT CRecipeDlg::initList()
{
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小  
	m_rList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格  
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列  

	m_rList.InsertColumn(L_Num, _T("序号"), LVCFMT_CENTER, 50, 0);
	m_rList.InsertColumn(L_Name, _T("配方名"), LVCFMT_CENTER, rect.Width() - 50, 0);
	
	return TRUE;
}

//加载配方名称
INT CRecipeDlg::loadRecipeName()
{
	m_rList.DeleteAllItems();
	CSQLRecipe_CH recipe;
	try
	{
		if (recipe.Open())
		{
			INT count = 0;//计数器
			CString str;
			while (!recipe.IsEOF())
			{
				str.Format(_T("%d"), count + 1);
				m_rList.InsertItem(count, str);//插入行号
				m_rList.SetItemText(count, L_Name, recipe.m_NAME);//插入配方名称
				++count;
				recipe.MoveNext();
			}
		}
	}
	catch (...)
	{
		AfxMessageBox(_T("加载配方失败！"));
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
		AfxMessageBox(_T("设备正在运行不允许重新加载配方"));
		return;
	}
	//获取选择的列表行数
	INT count = m_rList.GetSelectionMark();
	if (count < 0)
	{
		AfxMessageBox(_T("未选择配方！"));
		return;
	}
	//获取所选择的配方名称
	CString name;
	name = m_rList.GetItemText(count, L_Name);
	if (AfxMessageBox(_T("是否加载配方：") + name, MB_YESNO) != IDYES)
	{
		return;
	}
	//加载配方
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
		AfxMessageBox(_T("请先输入配方名称!"));
		return;
	}
	//查重名
	INT num = m_rList.GetItemCount();
	{
		CString nOld;
		for (INT i = 0; i < num; ++i)
		{
			nOld = m_rList.GetItemText(i, L_Name);
			if (name == nOld)
			{
				AfxMessageBox(_T("要添加的配方名已存在请勿重复添加!"));
				return;
			}
		}
	}
	if (AfxMessageBox(_T("确定要添加配方：") + name + _T(" ?"), MB_YESNO) != IDYES)
	{
		return;
	}

	//添加配方
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
		AfxMessageBox(_T("设备正在运行不允许重新加载配方"));
		return;
	}
	//获取选择的列表行数
	INT count = m_rList.GetSelectionMark();
	if (count < 0)
	{
		AfxMessageBox(_T("未选择配方！"));
		return;
	}
	//获取所选择的配方名称
	CString name;
	name = m_rList.GetItemText(count, L_Name);
	if (name == _T("通用"))
	{
		AfxMessageBox(_T("通用 配方不允许被删除！"));
		return;
	}
	if (AfxMessageBox(_T("是否加载配方：") + name, MB_YESNO) != IDYES)
	{
		return;
	}

	//删除配方
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
