/* 
 *ManageUsers.cpp : ʵ���ļ�
 *�����û� �Ի���
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
	GetClientRect(&rect); //ȡ�ͻ�����С   
	m_windowSize.x = rect.right - rect.left;
	m_windowSize.y = rect.bottom - rect.top;
	//���ڴ�СΪ����
	int cx = GetSystemMetrics(SM_CXSCREEN);//��Ļ���ؿ��  
	int cy = GetSystemMetrics(SM_CYSCREEN);//��Ļ���ظ߶�  
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
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)//�����С�����䶯���������
	{
		float fsp[2];
		POINT WindowSize; //��ȡ���ڶԻ���Ĵ�С
		CRect recta;
		GetClientRect(&recta); //ȡ�ͻ�����С   
		WindowSize.x = recta.right - recta.left;
		WindowSize.y = recta.bottom - recta.top;
		fsp[0] = (float)WindowSize.x / m_windowSize.x;
		fsp[1] = (float)WindowSize.y / m_windowSize.y;
		CRect Rect;
		int woc;
		CPoint m_oldSizeTLPoint, TLPoint; //���Ͻ�
		CPoint m_oldSizeBRPoint, BRPoint; //���½�
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //�г����пؼ�   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
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

//ɾ���û���ť�������
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
