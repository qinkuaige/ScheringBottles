// CameraInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServoMotorControl.h"
#include "CameraInterface.h"
#include "afxdialogex.h"


// CameraInterface �Ի���

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
	//imge->Load(_T("E:\\����\\�ĵ�\\֤����\\blue.jpg"));
	CRect rect;
	CImage * img = new CImage;
	GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);
	Camera::Stretchimage(imge, img,rect.Height(), rect.Width());
	int cx = img->GetWidth();
	int cy = img->GetHeight();
	ScreenToClient(&rect);// ���ͻ���ѡ�е�Picture�ؼ���ʾ�ľ���������
	GetDlgItem(IDC_STATIC1)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);// �������ƶ���Picture
	GetDlgItem(IDC_STATIC1)->GetClientRect(&rect);// ���pictrue�ؼ����ڵľ�������
	CDC *pDC = GetDlgItem(IDC_STATIC1)->GetDC();// ���pictrue�ؼ���DC
	img->Draw(pDC->m_hDC, rect);// ��ͼƬ����Picture�ؼ���ʾ�ľ�������
	ReleaseDC(pDC);// �ͷ�picture�ؼ���DC
	delete img;
	delete imge;
	img = NULL ;
	return;
}


void CameraInterface::EndAcquisition()
{
	
}


