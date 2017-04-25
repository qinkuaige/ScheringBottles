#include "stdafx.h"
#include "ServoMotorControl.h"
#include "ServoMotorControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CServoMotorControlDlg::CServoMotorControlDlg(CWnd* pParent)
: CDialogEx(CServoMotorControlDlg::IDD, pParent), m_motorState(false), m_camera(NULL)
{
	m_button.clear();
	m_edit.clear();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_board.set_mutex(&m_mutex);
	m_board.set_motor(&m_motor);
	m_mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("memtest"));
	if (m_mutex == NULL)
	{
		m_mutex = CreateMutex(NULL, FALSE, TEXT("memtest"));
	}
}

CServoMotorControlDlg::~CServoMotorControlDlg()
{
	for (auto pItor = m_button.begin(); pItor != m_button.end();pItor++)
	{

		delete(pItor->second);
	}
	m_button.clear();
	for (auto pItor = m_edit.begin(); pItor != m_edit.end(); pItor++)
	{
		delete(pItor->second);
	}
	m_edit.clear();
}

void CServoMotorControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTUTLTYPE1, m_motor);

	add_Control(IDC_BUTTON1, _T("M10"), pDX);
	add_Control(IDC_BUTTON2, _T("M11"), pDX);
	add_Control(IDC_BUTTON3, _T("M12"), pDX);
	add_Control(IDC_BUTTON4, _T("M13"), pDX);
	add_Control(IDC_BUTTON5, _T("M14"), pDX);
	add_Control(IDC_BUTTON6, _T("M15"), pDX);
	add_Control(IDC_BUTTON7, _T("M16"), pDX);
	add_Control(IDC_BUTTON8, _T("M17"), pDX);
	add_Control(IDC_BUTTON9, _T("M18"), pDX);
	add_Control(IDC_BUTTON10, _T("M19"), pDX);
	add_Control(IDC_BUTTON11, _T("M20"), pDX);
	add_Control(IDC_BUTTON12, _T("M21"), pDX);
	add_Control(IDC_BUTTON13, _T("M22"), pDX);
	add_Control(IDC_BUTTON14, _T("M23"), pDX);
	add_Control(IDC_BUTTON15, _T("M24"), pDX);
	add_Control(IDC_BUTTON16, _T("M25"), pDX);
	add_Control(IDC_BUTTON17, _T("M26"), pDX);
	add_Control(IDC_BUTTON18, _T("M27"), pDX);
	add_Control(IDC_BUTTON19, _T("M28"), pDX);
	add_Control(IDC_BUTTON20, _T("M29"), pDX);
	add_Control(IDC_BUTTON29, _T("M100"), pDX);
	add_Control(IDC_BUTTON30, _T("M101"), pDX);
	add_Control(IDC_BUTTON31, _T("M102"), pDX);
	add_Control(IDC_BUTTON32, _T("M103"), pDX);
}

void CServoMotorControlDlg::add_Control(const UINT &id, LPCTSTR device, CDataExchange* pDX)
{
	int button_id = id + smore_button_id;
	auto pItor = m_button.find(button_id);
	auto button  = new  PointMoveButton(button_id, device);
	m_button[button_id] = button;
	DDX_Control(pDX, id, *button);
	return;
}

BEGIN_MESSAGE_MAP(CServoMotorControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON21, &CServoMotorControlDlg::Start)
	ON_BN_CLICKED(IDC_BUTTON22, &CServoMotorControlDlg::Stop)
	ON_BN_CLICKED(IDC_BUTTON23, &CServoMotorControlDlg::M30)
	ON_BN_CLICKED(IDC_BUTTON24, &CServoMotorControlDlg::M31)
	ON_BN_CLICKED(IDC_BUTTON25, &CServoMotorControlDlg::M32)
	ON_BN_CLICKED(IDC_BUTTON26, &CServoMotorControlDlg::M33)
	ON_BN_CLICKED(IDC_BUTTON27, &CServoMotorControlDlg::M34)
	ON_BN_CLICKED(IDC_BUTTON28, &CServoMotorControlDlg::M35)
	ON_BN_CLICKED(IDC_BUTTON33, &CServoMotorControlDlg::M104)
	ON_BN_CLICKED(IDC_BUTTON34, &CServoMotorControlDlg::M105)
	ON_BN_CLICKED(IDC_BUTTON35, &CServoMotorControlDlg::M106)
	ON_BN_CLICKED(IDC_BUTTON36, &CServoMotorControlDlg::M107)
	ON_BN_CLICKED(IDC_BUTTON37, &CServoMotorControlDlg::M0)
	ON_BN_CLICKED(IDC_BUTTON38, &CServoMotorControlDlg::M180)
	ON_BN_CLICKED(IDC_BUTTON39, &CServoMotorControlDlg::M181)
	ON_BN_CLICKED(IDC_BUTTON40, &CServoMotorControlDlg::M184)
	ON_BN_CLICKED(IDC_BUTTON41, &CServoMotorControlDlg::M183)
	ON_BN_CLICKED(IDC_BUTTON42, &CServoMotorControlDlg::M185)
	ON_BN_CLICKED(IDC_BUTTON55, &CServoMotorControlDlg::M182)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON44, &CServoMotorControlDlg::turnON)
	ON_BN_CLICKED(IDC_BUTTON45, &CServoMotorControlDlg::turnOFF)
	ON_BN_CLICKED(IDC_BUTTON46, &CServoMotorControlDlg::camera)
END_MESSAGE_MAP()

BOOL CServoMotorControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	int   cx = 0, cy = 0;
	CRect rect;
	GetClientRect(&rect); //取客户区大小   
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;
	m_board.Create(IDD_DIALOG1);
	add_edit(IDC_EDIT28,_T("D2400"));
	add_edit(IDC_EDIT32, _T("D2402"));
	add_edit(IDC_EDIT36, _T("D2404"));
	add_edit(IDC_EDIT40, _T("D2406"));
	add_edit(IDC_EDIT41,_T("D2490"));
	m_m2044.LoadBitmaps(IDB_BITMAP1);
	m_m2044.SubclassDlgItem(IDC_BUTTON43, this);
	m_m2044.SizeToContent();
	return TRUE;  
}

void CServoMotorControlDlg::add_edit(const UINT &id, const LPCTSTR device)
{
	int Id = id + smore_button_id;
	ClickEdit* edit = new ClickEdit(Id, device);
	if (edit == NULL)
	{
		return ;
	}
	edit->SubclassDlgItem(id, this);
	m_edit[Id] = edit;
}

void CServoMotorControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{

	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CServoMotorControlDlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServoMotorControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//读数据线程
DWORD WINAPI CServoMotorControlDlg::ThreadProc(LPVOID pParam)
{
	CServoMotorControlDlg* ServoMotor = (CServoMotorControlDlg*)pParam;
	ServoMotor->ReadAndShowD();
	return 1;
}

//开机线程
DWORD WINAPI CServoMotorControlDlg::turnOn_thread(LPVOID pParam)
{
	CServoMotorControlDlg* ServoMotor = (CServoMotorControlDlg*)pParam;
	ServoMotor->turn_on();	
	return 1;
}
//自定义消息处理
BOOL CServoMotorControlDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (message <= smore_button_id || (message > IDC_EDIT41 + smore_button_id))
	{
		return CDialog::OnWndMsg(message, wParam, lParam, pResult);
	}
	
	auto pItor = m_button.find(message);
	if (pItor != m_button.end())
	{
		if (m_motorState == false)
		{
			return CDialog::OnWndMsg(message, wParam, lParam, pResult);

		}
		if (wParam == 1)
		{
			pItor->second->set_run(m_motor);
		}
		else if (wParam == 0)
		{
			pItor->second->set_stop(m_motor);
		}
		return CDialog::OnWndMsg(message, wParam, lParam, pResult);
	}
	auto pItor_edit = m_edit.find(message);
	if (pItor_edit != m_edit.end())
	{
		if (m_motorState == false)
		{
			return CDialog::OnWndMsg(message, wParam, lParam, pResult);

		}
		m_board.SetWindowPos(NULL, 500, 500, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_board.set_edit(pItor_edit->second);
		m_board.ShowWindow(SW_SHOW);
	}
 	
	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


//产生一个上升沿
void CServoMotorControlDlg::risingEdge(const CString str)
{
	if (m_motorState == false)
	{
		return;
	}
	m_motor.SetDevice(str, 0);
	Sleep(100);
	m_motor.SetDevice(str, 1);
	Sleep(400);
	m_motor.SetDevice(str, 0);
	return;
}

//读取D里面的数据显示到文本框
void CServoMotorControlDlg::ReadAndShowD()
{
	LONG value = 0; //读16位数据
	LONG data[2] = { 0 }; //32位数据

	while (m_motorState)
	{
		m_motor.ReadDeviceBlock(_T("D0"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		value = value;
		SetDlgItemInt(IDC_EDIT1, value);	

		m_motor.GetDevice(_T("D6"), &value);
		SetDlgItemInt(IDC_EDIT2, value);
		
		m_motor.GetDevice(_T("D7"), &value);
		SetDlgItemInt(IDC_EDIT3, value);
		
		m_motor.GetDevice(_T("D8"), &value);
		SetDlgItemInt(IDC_EDIT4, value);
		
		m_motor.ReadDeviceBlock(_T("D20"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT5, value);
		
		m_motor.GetDevice(_T("D26"), &value);
		SetDlgItemInt(IDC_EDIT6, value);
		
		m_motor.GetDevice(_T("D27"), &value);
		SetDlgItemInt(IDC_EDIT7, value);
		
		m_motor.GetDevice(_T("D28"), &value);
		SetDlgItemInt(IDC_EDIT8, value);
		
		m_motor.ReadDeviceBlock(_T("D40"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT9, value);
		
		m_motor.GetDevice(_T("D46"), &value);
		SetDlgItemInt(IDC_EDIT10, value);
		
		m_motor.GetDevice(_T("D47"), &value);
		SetDlgItemInt(IDC_EDIT11, value);
		
		m_motor.GetDevice(_T("D48"), &value);
		SetDlgItemInt(IDC_EDIT12, value);
		
		m_motor.ReadDeviceBlock(_T("D60"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT13, value);

		m_motor.GetDevice(_T("D66"), &value);
		SetDlgItemInt(IDC_EDIT14, value);
		
		m_motor.GetDevice(_T("D67"), &value);
		SetDlgItemInt(IDC_EDIT15, value);
		
		m_motor.GetDevice(_T("D68"), &value);
		SetDlgItemInt(IDC_EDIT16, value);
		
		m_motor.ReadDeviceBlock(_T("D80"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT17, value);
		
		m_motor.GetDevice(_T("D86"), &value);
		SetDlgItemInt(IDC_EDIT18, value);
		
		m_motor.GetDevice(_T("D87"), &value);
		SetDlgItemInt(IDC_EDIT19, value);
		
		m_motor.GetDevice(_T("D88"), &value);
		SetDlgItemInt(IDC_EDIT20, value);
	
		m_motor.ReadDeviceBlock(_T("D100"),2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT21, value);

		m_motor.GetDevice(_T("D106"), &value);
		SetDlgItemInt(IDC_EDIT22, value);
	
		m_motor.GetDevice(_T("D107"), &value);
		SetDlgItemInt(IDC_EDIT23, value);
	
		m_motor.GetDevice(_T("D108"), &value);
		SetDlgItemInt(IDC_EDIT24, value);
	
		m_motor.GetDevice(_T("D126"), &value);
		SetDlgItemInt(IDC_EDIT25, value);
	
		m_motor.GetDevice(_T("D127"), &value);
		SetDlgItemInt(IDC_EDIT26, value);
	
		m_motor.GetDevice(_T("D128"), &value);
		SetDlgItemInt(IDC_EDIT27, value);
	
		m_motor.GetDevice(_T("D146"), &value);
		SetDlgItemInt(IDC_EDIT29, value);
		
		m_motor.GetDevice(_T("147"), &value);
		SetDlgItemInt(IDC_EDIT30, value);

		m_motor.GetDevice(_T("148"), &value);
		SetDlgItemInt(IDC_EDIT31, value);

		m_motor.GetDevice(_T("D166"), &value);
		SetDlgItemInt(IDC_EDIT33, value);
		
		m_motor.GetDevice(_T("D167"), &value);
		SetDlgItemInt(IDC_EDIT34, value);
		
		m_motor.GetDevice(_T("D168"), &value);
		SetDlgItemInt(IDC_EDIT35, value);
		
		m_motor.GetDevice(_T("D186"), &value);
		SetDlgItemInt(IDC_EDIT37, value);

		m_motor.GetDevice(_T("D187"), &value);
		SetDlgItemInt(IDC_EDIT38, value);

		m_motor.GetDevice(_T("D188"), &value);
		SetDlgItemInt(IDC_EDIT39, value);

		m_motor.GetDevice(_T("M2044"), &value);
		if (value == 0)
		{
			m_m2044.LoadBitmaps(IDB_BITMAP1);
			m_m2044.Invalidate();
		}
		else
		{
			m_m2044.LoadBitmaps(IDB_BITMAP1);
			m_m2044.Invalidate();
		}

		//既要读又要写
		WaitForSingleObject(m_mutex, INFINITE);
		m_motor.ReadDeviceBlock(_T("D2400"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT28, value);
		
		m_motor.ReadDeviceBlock(_T("D2402"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT32, value);
		
		m_motor.ReadDeviceBlock(_T("D2404"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT36, value);
		
		m_motor.ReadDeviceBlock(_T("D2406"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		SetDlgItemInt(IDC_EDIT40, value);
		
		m_motor.ReadDeviceBlock(_T("D2490"), 2, data);
		value = (data[1] << 16) + (UINT)data[0];
		value /= 291271;
		SetDlgItemInt(IDC_EDIT41, value);
		ReleaseMutex(m_mutex);
	}
	
}

// 启动
void CServoMotorControlDlg::Start()
{
	if (m_motorState == true)
	{
		return;
	}
	m_motor.put_ActLogicalStationNumber(1);//设置PLC通道号
	LONG error = m_motor.Open();//打开通道 返回值不为0则失败
	if (error != 0)
	{
		return;
	}
	m_motorState = true;
	handle = ::CreateThread(NULL, 0, CServoMotorControlDlg::ThreadProc, this, 0, NULL);
}

// 停止
void CServoMotorControlDlg::Stop()
{
	if (m_motorState == false)
	{
		return;
	}

	LONG error = m_motor.Close();
	if (error != 0)
	{
		return;
	}
	m_motorState = false;
	WaitForMultipleObjects(1, &handle, true, INFINITE);
	::CloseHandle(handle);
}


void CServoMotorControlDlg::M30()
{
	risingEdge(_T("M30"));
}


void CServoMotorControlDlg::M31()
{
	risingEdge(_T("M31"));
}


void CServoMotorControlDlg::M32()
{
	risingEdge(_T("M32"));
}


void CServoMotorControlDlg::M33()
{
	risingEdge(_T("M33"));
}


void CServoMotorControlDlg::M34()
{
	risingEdge(_T("M34"));
}


void CServoMotorControlDlg::M35()
{
	risingEdge(_T("M35"));
}




void CServoMotorControlDlg::M104()
{
	risingEdge(_T("M104"));
}


void CServoMotorControlDlg::M105()
{
	risingEdge(_T("M105"));
	
}


void CServoMotorControlDlg::M106()
{
	risingEdge(_T("M106"));
}


void CServoMotorControlDlg::M107()
{
	risingEdge(_T("M107"));
}


void CServoMotorControlDlg::M0()
{
	risingEdge(_T("M0"));
}


void CServoMotorControlDlg::M180()
{
	risingEdge(_T("M180"));
}




void CServoMotorControlDlg::M181()
{
	LONG data = 0;
	if (m_motorState == false)
	{
		return;
	}
	m_motor.GetDevice(_T("M181"), &data);
	data = !data;
	m_motor.SetDevice(_T("M181"), data);
}

void CServoMotorControlDlg::M182()
{
	risingEdge(_T("M182"));
}

void CServoMotorControlDlg::M183()
{
	risingEdge(_T("M183"));
}

void CServoMotorControlDlg::M184()
{
	risingEdge(_T("M184"));
}

void CServoMotorControlDlg::M185()
{
	risingEdge(_T("M185"));
}


void CServoMotorControlDlg::OnSize(UINT nType, int cx, int cy)
{
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)//窗体大小发生变动。处理程序
	{
		float fsp[2];
		POINT Newp; //获取现在对话框的大小
		CRect recta;
		GetClientRect(&recta); //取客户区大小   
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / Old.x;
		fsp[1] = (float)Newp.y / Old.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //左上角
		CPoint OldBRPoint, BRPoint; //右下角
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}

		Old = Newp;
	}
	CDialogEx::OnSize(nType, cx, cy);

}


void CServoMotorControlDlg::OnClose()
{
	CDialogEx::OnClose();
	exit(0);
}


void CServoMotorControlDlg::turnON()
{
	if (!m_motorState)
	{
		return;
	}
	m_ONhandle = ::CreateThread(NULL, 0, CServoMotorControlDlg::turnOn_thread, this, 0, NULL);
}

void CServoMotorControlDlg::turn_on()
{
	risingEdge(_T("M180"));
	bool is_zero = false;
	while (!is_zero)
	{
		is_zero = true;
		if (!PositionOrigin(_T("D0")))
		{
			is_zero = false;
			break;
		}
		if (!PositionOrigin(_T("D20")))
		{
			is_zero = false;
			break;
		}
		if (!PositionOrigin(_T("D40")))
		{
			is_zero = false;
			break;
		}
		if (!PositionOrigin(_T("D60")))
		{
			is_zero = false;
			break;
		}

		if (!PositionOrigin(_T("D80")))
		{
			is_zero = false;
			break;
		}

		if (!PositionOrigin(_T("D100")))
		{
			is_zero = false;
			break;
		}
	}
	m_motor.SetDevice(_T("M181"), 1);
	risingEdge(_T("M183"));
}

bool CServoMotorControlDlg::PositionOrigin(const CString str)
{
	long data[2];
	long value;
	m_motor.ReadDeviceBlock(str, 2, data);
	value = (data[1] << 16) + (UINT)data[0];
	if (value != 0)
	{
		return false;
	}
	return true;
}

void CServoMotorControlDlg::turnOFF()
{
	risingEdge(_T("M185"));
	m_motor.SetDevice(_T("M181"), 0);
}


void CServoMotorControlDlg::OnOK()
{

}


void CServoMotorControlDlg::OnCancel()
{
	exit(0);
}


void CServoMotorControlDlg::camera()
{
	if (m_camera == NULL)
	{
		m_camera = new CameraInterface;
		m_camera->Create(IDD_DIALOG7);
	}
	
	m_camera->ShowWindow(SW_MAXIMIZE);
}
