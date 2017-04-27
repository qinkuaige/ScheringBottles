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
	}

	m_camera->captureImages(1);
	CImage* imge = m_camera->get_image();
   // CImage* imge = new CImage;
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


