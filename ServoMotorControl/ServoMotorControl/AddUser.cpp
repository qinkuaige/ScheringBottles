// AddUser.cpp : 实现文件
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "AddUser.h"
#include "afxdialogex.h"
#include "UserInformation.h"


// AddUser 对话框

IMPLEMENT_DYNAMIC(AddUser, CDialogEx)

AddUser::AddUser(CWnd* pParent)
	: CDialogEx(AddUser::IDD, pParent)
{

}

AddUser::~AddUser()
{
}

void AddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_permisBox);
}


BEGIN_MESSAGE_MAP(AddUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AddUser::OK)
END_MESSAGE_MAP()


// AddUser 消息处理程序


BOOL AddUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//样式为无边框样式
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
	//获取窗口大下
	CRect rect;
	GetClientRect(&rect); //取客户区大小   
	m_windowSize.x = rect.right - rect.left;
	m_windowSize.y = rect.bottom - rect.top;
	//窗口大小为满屏
	int cx = GetSystemMetrics(SM_CXSCREEN);//屏幕像素宽度  
	int cy = GetSystemMetrics(SM_CYSCREEN);//屏幕像素高度  
	SetWindowPos(NULL, 0, 0, cx, cy, 0);
	size_t size = sizeof Permissions / sizeof Permissions[0];
	//初始化权限列表
	for (size_t i = 0; i < size; i++)
	{
		m_permisBox.AddString((CString)Permissions[i]);
	}
	m_permisBox.SetCurSel(0);
	return TRUE; 
}


void AddUser::OK()
{
	User* user = new User;
	CString confirmPassword = _T("");
	GetDlgItemText(IDC_EDIT1, user->name);
	GetDlgItemText(IDC_EDIT2, user->password);
	GetDlgItemText(IDC_EDIT3, confirmPassword);

	auto sel = m_permisBox.GetCurSel();
	m_permisBox.GetLBText(sel, user->permissions);

	if (user->password != confirmPassword)
	{
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
		if (user != NULL)
		{
			delete user;
			user = NULL;
		}
		AfxMessageBox(_T("你两次输入的密码不一致，请重新输入!"));
		return;
	}
	auto ret = UserInformation::getInstance()->addUser(user);
	switch(ret)
	{
	case 1 :
		SetDlgItemText(IDC_EDIT1, _T(""));
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
		AfxMessageBox(_T("请输入用户名"));
		return;
	case 2:
		SetDlgItemText(IDC_EDIT1, _T(""));
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
		AfxMessageBox(_T("该用户名已经存在!"));
		return;
	case 3:
		AfxMessageBox(_T("你的权限不够!"));
		return;
	default:
		break;
	}
}
