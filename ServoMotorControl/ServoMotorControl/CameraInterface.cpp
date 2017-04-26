// CameraInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "CameraInterface.h"
#include "afxdialogex.h"


// CameraInterface 对话框

IMPLEMENT_DYNAMIC(CameraInterface, CDialogEx)

CameraInterface::CameraInterface(CWnd* pParent )
: CDialogEx(CameraInterface::IDD, pParent), m_camera(NULL)
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
	ON_WM_TIMER()
END_MESSAGE_MAP()




void CameraInterface::StartCollecting()
{
	if (m_camera == NULL)
	{
		m_camera = new Camera;
		m_camera->init();
		SetTimer(1, 50, NULL);
	}
}


void CameraInterface::EndAcquisition()
{
	if (m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
}


void CameraInterface::OnTimer(UINT_PTR nIDEvent)
{
	
	m_camera->captureImages(GetDlgItem(IDC_STATIC1));
	CDialogEx::OnTimer(nIDEvent);
}
