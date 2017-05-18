
// DetectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "DetectionDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDetectionDlg �Ի���



CDetectionDlg::CDetectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetectionDlg::IDD, pParent)
	, m_pKey(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	m_path = sPath.Left(nPos);


}

void CDetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDetectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDetectionDlg ��Ϣ�������

BOOL CDetectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//GetDlgItem(IDC_START2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STOP6)->ShowWindow(SW_HIDE);
	//
	
	CenterWindow();//���ھ���
	initDlg();//��ʼ��������
	m_control.ComInit(this);//��ʼ���߼���
	m_mainDlg.showDlg(m_mainDlg.IDD);

	//�����豸
	m_control.ComConnect();//�����豸
	GetDlgItem(IDC_ONLINE1)->EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		/*
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);
		//IDB_BITMAP�����Լ���ͼ��Ӧ��ID   
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			rect.Width(), rect.Height(), SRCCOPY);
		*/
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ʼ���Ӵ���
INT CDetectionDlg::initDlg()
{
	m_mainDlg.initDlg(this);//�����
	m_reportDlg.initDialog(this);//��ʷ��¼
	m_motorDlg.initDialog(this);//�ŷ�
	m_paramDlg.initDialog(this);//�����޸�
	m_userDlg.initDialog(this);//��¼����
	m_errInfoDlg.initDialog(this);//������Ϣ����
	m_mReportDLg.initDialog(this, CPoint(140 * 2, 260 * 2));//��ʷ���ݲ˵�����
	m_recipeDlg.initDialog(this);//�䷽�޸Ĵ���


	//��ʾ��¼����
	//if (m_userDlg.showDialog(TRUE) == r_Null)
	{
		//m_control.ComExit();
	}
	return TRUE;
}

//��ʾ����
INT CDetectionDlg::showDialog(INT dlgID)
{
	m_mainDlg.showDlg(dlgID);
	m_reportDlg.showDialog(dlgID);
	m_motorDlg.showDialog(dlgID);
	m_paramDlg.showDialog(dlgID);//�����޸�
	m_errInfoDlg.showDialog(dlgID);//������Ϣ����
	m_recipeDlg.showDialog(dlgID);//�䷽�޸Ĵ���
	showMenu(dlgID);//��ʾ�˵�����
	return TRUE;
}

//��ʾ�˵�
INT CDetectionDlg::showMenu(INT dlgID)
{
	m_mReportDLg.showDialog(dlgID);//��ʷ���ݲ˵�����
	return TRUE;
}

//��ʾ��Ļ����
INT CDetectionDlg::showKey(CRect rect)
{

	return TRUE;
}

BEGIN_EVENTSINK_MAP(CDetectionDlg, CDialogEx)
ON_EVENT(CDetectionDlg, IDC_ONLINE1, DISPID_CLICK, CDetectionDlg::ClickOnline1, VTS_NONE)
ON_EVENT(CDetectionDlg, IDC_MAIN3, DISPID_CLICK, CDetectionDlg::ClickMain3, VTS_NONE)
ON_EVENT(CDetectionDlg, IDC_MOTOR6, DISPID_CLICK, CDetectionDlg::ClickMotor6, VTS_NONE)
ON_EVENT(CDetectionDlg, IDC_OUT10, DISPID_CLICK, CDetectionDlg::ClickOut10, VTS_NONE)
ON_EVENT(CDetectionDlg, IDC_PARAM5, DISPID_CLICK, CDetectionDlg::ClickParam5, VTS_NONE)
ON_EVENT(CDetectionDlg, IDC_REPORT4, 2, CDetectionDlg::LButtonUpReport4, VTS_I4 VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

//�����豸
void CDetectionDlg::ClickOnline1()
{
	m_control.ComConnect();//�����豸
	GetDlgItem(IDC_ONLINE1)->EnableWindow(FALSE);
}

//��ʾ���ش���
void CDetectionDlg::ClickMain3()
{
	showDialog(m_mainDlg.IDD);
}

//��ʾ�ŷ�����
void CDetectionDlg::ClickMotor6()
{
	if (m_control.m_motor.m_isRun == TRUE)
	{
		AfxMessageBox(_T("����ֹͣ���"));
		return;
	}
	showDialog(m_motorDlg.IDD);
}

//��ʾ�����޸Ĵ���
void CDetectionDlg::ClickParam5()
{
	showDialog(m_paramDlg.IDD);
}


void CDetectionDlg::ClickOut10()
{
	OnOK();
}


void CDetectionDlg::OnDestroy()
{
	m_control.ComDisConnect();
	CDialogEx::OnDestroy();
}




void CDetectionDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		
	}
}


void CDetectionDlg::LButtonUpReport4(long ID, LPCTSTR addr, long other)
{
	showMenu(m_mReportDLg.IDD);
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
