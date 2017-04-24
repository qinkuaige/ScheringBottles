// AddUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "AddUser.h"
#include "afxdialogex.h"
#include "UserInformation.h"


// AddUser �Ի���

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


// AddUser ��Ϣ�������


BOOL AddUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	size_t size = sizeof Permissions / sizeof Permissions[0];
	//��ʼ��Ȩ���б�
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
		AfxMessageBox(_T("��������������벻һ�£�����������!"));
		return;
	}
	auto ret = UserInformation::getInstance()->addUser(user);
	switch(ret)
	{
	case 1 :
		SetDlgItemText(IDC_EDIT1, _T(""));
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
		AfxMessageBox(_T("�������û���"));
		return;
	case 2:
		SetDlgItemText(IDC_EDIT1, _T(""));
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
		AfxMessageBox(_T("���û����Ѿ�����!"));
		return;
	case 3:
		AfxMessageBox(_T("���Ȩ�޲���!"));
		return;
	default:
		break;
	}
}
