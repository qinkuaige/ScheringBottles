// DeleteUser.cpp : 实现文件
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "DeleteUser.h"
#include "afxdialogex.h"
#include "UserInformation.h";


// DeleteUser 对话框

IMPLEMENT_DYNAMIC(DeleteUser, CDialogEx)

DeleteUser::DeleteUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(DeleteUser::IDD, pParent)
{

}

DeleteUser::~DeleteUser()
{
}

void DeleteUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_deleteUserBox);
}


BEGIN_MESSAGE_MAP(DeleteUser, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DeleteUser::ok)
END_MESSAGE_MAP()


// DeleteUser 消息处理程序
BOOL DeleteUser::OnInitDialog()
{
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
	SetWindowPos(NULL, 0, 0, cx, cy, 0);
	CDialogEx::OnInitDialog();
	auto endItor = UserInformation::getInstance()->get_allUser()->end();

	const int level = UserInformation::getInstance()->get_level(UserInformation::getInstance()->get_user()->permissions);
	for (map<CString,User*>::const_iterator pItor = UserInformation::getInstance()->get_allUser()->begin(); pItor != endItor; pItor++)
	{
		if (UserInformation::getInstance()->get_level(pItor->second->permissions) < level)
		{
			m_deleteUserBox.AddString(pItor->first);
		}
	}
	return TRUE;
}

void DeleteUser::ok()
{
	const auto sel = m_deleteUserBox.GetCurSel();
	CString   name = _T("");
	m_deleteUserBox.GetLBText(sel, name);
	auto ret = UserInformation::getInstance()->deleteUser(name);

	switch (ret)
	{
	case 1:
		AfxMessageBox(_T("没有此用户!"));
		break;
	case 2:
		AfxMessageBox(_T("你的权限不够!"));
		break;
	case 3:
		AfxMessageBox(_T("操作失败!"));
		break;
	default:
		m_deleteUserBox.DeleteString(sel);
		break;
	}
}
