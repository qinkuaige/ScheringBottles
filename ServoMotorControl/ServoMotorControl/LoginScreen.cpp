#include "stdafx.h"
#include "ServoMotorControl.h"
#include "LoginScreen.h"
#include "afxdialogex.h"
#include "ServoMotorControlDlg.h"
#include "ManageUsers.h"
#include "Encryption.h"
#include "LoginScreen.h"

#include <string.h>


//登录对话框

IMPLEMENT_DYNAMIC(LoginScreen, CDialogEx)

LoginScreen::LoginScreen(CWnd* pParent)
: CDialogEx(LoginScreen::IDD, pParent), m_childWindows(NULL)
, m_passwordEdit(MessageNumberBase + IDC_EDIT2, _T(""))
{
	
}

LoginScreen::~LoginScreen()
{
	if (NULL != m_childWindows)
	{
		delete m_childWindows;
		m_childWindows = NULL;
	}
}

void LoginScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_userNameBox);
}

//注册消息
BEGIN_MESSAGE_MAP(LoginScreen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &LoginScreen::ManageUsers)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginScreen::Login)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginScreen::Quit)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//初始化窗口
BOOL LoginScreen::OnInitDialog()
{
	m_passwordEdit.SubclassDlgItem(IDC_EDIT2, this);
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
	auto allUser = UserInformation::getInstance()->get_allUser();
	for (auto pItor = allUser->begin(); pItor != allUser->end(); pItor++)
	{
		m_userNameBox.AddString(pItor->first);
	}

	m_userNameBox.SetCurSel(0);
	return TRUE;
}



//管理用户
void LoginScreen::ManageUsers()
{
	CString  userName = _T("");
	auto sel = m_userNameBox.GetCurSel();
	m_userNameBox.GetLBText(sel, userName);
	if (UserInformation::getInstance()->set_user(userName) == -1)
	{
		AfxMessageBox(_T("没有此用户!"));
		return;
	}
	CString str;
	GetDlgItemText(IDC_EDIT2, str);
	if(!UserInformation::getInstance()->verifyPassword(str))
	{
		AfxMessageBox(_T("密码错误!"));
		return;
	}
	if (NULL != m_childWindows)
	{
		delete m_childWindows;
	}
	WinExec("cmd.exe /c taskkill /IM osk.exe", SW_HIDE);
	m_childWindows = new ::ManageUsers;
	m_childWindows->Create(IDD_DIALOG3);
	m_childWindows->ShowWindow(SW_MAXIMIZE);
	this->ShowWindow(SW_HIDE);
}

//登录
void LoginScreen::Login()
{
	CString  userName = _T("");
	auto sel = m_userNameBox.GetCurSel();
	m_userNameBox.GetLBText(sel, userName);
	if (UserInformation::getInstance()->set_user(userName) == -1)
	{
		AfxMessageBox(_T("没有此用户!"));
		return;
	}
	CString str;
	GetDlgItemText(IDC_EDIT2, str);
	if (!UserInformation::getInstance()->verifyPassword(str))
	{
		AfxMessageBox(_T("密码错误!"));
		return;
	}
	if (NULL != m_childWindows)
	{
		delete m_childWindows;
	}
	WinExec("cmd.exe /c taskkill /IM osk.exe", SW_HIDE);
	m_childWindows = new CServoMotorControlDlg;
	m_childWindows->Create(IDD_SERVOMOTORCONTROL_DIALOG);
	m_childWindows->ShowWindow(SW_MAXIMIZE);
	this->ShowWindow(SW_HIDE);
}

//退出
void LoginScreen::Quit()
{
	CDialogEx::OnClose();
	exit(0);
}

//当页面大小改变时，空间随着页面的大小而改变
void LoginScreen::OnSize(UINT nType, int cx, int cy)
{
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)//窗体大小发生变动。处理程序
	{
		float fsp[2];
		POINT WindowSize; //获取现在对话框的大小
		CRect recta;
		GetClientRect(&recta); //取客户区大小   
		WindowSize.x = recta.right - recta.left;
		WindowSize.y = recta.bottom - recta.top;
		fsp[0] = (float)WindowSize.x / m_windowSize.x;
		fsp[1] = (float)WindowSize.y / m_windowSize.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //左上角
		CPoint OldBRPoint, BRPoint; //右下角
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]); 
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}

		m_windowSize = WindowSize;
	}
	CDialogEx::OnSize(nType, cx, cy);

}


BOOL LoginScreen::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (message == m_passwordEdit.get_msgID())
	{
		WinExec("osk.exe", SW_NORMAL);
		
	}
	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}


void LoginScreen::OnOK()
{
	this->Login();
}
