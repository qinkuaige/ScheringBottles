#include "stdafx.h"
#include "ServoMotorControl.h"
#include "CameraInterface.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CameraInterface, CDialogEx)

CameraInterface::CameraInterface(CWnd* pParent )
: CDialogEx(CameraInterface::IDD, pParent), m_camera(NULL)
{
	
}

CameraInterface::~CameraInterface()
{
	if (m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
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

//图像采集线程
DWORD WINAPI CameraInterface::imageAcquisitionThread(LPVOID pParam)
{
	CameraInterface* camera = (CameraInterface*)pParam;
	camera->collect();
	return 1;
}

void CameraInterface::collect()
{
	if (m_camera == NULL)
	{
		m_camera = new Camera;
		m_camera->init();
	}
	m_camera->captureImages(6);
	Sleep(5000);

}

void CameraInterface::StartCollecting()
{
	m_acquistionHandle = ::CreateThread(NULL, 0, CameraInterface::imageAcquisitionThread, this, 0, NULL);

	
}


void CameraInterface::EndAcquisition()
{
	if (m_camera == NULL)
	{
		return;
	}
	CImage* image = m_camera->get_image();
	if (image == NULL)
	{
		return;
	}

	
	

	RECT rect;
	int cx = image->GetWidth();
	int cy = image->GetHeight();
	CWnd *pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetClientRect(&rect);
	CDC *pDC = pWnd->GetDC();// 获得pictrue控件的DC
	pDC->FillSolidRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, RGB(240, 240, 240));

	image->Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);// 释放picture控件的DC
	if (image != NULL)
	{
		delete image;
		image = NULL;
	}
}


