// KeyBoard.cpp : 实现文件
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "KeyBoard.h"
#include "afxdialogex.h"



// KeyBoard 对话框

IMPLEMENT_DYNAMIC(KeyBoard, CDialogEx)

KeyBoard::KeyBoard(CWnd* pParent)
: CDialogEx(KeyBoard::IDD, pParent), m_edit(NULL),m_mutex(NULL),m_motor(NULL), m_number(0)
{

}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KeyBoard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &KeyBoard::one)
	ON_BN_CLICKED(IDC_BUTTON2, &KeyBoard::two)
	ON_BN_CLICKED(IDC_BUTTON3, &KeyBoard::three)
	ON_BN_CLICKED(IDC_BUTTON4, &KeyBoard::four)
	ON_BN_CLICKED(IDC_BUTTON5, &KeyBoard::five)
	ON_BN_CLICKED(IDC_BUTTON6, &KeyBoard::six)
	ON_BN_CLICKED(IDC_BUTTON7, &KeyBoard::seven)
	ON_BN_CLICKED(IDC_BUTTON8, &KeyBoard::eight)
	ON_BN_CLICKED(IDC_BUTTON9, &KeyBoard::nine)
	ON_BN_CLICKED(IDC_BUTTON11, &KeyBoard::zero)
	ON_BN_CLICKED(IDC_BUTTON10, &KeyBoard::remove)
	ON_BN_CLICKED(IDC_BUTTON12, &KeyBoard::ok)
	ON_BN_CLICKED(IDC_BUTTON13, &KeyBoard::ok)
END_MESSAGE_MAP()


void KeyBoard::input(const UINT number)
{
	m_number = m_number * 10 + number;
	SetDlgItemInt(IDC_EDIT1, m_number);
}

void KeyBoard::one()
{
	input(1);
}



void KeyBoard::two()
{
	input(2);
}


void KeyBoard::three()
{
	input(3);
}


void KeyBoard::four()
{
	input(4);
}


void KeyBoard::five()
{
	input(5);
}


void KeyBoard::six()
{
	input(6);
}


void KeyBoard::seven()
{
	input(7);
}


void KeyBoard::eight()
{
	input(8);
}


void KeyBoard::nine()
{
	input(9);
}


void KeyBoard::zero()
{
	input(0);
}


void KeyBoard::remove()
{
	m_number = m_number / 10 ;	
	
	if (m_number == 0)
	{
		SetDlgItemText(IDC_EDIT1,_T(""));
		return;
	}
	SetDlgItemInt(IDC_EDIT1, m_number);
}


void KeyBoard::ok()
{
	
	
	
	this->ShowWindow(SW_HIDE);
	if (m_mutex != NULL)
	{
		WaitForSingleObject(m_mutex, INFINITE);
		CString str;
		if (m_number != 0)
		{
			str.Format(_T("%d"), m_number);
			m_edit->SetWindowTextW(str);
			m_motor->SetDevice(m_edit->get_device(), m_number);
		}
		ReleaseMutex(m_mutex);
	}
	m_number = 0;
}


void KeyBoard::OnOK()
{
	this->ok();
}
