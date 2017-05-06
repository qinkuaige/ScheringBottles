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
	ON_BN_CLICKED(IDC_BUTTON3, &CameraInterface::return_button)
	ON_WM_SIZE()
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
		m_camera = new Camera(1);
		m_camera->init();
	}
	m_camera->captureImages(6);
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




void CameraInterface::return_button()
{
	m_pParentWnd->ShowWindow(SW_MAXIMIZE);
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	m_pParentWnd->MoveWindow(&rcWorkArea);
	this->ShowWindow(SW_HIDE);
}


void CameraInterface::OnSize(UINT nType, int cx, int cy)
{
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		float fsp[2];
		POINT Newp; //获取现在对话框的大小
		CRect recta;
		GetClientRect(&recta); //取客户区大小   
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / m_oldSize.x;
		fsp[1] = (float)Newp.y / m_oldSize.y;
		CRect Rect;
		int woc;
		CPoint m_oldSizeTLPoint, TLPoint;
		CPoint m_oldSizeBRPoint, BRPoint;
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD);
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			m_oldSizeTLPoint = Rect.TopLeft();
			TLPoint.x = long(m_oldSizeTLPoint.x*fsp[0]);
			TLPoint.y = long(m_oldSizeTLPoint.y*fsp[1]);
			m_oldSizeBRPoint = Rect.BottomRight();
			BRPoint.x = long(m_oldSizeBRPoint.x *fsp[0]);
			BRPoint.y = long(m_oldSizeBRPoint.y *fsp[1]);
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}

		m_oldSize = Newp;
	}
	CDialogEx::OnSize(nType, cx, cy);

}


BOOL CameraInterface::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	GetClientRect(&rect); //取客户区大小   
	m_oldSize.x = rect.right - rect.left;
	m_oldSize.y = rect.bottom - rect.top;
	return TRUE;  // return TRUE unless you set the focus to a control
}
