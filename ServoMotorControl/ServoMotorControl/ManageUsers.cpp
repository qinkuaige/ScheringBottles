/* 
 *ManageUsers.cpp : 实现文件
 *管理用户 对话框
*/
#include "stdafx.h"
#include "ServoMotorControl.h"
#include "ManageUsers.h"
#include "afxdialogex.h"
#include "AddUser.h"
#include "DeleteUser.h"
#include "ChangePassword.h"

IMPLEMENT_DYNAMIC(ManageUsers, CDialogEx)

ManageUsers::ManageUsers(CWnd* pParent )
	: CDialogEx(ManageUsers::IDD, pParent)
{
	m_chidWindow.clear();
	CDialogEx *window = new AddUser(this);
	m_chidWindow[IDD_DIALOG4] = window;
	window = new DeleteUser(this);
	m_chidWindow[IDD_DIALOG5] = window;
	window = new ChangePassword(this);
	m_chidWindow[IDD_DIALOG6] = window;
	m_childWindow_itor = m_chidWindow.end();
}

ManageUsers::~ManageUsers()
{
	for (auto pItor = m_chidWindow.begin(); pItor != m_chidWindow.end(); pItor++)
	{
		delete pItor->second;
	}
	m_chidWindow.clear();
}

void ManageUsers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ManageUsers, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &ManageUsers::add_user)
	ON_BN_CLICKED(IDC_BUTTON2, &ManageUsers::delete_user)
	ON_BN_CLICKED(IDC_BUTTON3, &ManageUsers::change_password)
	ON_BN_CLICKED(IDC_BUTTON4, &ManageUsers::OpenKeyboard)
END_MESSAGE_MAP()


void ManageUsers::OnClose()
{
	CDialogEx::OnClose();
	exit(0);
}


BOOL ManageUsers::OnInitDialog()
{
	CRect rect;
	GetClientRect(&rect); //取客户区大小   
	m_windowSize.x = rect.right - rect.left;
	m_windowSize.y = rect.bottom - rect.top;
	//窗口大小为满屏
	int cx = GetSystemMetrics(SM_CXSCREEN);//屏幕像素宽度  
	int cy = GetSystemMetrics(SM_CYSCREEN);//屏幕像素高度  
	SetWindowPos(NULL, 0, 0, cx, cy, 0);
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&m_DialogChild);
	ScreenToClient(m_DialogChild);
	for (auto pItor = m_chidWindow.begin(); pItor != m_chidWindow.end(); pItor++)
	{
		pItor->second->Create(pItor->first, this);

	}
	m_childWindow_itor = m_chidWindow.find(IDD_DIALOG4);
	if (m_childWindow_itor == m_chidWindow.end())
	{
		return FALSE;
	}

	m_childWindow_itor->second->MoveWindow(m_DialogChild);
	m_childWindow_itor->second->ShowWindow(SW_SHOW);
	CDialogEx::OnInitDialog();
	return TRUE;
}


void ManageUsers::OnSize(UINT nType, int cx, int cy)
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
		CPoint m_oldSizeTLPoint, TLPoint; //左上角
		CPoint m_oldSizeBRPoint, BRPoint; //右下角
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			m_oldSizeTLPoint = Rect.TopLeft();
			TLPoint.x = long(m_oldSizeTLPoint.x*fsp[0]);
			TLPoint.y = long(m_oldSizeTLPoint.y*fsp[1]);
			m_oldSizeBRPoint = Rect.BottomRight();
			BRPoint.x = long(m_oldSizeBRPoint.x *fsp[0]);
			BRPoint.y = long(m_oldSizeBRPoint.y *fsp[1]);
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}

		m_windowSize = WindowSize;
	}
	CDialogEx::OnSize(nType, cx, cy);
}



void ManageUsers::change_childWindow(UINT wind_id)
{
	if (m_childWindow_itor != m_chidWindow.end())
	{
		m_childWindow_itor->second->ShowWindow(SW_HIDE);
	}
	m_childWindow_itor = m_chidWindow.find(wind_id);
	if (m_childWindow_itor == m_chidWindow.end())
	{
		return;
	}
	m_childWindow_itor->second->MoveWindow(m_DialogChild);
	m_childWindow_itor->second->ShowWindow(SW_SHOW);
}

void ManageUsers::add_user()
{
	change_childWindow(IDD_DIALOG4);
}

//删除用户按钮处理程序
void ManageUsers::delete_user()
{
	change_childWindow(IDD_DIALOG5);
}


void ManageUsers::change_password()
{
	change_childWindow(IDD_DIALOG6);
}


void ManageUsers::OnOK()
{
	//CDialogEx::OnOK();
}




void ManageUsers::OnCancel()
{
	exit(1);
	CDialogEx::OnCancel();
}


void ManageUsers::OpenKeyboard()
{
	WinExec("osk.exe", SW_NORMAL);
}
