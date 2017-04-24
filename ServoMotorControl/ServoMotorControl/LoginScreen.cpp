#include "stdafx.h"
#include "ServoMotorControl.h"
#include "LoginScreen.h"
#include "afxdialogex.h"
#include "ServoMotorControlDlg.h"
#include "ManageUsers.h"
#include "Encryption.h"
#include "LoginScreen.h"

#include <string.h>


//��¼�Ի���

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

//ע����Ϣ
BEGIN_MESSAGE_MAP(LoginScreen, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &LoginScreen::ManageUsers)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginScreen::Login)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginScreen::Quit)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//��ʼ������
BOOL LoginScreen::OnInitDialog()
{
	m_passwordEdit.SubclassDlgItem(IDC_EDIT2, this);
	//��ʽΪ�ޱ߿���ʽ
	CDialogEx::OnInitDialog();
	DWORD dwStyle = GetStyle();//��ȡ����ʽ    
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;//��λ�뽫����ʽȥ��    
	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);//���ó��µ���ʽ    
	DWORD dwExStyle = GetExStyle();//��ȡ����չ��ʽ    
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;//��λ�뽫����չ��ʽȥ��    
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);//�����µ���չ��ʽ    
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);//����windows���ҵ���ʽ�ı��ˣ�����λ�úʹ�С����ԭ�����䣡
	//��ȡ���ڴ���
	CRect rect;
	GetClientRect(&rect); //ȡ�ͻ�����С   
	m_windowSize.x = rect.right - rect.left;
	m_windowSize.y = rect.bottom - rect.top;
	//���ڴ�СΪ����
	int cx = GetSystemMetrics(SM_CXSCREEN);//��Ļ���ؿ��  
	int cy = GetSystemMetrics(SM_CYSCREEN);//��Ļ���ظ߶�  
	SetWindowPos(NULL, 0, 0, cx, cy, 0);
	auto allUser = UserInformation::getInstance()->get_allUser();
	for (auto pItor = allUser->begin(); pItor != allUser->end(); pItor++)
	{
		m_userNameBox.AddString(pItor->first);
	}

	m_userNameBox.SetCurSel(0);
	return TRUE;
}



//�����û�
void LoginScreen::ManageUsers()
{
	CString  userName = _T("");
	auto sel = m_userNameBox.GetCurSel();
	m_userNameBox.GetLBText(sel, userName);
	if (UserInformation::getInstance()->set_user(userName) == -1)
	{
		AfxMessageBox(_T("û�д��û�!"));
		return;
	}
	CString str;
	GetDlgItemText(IDC_EDIT2, str);
	if(!UserInformation::getInstance()->verifyPassword(str))
	{
		AfxMessageBox(_T("�������!"));
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

//��¼
void LoginScreen::Login()
{
	CString  userName = _T("");
	auto sel = m_userNameBox.GetCurSel();
	m_userNameBox.GetLBText(sel, userName);
	if (UserInformation::getInstance()->set_user(userName) == -1)
	{
		AfxMessageBox(_T("û�д��û�!"));
		return;
	}
	CString str;
	GetDlgItemText(IDC_EDIT2, str);
	if (!UserInformation::getInstance()->verifyPassword(str))
	{
		AfxMessageBox(_T("�������!"));
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

//�˳�
void LoginScreen::Quit()
{
	CDialogEx::OnClose();
	exit(0);
}

//��ҳ���С�ı�ʱ���ռ�����ҳ��Ĵ�С���ı�
void LoginScreen::OnSize(UINT nType, int cx, int cy)
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
		CPoint OldTLPoint, TLPoint; //���Ͻ�
		CPoint OldBRPoint, BRPoint; //���½�
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //�г����пؼ�   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
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
