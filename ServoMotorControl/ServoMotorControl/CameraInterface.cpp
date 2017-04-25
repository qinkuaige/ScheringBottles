// CameraInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "CameraInterface.h"
#include "afxdialogex.h"


// CameraInterface �Ի���

IMPLEMENT_DYNAMIC(CameraInterface, CDialogEx)

CameraInterface::CameraInterface(CWnd* pParent )
	: CDialogEx(CameraInterface::IDD, pParent)
{

}

CameraInterface::~CameraInterface()
{
}

void CameraInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CameraInterface, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CameraInterface::StartCollecting)
	ON_BN_CLICKED(IDC_BUTTON2, &CameraInterface::EndAcquisition)
END_MESSAGE_MAP()




void CameraInterface::StartCollecting()
{
	
}


void CameraInterface::EndAcquisition()
{
	
}
