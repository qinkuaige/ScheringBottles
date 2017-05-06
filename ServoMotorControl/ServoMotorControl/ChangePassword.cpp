#include "stdafx.h"
#include "ServoMotorControl.h"
#include "ChangePassword.h"
#include "afxdialogex.h"
#include "UserInformation.h"

// 修改密码 对话框

IMPLEMENT_DYNAMIC(ChangePassword, CDialogEx)

ChangePassword::ChangePassword(CWnd* pParent)
	: CDialogEx(ChangePassword::IDD, pParent)
{

}


ChangePassword::~ChangePassword()
{
}

void ChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangePassword, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangePassword::ok)
END_MESSAGE_MAP()


// ChangePassword 消息处理程序


BOOL ChangePassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwStyle = GetStyle(); 
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);
	DWORD dwExStyle = GetExStyle();   
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;  
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);  
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	int cx = GetSystemMetrics(SM_CXSCREEN); 
	int cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 5,5, cx, cy, 0);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetLimitText(20);
	return TRUE;  
}


void ChangePassword::ok()
{

	CString  m_oldSizePassword = _T("");
	CString  newPassword = _T("");
	CString  password = _T("");
	CString confirmPassword = _T("");
	GetDlgItemText(IDC_EDIT1, m_oldSizePassword);
	GetDlgItemText(IDC_EDIT2, newPassword);
	GetDlgItemText(IDC_EDIT3, confirmPassword);

	if (!UserInformation::getInstance()->verifyPassword(m_oldSizePassword))
	{
		AfxMessageBox(_T("原始密码错误！"));
		return;
	}

	if (newPassword != confirmPassword)
	{
		AfxMessageBox(_T("两次输入的密码不一致！"));
		return;
	}

	UserInformation::getInstance()->changePassword(newPassword);
	return;
}