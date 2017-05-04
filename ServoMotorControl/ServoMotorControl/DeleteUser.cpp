// DeleteUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "DeleteUser.h"
#include "afxdialogex.h"
#include "UserInformation.h";


// DeleteUser �Ի���

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


// DeleteUser ��Ϣ�������
BOOL DeleteUser::OnInitDialog()
{
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
		AfxMessageBox(_T("û�д��û�!"));
		break;
	case 2:
		AfxMessageBox(_T("���Ȩ�޲���!"));
		break;
	case 3:
		AfxMessageBox(_T("����ʧ��!"));
		break;
	default:
		m_deleteUserBox.DeleteString(sel);
		break;
	}
}
