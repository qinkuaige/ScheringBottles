#include "stdafx.h"
#include "MotorSL.h"
#include "Control.h"

CMotorSL::CMotorSL()
	:m_GUID(FALSE)//序号
	, m_state(State_DisConnect)//保存伺服状态
	, m_isRun(FALSE)//设备在运行状态
	, m_permission(FALSE)//权限
	, m_pStartFlag(NULL)//
	, m_speed(FALSE)//保存运行速度
	, m_collectT(NULL)//采集线程
	, m_collectFlag(FALSE)//采集标志位
	, m_pMotor(NULL)//伺服控制
	, m_allNum(FALSE)//PLC统计总数
	, m_allBad(FALSE)//PLC统计总废品数
{
	InitializeCriticalSection(&m_cs);//初始化临界区  
	for (INT i = 0; i < 255; ++i)
	{
		m_errState[i] = 0;
	}
}


CMotorSL::~CMotorSL()
{
	ComDisConnect();
}

//初始化类
INT CMotorSL::ComInit(CWnd* parentDlg, CControl* control, UINT GUID, INT permission)
{
	m_GUID = GUID;//保存序号
	m_permission = permission;//保存权限
	m_pControl = control;
	PriCreateMotor(parentDlg);
	return TRUE;
}

//连接设备
INT CMotorSL::ComConnect(UINT Channel)
{
	CString	MsgStr;
	CString str;
	str.Format(_T("%d"), Channel);
	if (Channel > 1024)
	{
		AfxMessageBox(_T("伺服连接站点号超范围(0-1024):") + Channel);
		return FALSE;
	}
	if (State_Connect == m_state)
	{
		AfxMessageBox(_T("伺服电机已经连接上"));
		return TRUE;
	}
	try{
		//设置PLC站号
		//m_motorDlg.m_motor.put_ActLogicalStationNumber(Channel);

		m_pMotor->put_ActLogicalStationNumber(Channel);
		m_pMotor->Close();
		long re = m_pMotor->Open();	// Open method exec
		if (!re){
			m_state = State_Connect;
		}
		else{
			m_state = State_DisConnect;
			CString str1;
			str1.Format(_T("0X%x"), re);
			AfxMessageBox(_T("站号:") + str + _T("伺服电机连接失败！错误码:") + str1);
			return FALSE;
		}
	}
	catch (INT w){
		int x = w;
		AfxMessageBox(_T("站号:") + str + _T("伺服电机连接失败！"));
		return FALSE;
	}
	//获取当前速度
	LONG value1 = FALSE;
	LONG value2 = FALSE;
	ComGetValue(_T("D578"), &value1);
	ComGetValue(_T("D579"), &value2);
	m_speed = value1 + value2 * 65536;

	//错误复位
	ComResetErr();

	//开启采集线程
	PriOpenThread();
	return TRUE;
}

//断开连接
INT CMotorSL::ComDisConnect()
{
	if (m_state == State_DisConnect)
	{
		return TRUE;
	}
	ComStop();
	PriCloseThread();
	m_pMotor->Close();//断开伺服连接
	m_state = State_DisConnect;
	return TRUE;
}

//设备启动
INT CMotorSL::ComStart()
{
	if (m_state == State_DisConnect)
	{
		AfxMessageBox(_T("伺服未连接"));
		return FALSE;
	}
	//错误复位
	ComResetErr();

	//计数清零
	ComClearData();

	vector<CString> err;
	ComGetErr(err);
	if (err.size() > 0)
	{
		AfxMessageBox(err[0]);
		return FALSE; 
	}
	if (m_isRun == TRUE)
	{
		return TRUE;
	}

	//启动设备
	AfxBeginThread(PriStartThread, this);
	//打开采集线程
	PriOpenThread();
	return TRUE;
}

//设备停止
INT CMotorSL::ComStop()
{
	if (m_state == State_DisConnect)
	{
		AfxMessageBox(_T("伺服未连接"));
		return FALSE;
	}

	//停止设备
	PriStopFun();
	//关闭采集线程
	PriCloseThread();
	m_isRun = FALSE;
	m_state = State_Stop;
	return TRUE;
}

//设置伺服地址的值
INT CMotorSL::ComSetValue(CString addr, long value)
{
	if (m_state == State_DisConnect)
	{
		return FALSE;
	}
	//EnterCriticalSection(&m_cs);//进入临界区 
	m_pMotor->SetDevice(addr, value);
	//LeaveCriticalSection(&m_cs);//离开临界区 
	return TRUE;
}

//获取伺服地址的值
INT CMotorSL::ComGetValue(CString addr, long* value)
{
	if (m_state == State_DisConnect || value == NULL)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//进入临界区 
	m_pMotor->GetDevice(addr, value);
	LeaveCriticalSection(&m_cs);//离开临界区 
	return TRUE;
}

//获取伺服X地址
INT CMotorSL::ComGetValueX(CString addr, long* value, INT num)
{
	if (m_state == State_DisConnect || value == NULL)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//进入临界区 
	m_pMotor->ReadDeviceRandom(addr, num, value);
	LeaveCriticalSection(&m_cs);//离开临界区 
	return TRUE;
}

//批量获取伺服地址的值
INT CMotorSL::ComGetValue(CString addr, long* value, INT num)
{
	if (m_state == State_DisConnect || value == NULL || num <= 0)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//进入临界区 
	m_pMotor->ReadDeviceBlock(addr, num, value);
	LeaveCriticalSection(&m_cs);//离开临界区 
	return TRUE;
}

//设置取图标识位
INT CMotorSL::ComSetGrabFlag(INT GUID, INT* grabFlag)
{
	m_pStartFlag = grabFlag;
	return TRUE;
}

//获取设备运行速度
INT CMotorSL::ComGetSpeed()
{
	return m_speed;
}

//设置速度
INT CMotorSL::ComSetSpeed(LONG speed)
{
	if (speed > Max_Motor_Speed)
	{
		speed = Max_Motor_Speed;
	}
	if (speed < 0)
	{
		speed = 0;
	}
	LONG value1 = speed % 65536;
	LONG value2 = speed / 65536;
	if (ComSetValue(_T("D578"), value1) == TRUE)
	{
		ComSetValue(_T("D579"), value2);
		ComSetValue(_T("M645"), TRUE);
		Sleep(400);
		ComSetValue(_T("M645"), FALSE);
		m_speed = speed;
	}
	
	return TRUE;
}

int CMotorSL::ComSetmbSpeed(LONG speed)
{
	if (speed > Max_MeshBelt_speed)
	{
		speed = Max_MeshBelt_speed;
	}
	if (speed < 0)
	{
		speed = 0;
	}

	if (ComSetValue(_T("D690"), speed) == TRUE)
	{
		ComSetValue(_T("M647"), TRUE);
		Sleep(400);
		ComSetValue(_T("M647"), FALSE);
		return TRUE;
	}
	return FALSE;
}

//获取错误信息
INT CMotorSL::ComGetErr(vector<CString>& str)
{
	LONG data[3] = { 0 };
	ComGetValue(_T("D0"), data, 3);

	
	str.clear();//
	INT sub = 0;//计数器
	PriGetErr((data[0] >> 0) & 1, _T("紧急停机按钮1按下！"), str, sub++);
	PriGetErr((data[0] >> 1) & 1, _T("紧急停机按钮2按下！"), str, sub++);
	PriGetErr((data[0] >> 2) & 1, _T("变频器报警！"), str, sub++);
	PriGetErr((data[0] >> 3) & 1, _T("Q2开关保护！"), str, sub++);
	PriGetErr((data[0] >> 4) & 1, _T("Q3开关保护！"), str, sub++);
	PriGetErr((data[0] >> 5) & 1, _T("门打开！"), str, sub++);


	PriGetErr((data[1] >> 0) & 1, _T("1号检测连续破损！"), str, sub++);
	PriGetErr((data[1] >> 1) & 1, _T("2号检测连续破损！"), str, sub++);
	PriGetErr((data[1] >> 2) & 1, _T("3号检测连续破损！"), str, sub++);
	PriGetErr((data[1] >> 3) & 1, _T("4号检测连续破损！"), str, sub++);
	PriGetErr((data[1] >> 4) & 1, _T("5号检测连续破损！"), str, sub++);
	PriGetErr((data[1] >> 5) & 1, _T("6号检测连续破损！"), str, sub++);


	PriGetErr((data[2] >> 0) & 1, _T("1轴错误检测！"), str, sub++);
	PriGetErr((data[2] >> 1) & 1, _T("2轴错误检测！"), str, sub++);
	PriGetErr((data[2] >> 2) & 1, _T("3轴错误检测！"), str, sub++);
	PriGetErr((data[2] >> 3) & 1, _T("4轴错误检测！"), str, sub++);
	PriGetErr((data[2] >> 4) & 1, _T("5轴错误检测！"), str, sub++);

	PriGetErr((data[2] >> 5) & 1, _T("1轴报警检测！"), str, sub++);
	PriGetErr((data[2] >> 6) & 1, _T("2轴报警检测！"), str, sub++);
	PriGetErr((data[2] >> 7) & 1, _T("3轴报警检测！"), str, sub++);
	PriGetErr((data[2] >> 8) & 1, _T("4轴报警检测！"), str, sub++);
	PriGetErr((data[2] >> 9) & 1, _T("5轴报警检测！"), str, sub++);

	PriGetErr((data[2] >> 10) & 1, _T("1轴伺服状态报警！"), str, sub++);
	PriGetErr((data[2] >> 11) & 1, _T("2轴伺服状态报警！"), str, sub++);
	PriGetErr((data[2] >> 12) & 1, _T("3轴伺服状态报警！"), str, sub++);
	PriGetErr((data[2] >> 13) & 1, _T("4轴伺服状态报警！"), str, sub++);
	PriGetErr((data[2] >> 14) & 1, _T("5轴伺服状态报警！"), str, sub++);
	
	CString errInfo;
	for (INT i = 0; i < str.size(); ++i)
	{
		errInfo += str[i] + _T("\n");
	}
	if (str.size() > 0)
	{
		AfxMessageBox(errInfo);
	}
	return str.size();
}

//错误复位
INT CMotorSL::ComResetErr()
{
	ComSetValue(_T("M500"), TRUE);
	ComSetValue(_T("M480"), TRUE);
	Sleep(300);
	ComSetValue(_T("M500"), FALSE);
	ComSetValue(_T("M480"), FALSE);
	for (INT i = 0; i < 255; ++i)
	{
		m_errState[i] = FALSE;
	}
	return TRUE;
}
//数据清零
INT CMotorSL::ComClearData()
{
	ComSetValue(_T("M420"), TRUE);
	Sleep(300);
	ComSetValue(_T("M420"), FALSE);
	return TRUE;
}
//创建伺服插件
INT CMotorSL::PriCreateMotor(CWnd* parent)
{
	if (m_pMotor != NULL)
	{
		delete m_pMotor;
		m_pMotor = NULL;
	}
	//拿到伺服插件指针
	m_pMotor = new CActutltype1;
	INT res = m_pMotor->Create(_T(""), _T(""), WS_CHILD, CRect(0, 0, 10, 10), parent, Dlg_ID);
	if (res == FALSE)
	{
		delete m_pMotor;
		m_pMotor = NULL;
		AfxMessageBox(_T("伺服插件创建失败！"));
		return FALSE;
	}
	
	return TRUE;
}

//采集线程
UINT CMotorSL::PriCollectThread(LPVOID lparam)
{
	CMotorSL* parent = (CMotorSL*)lparam;
	parent->PriCollectFun();
	return TRUE;
}

//采集函数
INT CMotorSL::PriCollectFun()
{
	LONG start = -1;
	LONG upDown = -1;
	LONG value = 0;
	LONG data[20] = { 0 };
	LONG isErr = 0;
	enum
	{
		Speed = 0,//速度
		All_Num = 1,//总数
		Bad_Num = 3,//废品数

	};
	m_collectFlag = TRUE;
	while (m_collectFlag)
	{
		//实事获取plc运行数据
		ComGetValue(_T("D3"), m_data, Plc_Data_Num);
		if ((m_data[0] >> 5) & 1)//上升沿或者下降沿触发报警
		{
			isErr = TRUE;
			vector<CString> errInfo;
			if (ComGetErr(errInfo))
			{
				m_pControl->ComInsertErr(errInfo);//错误信息保存到数据库
			}
		}
		
		m_isRun = ((m_data[0] >> 4) & 1) && ((m_data[0] >> 0) & 1);//保存设备运行状态，运行状态为1 且同步为1的时候才算开机了
		if (m_isRun != TRUE)//停机状态
		{
			Sleep(20);
			continue;
		}
		//获取PLC的总数
		m_allNum = m_data[1] + m_data[2] * 65536;
		m_allBad = m_data[3] + m_data[4] * 65536;

		value = (m_data[0] >> 1) & 1;//工位信号
		if (upDown == -1)
		{
			upDown = value;
			continue;
		}
		if (upDown != value)
		{
			upDown = value;
			if (upDown == TRUE)
			{
				for (INT i = 0; i < CControl::ModBus_Num; ++i)
				{
					if (m_pControl->m_modbus[i].m_startFlag == TRUE)
					{
						CString str;
						str.Format(_T("高压箱%d数据采集超时"), i + 1);
						OutputDebugString(str);
					}
					m_pControl->m_modbus[i].m_startFlag = TRUE;
				}
				static INT count = FALSE;
				count++;
				CString str;
				str.Format(_T("count = %d"), count);
				OutputDebugString(str);
			}
			
		}
		Sleep(5);
	}
	m_collectFlag = FALSE;
	m_collectT = NULL;
	return TRUE;
}

//开机线程
UINT CMotorSL::PriStartThread(LPVOID lParam)
{
	static INT isRun = FALSE;//开机线程不重复启动
	if (isRun == TRUE)
	{
		return TRUE;
	}
	isRun = TRUE;
	CMotorSL* parent = (CMotorSL*)lParam;
	parent->PriStartFun();
	isRun = FALSE;
	return TRUE;
}

//设备启动流程函数
INT CMotorSL::PriStartFun()
{
	LONG value = FALSE;
	
	//同步
	ComGetValue(_T("M660"), &value);
	if (value == FALSE)//判断是否在同步
	{
		//原点回归
		ComSetValue(_T("M541"),TRUE);
		Sleep(300);
		ComSetValue(_T("M541"), FALSE);
		LONG data[2] = { 0 };
		INT time = 100;
		while (TRUE)
		{
			ComGetValue(_T("D500"), data, 2);
			if (PriGetValue(data) == FALSE)
			{
				Sleep(2);
				ComGetValue(_T("D502"), data, 2);
				if (PriGetValue(data) == FALSE)
				{
					Sleep(2);
					ComGetValue(_T("D504"), data, 2);
					if (PriGetValue(data) == FALSE)
					{
						Sleep(2);
						ComGetValue(_T("D506"), data, 2);
						if (PriGetValue(data) == FALSE)
						{
							Sleep(2);
							ComGetValue(_T("D652"), data, 2);
							if (PriGetValue(data) == FALSE)
							{
								Sleep(200);
								break;
							}
						}
						
					}
				}
			}
			if (time > 0)//超时
			{
				--time;
			}
			else
			{
				AfxMessageBox(_T("开机超时！"));
				return FALSE;
			}
			Sleep(200);
		}
		//开始同步
		ComSetValue(_T("M660"), TRUE);
	}//判断是否在同步

	//关闭机械调试
	ComSetValue(_T("M631"), FALSE);
	//主机启动
	ComSetValue(_T("M670"), TRUE);
	Sleep(500);
	ComSetValue(_T("M670"), FALSE);

	//启动状态
	m_state = State_Start;
	return TRUE;
}

//停机线程
UINT CMotorSL::PriStopThread(LPVOID lParam)
{
	CMotorSL* parent = (CMotorSL*)lParam;
	parent->PriStopFun();
	return TRUE;
}

//设备停止流程函数
INT CMotorSL::PriStopFun()
{
	//启动停止
	ComSetValue(_T("M642"), TRUE);
	Sleep(500);
	ComSetValue(_T("M642"), FALSE);
	
	return TRUE;
}



//打开采集线程
INT CMotorSL::PriOpenThread()
{
	if (m_collectFlag == TRUE)//如果线程没有被关闭则直接返回
	{
		return TRUE;
	}
	m_collectFlag = TRUE;
	//开启采集线程
	m_collectT = AfxBeginThread(PriCollectThread, this);
	return TRUE;
}

//关闭线程
INT CMotorSL::PriCloseThread()
{
	PriStopOneThread(&m_collectFlag,m_collectT, 200);
	return TRUE;
}

//关闭一个线程
INT CMotorSL::PriStopOneThread(INT* falg,CWinThread* pThread, INT waitTime)
{
	if (*falg != TRUE)
	{
		return TRUE;
	}
	*falg = FALSE;

	HRESULT hResult = ERROR_SUCCESS;
	//等待取图线程结束
	if (pThread != NULL && WaitForSingleObject(pThread->m_hThread, waitTime) != WAIT_OBJECT_0)
	{
		INT res = TerminateThread(pThread->m_hThread, 0);//强制关闭线程
		if (!res)//获取为什么没有关闭线程的原因
		{
			hResult = ::GetLastError();
		}
		//判断线程是否有效 有效则回收线程
		if (hResult != ERROR_INVALID_HANDLE)
		{
			delete pThread;
		}
		pThread = NULL;
	}
	return TRUE;
}

//计算伺服获取的数据结果
INT CMotorSL::PriGetValue(LONG* data)
{
	data[0] = (USHORT)data[0];
	data[1] = (USHORT)data[1];
	return data[0] + (USHORT)data[1] * 65536;
}

//获取单个报警信息
INT CMotorSL::PriGetErr(CString addr, CString message, vector<CString>& str, INT sub)
{
	LONG value;
	ComGetValue(addr, &value);
	if (value != m_errState[sub])//判断是否有新的报警
	{
		m_errState[sub] = value;
		if (value == TRUE)
		{
			str.push_back(message);
		}
	}
	
	return TRUE;
}