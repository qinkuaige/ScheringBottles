
// DetectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "DetectionDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDetectionDlg 对话框



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


// CDetectionDlg 消息处理程序

BOOL CDetectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//GetDlgItem(IDC_START2)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STOP6)->ShowWindow(SW_HIDE);
	//
	
	CenterWindow();//窗口剧中
	initDlg();//初始化窗口类
	m_control.ComInit(this);//初始化逻辑类
	m_mainDlg.showDlg(m_mainDlg.IDD);

	//连接设备
	m_control.ComConnect();//连接设备
	GetDlgItem(IDC_ONLINE1)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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
		//IDB_BITMAP是你自己的图对应的ID   
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			rect.Width(), rect.Height(), SRCCOPY);
		*/
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//初始化子窗口
INT CDetectionDlg::initDlg()
{
	m_mainDlg.initDlg(this);//主监控
	m_reportDlg.initDialog(this);//历史记录
	m_motorDlg.initDialog(this);//伺服
	m_paramDlg.initDialog(this);//参数修改
	m_userDlg.initDialog(this);//登录窗口
	m_errInfoDlg.initDialog(this);//错误信息窗口
	m_mReportDLg.initDialog(this, CPoint(140 * 2, 260 * 2));//历史数据菜单窗口
	m_recipeDlg.initDialog(this);//配方修改窗口


	//显示登录窗口
	//if (m_userDlg.showDialog(TRUE) == r_Null)
	{
		//m_control.ComExit();
	}
	return TRUE;
}

//显示窗口
INT CDetectionDlg::showDialog(INT dlgID)
{
	m_mainDlg.showDlg(dlgID);
	m_reportDlg.showDialog(dlgID);
	m_motorDlg.showDialog(dlgID);
	m_paramDlg.showDialog(dlgID);//参数修改
	m_errInfoDlg.showDialog(dlgID);//错误信息窗口
	m_recipeDlg.showDialog(dlgID);//配方修改窗口
	showMenu(dlgID);//显示菜单窗口
	return TRUE;
}

//显示菜单
INT CDetectionDlg::showMenu(INT dlgID)
{
	m_mReportDLg.showDialog(dlgID);//历史数据菜单窗口
	return TRUE;
}

//显示屏幕键盘
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

//连接设备
void CDetectionDlg::ClickOnline1()
{
	m_control.ComConnect();//连接设备
	GetDlgItem(IDC_ONLINE1)->EnableWindow(FALSE);
}

//显示主控窗口
void CDetectionDlg::ClickMain3()
{
	showDialog(m_mainDlg.IDD);
}

//显示伺服窗口
void CDetectionDlg::ClickMotor6()
{
	if (m_control.m_motor.m_isRun == TRUE)
	{
		AfxMessageBox(_T("请先停止检测"));
		return;
	}
	showDialog(m_motorDlg.IDD);
}

//显示参数修改窗口
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

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
