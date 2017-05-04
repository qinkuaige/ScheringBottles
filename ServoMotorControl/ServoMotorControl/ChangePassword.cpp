// ChangePassword.cpp : 实现文件
//

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
	DWORD dwStyle = GetStyle();//获取旧样式    
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;//按位与将旧样式去掉    
	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);//设置成新的样式    
	DWORD dwExStyle = GetExStyle();//获取旧扩展样式    
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;//按位与将旧扩展样式去掉    
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);//设置新的扩展样式    
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);//告诉windows：我的样式改变了，窗口位置和大小保持原来不变！
	//窗口大小为满屏
	int cx = GetSystemMetrics(SM_CXSCREEN);//屏幕像素宽度  
	int cy = GetSystemMetrics(SM_CYSCREEN);//屏幕像素高度  
	SetWindowPos(NULL, 5,5, cx, cy, 0);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetLimitText(20);
	return TRUE;  
}


void ChangePassword::ok()
{

	CString  oldPassword = _T("");
	CString  newPassword = _T("");
	CString  password = _T("");
	CString confirmPassword = _T("");
	GetDlgItemText(IDC_EDIT1, oldPassword);
	GetDlgItemText(IDC_EDIT2, newPassword);
	GetDlgItemText(IDC_EDIT3, confirmPassword);

	if (!UserInformation::getInstance()->verifyPassword(oldPassword))
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