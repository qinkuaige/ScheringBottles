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

	CImage* imge = m_camera->get_image();
	//CImage* imge = new CImage;
	//imge->Load(_T("E:\\资料\\文档\\证件照\\blue.jpg"));
	CRect rect;
	CImage * img = new CImage;
	GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);
	Camera::Stretchimage(imge, img,rect.Height(), rect.Width());
	int cx = img->GetWidth();
	int cy = img->GetHeight();
	ScreenToClient(&rect);// 将客户区选中到Picture控件表示的矩形区域内
	GetDlgItem(IDC_STATIC1)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);// 将窗口移动到Picture
	GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);// 获得pictrue控件所在的矩形区域
	CDC *pDC = GetDlgItem(IDC_STATIC1)->GetDC();// 获得pictrue控件的DC
	img->Draw(pDC->m_hDC, rect);// 将图片画到Picture控件表示的矩形区域
	ReleaseDC(pDC);// 释放picture控件的DC
	delete img;
	delete imge;
	img = NULL ;
	return;
}


void CameraInterface::EndAcquisition()
{
	
}


