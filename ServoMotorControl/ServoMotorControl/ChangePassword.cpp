// ChangePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "ChangePassword.h"
#include "afxdialogex.h"
#include "UserInformation.h"


// �޸����� �Ի���

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


// ChangePassword ��Ϣ�������


BOOL ChangePassword::OnInitDialog()
{
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
	//���ڴ�СΪ����
	int cx = GetSystemMetrics(SM_CXSCREEN);//��Ļ���ؿ��  
	int cy = GetSystemMetrics(SM_CYSCREEN);//��Ļ���ظ߶�  
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
		AfxMessageBox(_T("ԭʼ�������"));
		return;
	}

	if (newPassword != confirmPassword)
	{
		AfxMessageBox(_T("������������벻һ�£�"));
		return;
	}

	UserInformation::getInstance()->changePassword(newPassword);
	return;
}