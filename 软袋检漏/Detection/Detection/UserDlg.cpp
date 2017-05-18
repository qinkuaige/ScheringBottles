// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CUserDlg 对话框

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserDlg::IDD, pParent)
{
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	m_path = sPath.Left(nPos);
	//
	m_isShow = 1;
}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_U_NAME, m_nameList);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_EN_SETFOCUS(IDC_U_PW, &CUserDlg::OnEnSetfocusUPw)
	ON_EN_CHANGE(IDC_U_PW, &CUserDlg::OnEnChangeUPw)
END_MESSAGE_MAP()


// CUserDlg 消息处理程序
INT CUserDlg::initDialog(CDetectionDlg* parentDlg)
{
	m_pDlg = parentDlg;
	m_pControl = &parentDlg->m_control;
	return TRUE;
}

INT CUserDlg::showDialog(INT dlgID)
{
	PriReadIni();//读取配置文件是否显示
	if (m_isShow == TRUE)
	{
		return DoModal();
	}
	return r_Code;
}

//读取配置文件
INT CUserDlg::PriReadIni()
{
	CString filePath = _T("user.ini");
	filePath = m_path + _T("\\ini\\") + filePath;
	CFileFind find;
	if (find.FindFile(filePath) == FALSE)
	{
		AfxMessageBox(_T("参数文件不存在:") + filePath);
		return FALSE;
	}
	//是否显示登录窗口
	m_isShow = GetPrivateProfileInt(_T("main"), _T("登录窗口"), 1, filePath);
	return TRUE;
}

//读取数据库数据
INT CUserDlg::PriReadSQL()
{

	return TRUE;
}

//退出程序
INT CUserDlg::PriOut()
{
	exit(0);
	return TRUE;
}

//验证密码是否正确
INT CUserDlg::PriPassWord()
{
	//最高权限
	CString passWrod;
	GetDlgItemText(IDC_U_PW, passWrod);
	if (passWrod == _T("2008-ZZ"))
	{
		return r_Code;
	}
	//判断用户名是否为空
	if (m_nameList.GetCurSel() < 0)
	{
		AfxMessageBox(_T("请先选择用户名！"));
		return FALSE;
	}
	//获取用户名 
	CSQLUser user;
	CString name;
	//获取用户名
	m_nameList.GetWindowTextW(name);
	//获取数据库中对应用户名的密码
	CString sql = _T("SELECT * FROM ")
		+ user.m_tableName +
		_T(" WHERE NAME = '") + name + _T("';");
	if (user.Open(NULL, sql))
	{
		CString passWrod;
		GetDlgItemText(IDC_U_PW, passWrod);
		if (passWrod == user.m_PW)
		{
			INT root = user.m_ROOT;
			user.Close();
			return root;
		}
		else
		{
			AfxMessageBox(_T("密码错误！"));
			return r_Null;
		}
	}
	else
	{
		AfxMessageBox(_T("用户名或者密码错误！"));
	}
	return r_Null;
}

void CUserDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow == TRUE)
	{
		//打开数据库
		if (m_sqlUser.IsOpen() == FALSE)
		{
			m_sqlUser.Open();
		}
		//读取用户名
		while (!m_sqlUser.IsEOF())
		{
			m_nameList.AddString(m_sqlUser.m_NAME);
			m_sqlUser.MoveNext();
		}
		m_nameList.SetCurSel(0);
	}
}

BEGIN_EVENTSINK_MAP(CUserDlg, CDialogEx)
	ON_EVENT(CUserDlg, IDC_U_OUT, DISPID_CLICK, CUserDlg::ClickUOut, VTS_NONE)
	ON_EVENT(CUserDlg, IDC_U_OK, DISPID_CLICK, CUserDlg::ClickUOk, VTS_NONE)
END_EVENTSINK_MAP()


void CUserDlg::ClickUOut()
{
	PriOut();
}


void CUserDlg::OnEnSetfocusUPw()
{
	CRect rect(5, 299, 500, 595);
	CRect rectW;
	m_pDlg->GetWindowRect(&rectW);
	rect.left += rectW.left;
	rect.top += rectW.top;
	rect.right += rectW.left;
	rect.bottom += rectW.top;

	//打开屏幕键盘
	CWnd* m_pKey = FindWindow(NULL, _T("屏幕键盘"));
	if (!m_pKey)
	{
		ShellExecute(NULL, _T("open"), m_path + _T("\\osk.exe"), NULL, NULL, SW_SHOWNORMAL);
		m_pKey = FindWindow(NULL, _T("屏幕键盘"));
		m_pKey->SetWindowPos((CWnd*)HWND_TOPMOST, 0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		m_pKey->ShowWindow(SW_RESTORE);
	}
	m_pKey->MoveWindow(rect);
	
}

void CUserDlg::ClickUOk()
{
	INT root = PriPassWord();
	if (root != r_Null)
	{
		CWnd* m_pKey = FindWindow(NULL, _T("屏幕键盘"));
		m_pKey->ShowWindow(SW_MINIMIZE);
		EndDialog(root);
	}
}


void CUserDlg::OnEnChangeUPw()
{
	
}
