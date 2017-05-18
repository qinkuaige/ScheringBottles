#include "stdafx.h"
#include "Control.h"
#include "DetectionDlg.h"
CControl* m_this = NULL;
CControl::CControl()
	:m_isConnect(FALSE)//保存连接状态
	, m_collectT(NULL)//发送数据线程
	, m_collectFlg(FALSE)//发送数据标志位
	, m_startFlag(FALSE)//采集标志位
	, m_workSubT(FALSE)//统计用工位
	, m_isStart(FALSE)//开始检测标志位
	, m_isSend(FALSE)//发送报文标志
{
	m_this = this;
	//工位
	for (INT i = 0; i < Work_Max; ++i)
	{
		for (INT j = 0; j < CH_Num + 1; ++j)
		{
			m_allWork[i][j] = Empty_Work;
		}
	}
	//获取程序路径
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_path = sPath;
}


CControl::~CControl()
{
	ComDisConnect();
}

//初始化
INT CControl::ComInit(CDetectionDlg* parentDlg)
{
	m_parentDlg = parentDlg;
	//加载参数
	PriReadIni();
	//初始化通讯
	CString key;
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		key.Format(_T("通道%d"),i + 1);
		CString addr;
		addr.Format(_T("%02d"), i + 1);
		m_modbus[i].ComInit(parentDlg, this, i, addr);//初始化通讯类
		m_modbus[i].ComLoadParam(key);//加载通讯参数
		m_modbus[i].ComSetCallBack(dataCallBack);//设置通讯用回调函数
	}
	
	//初始化伺服
	m_motor.ComInit(parentDlg,this);

	return TRUE;
}

//连接设备
INT CControl::ComConnect()
{
	if (m_isConnect == TRUE)
	{
		AfxMessageBox(_T("设备已连接,请勿重复连接"));
		return FALSE;
	}
	m_isConnect = TRUE;//设备连接标志位

	
	//连接数据库
	{
		if (m_sqlRes.IsOpen() == FALSE)
		{
			m_sqlRes.Open();
		}
		if (m_sqlResAll.IsOpen() == FALSE)
		{
			m_sqlResAll.Open();
		}
	}
	
	//连接通讯
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComConnect();//连接com口
		//读取配方
		m_modbus[i].ComSetRecipeT(_T("通用"));
	}
	
	//连接伺服
	m_motor.ComConnect();
	return TRUE;
}

//断开设备连接
INT CControl::ComDisConnect()
{
	if (m_isConnect == TRUE)
	{
		m_motor.ComDisConnect();
		PriStopOneThread(&m_collectFlg, m_collectT, 100);
		m_isConnect = FALSE;
	}
	return TRUE;
}

//开始检测
INT CControl::ComStart()
{
	m_isStart = TRUE;
#ifdef TEST
	//m_startFlag = TRUE;
	//测试保持数据
	
#endif
	return m_motor.ComStart();//伺服启动;
}

//停止检测
INT CControl::ComStop()
{
	m_isStart = FALSE;
	//m_access.ComUpData();
	PriInsertRes(0);
	PriInsertResAll();
	return m_motor.ComStop();//伺服停止
}

//清除数据
INT CControl::ComClearData()
{
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComClearData();
	}
	return TRUE;
}

//将错误信息输入到数据库中
INT CControl::ComInsertErr(vector<CString>& err)
{
	CSQLErr sqlErr;
	if (sqlErr.Open())
	{
		INT size = err.size();
		for (INT i = 0; i < size; ++i)
		{
			sqlErr.AddNew();
			CTime time = ::CTime::GetCurrentTime();//报错时间
			sqlErr.m_TI = time.GetTime();
			sqlErr.m_NAME = m_userName;//报错时操作员
			sqlErr.m_INFO = err[i];//错误信息
			sqlErr.Update();
		}
	}
	else
	{
		AfxMessageBox(_T("错误信息数据库打开失败！"));
	}
	return TRUE;
}

//关闭程序
INT CControl::ComExit()
{
	exit(0);
	return TRUE;
}

//获取数据的回调函数
INT CControl::dataCallBack(UINT GUID, CByteArray& arry)
{
	m_this->dataFun(GUID, arry);
	return TRUE;
}

//获取数据的回调函数
INT CControl::dataFun(UINT GUID, CByteArray& arry)
{
	//1#
	INT sub = m_modbus[GUID].m_workSub1;
	INT res = m_modbus[GUID].m_res1.m_res;
	if (res > m_allWork[sub][CH_Num])//存储数据 坏品 > 好品 > 空位
	{
		m_allWork[sub][CH_Num] = res;
	}
	//保存漏电电压
	m_allWork[sub][GUID * 2] = m_modbus[GUID].m_lou1;

	//2#
	sub = m_modbus[GUID].m_workSub2;
	res = m_modbus[GUID].m_res2.m_res;
	if (res > m_allWork[sub][CH_Num])//存储数据 坏品 > 好品 > 空位
	{
		m_allWork[sub][CH_Num] = res;
	}

	//保存漏电电压
	m_allWork[sub][GUID * 2 + 1] = m_modbus[GUID].m_lou2;
	
	if (GUID + 1 == ModBus_Num && m_allWork[sub][0] != Res_Empty)//储存数据
	{
		//保存数据
		PriInsertRes(sub);
		//统计数据
		++m_resT.m_allNum;//总数加一
		res = m_allWork[sub][CH_Num];
		m_allWork[sub][CH_Num] = Res_Empty;//数据清零
		if (res == Res_OK)//好品
		{
			++m_resT.m_goodNum;
		}
		else if (res == Res_NG)//坏品
		{
			++m_resT.m_badNum;
		}

	}
	//控件上显示结果
	//m_parentDlg->m_mainDlg.updataList(m_allWork[sub]);
	//工位加一
	PriAddWork(GUID);
	
	return TRUE;
}

//采集线程
UINT CControl::collectThread(LPVOID lParam)
{
	m_this->collectFun();
	return TRUE;
}

//采集函数
INT CControl::collectFun()
{
	m_collectT = NULL;
	return TRUE;
}

//发送报文
INT CControl::PriSendData()
{
#ifdef TEST
	//OutputDebugString(_T("开始发送数据"));
#endif
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComSendData();//发送报文
	}
	return TRUE;
}
//读取参数文件
INT CControl::PriReadIni()
{
	return TRUE;
}
//工位加一
INT CControl::PriAddWork(UINT GUID)
{
	//工位加一
	m_modbus[GUID].m_workSub1 = (m_modbus[GUID].m_workSub1 + m_modbus[GUID].m_workAdd1) % Work_Max;
	m_modbus[GUID].m_workSub2 = (m_modbus[GUID].m_workSub2 + m_modbus[GUID].m_workAdd2) % Work_Max;
	return TRUE;
}

//关闭一个线程
INT CControl::PriStopOneThread(INT* falg, CWinThread* pThread, INT waitTime)
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

//想数据库添加结果数据
INT CControl::PriInsertRes(INT sub)
{
	CTime time = CTime::GetCurrentTime();//
	m_sqlRes.AddNew();//添加新数据
	m_sqlRes.m_TI = time.GetTime();//时间
	m_sqlRes.m_PH = _T("1");//批号
	m_sqlRes.m_CH1 = m_allWork[sub][0];//通道1电压1
	m_sqlRes.m_CH2 = m_allWork[sub][1];//通道1电压2
	m_sqlRes.m_CH3 = m_allWork[sub][2];//通道2电压1
	m_sqlRes.m_CH4 = m_allWork[sub][3];//通道2电压2
	m_sqlRes.m_CH5 = m_allWork[sub][4];//通道3电压1
	m_sqlRes.m_CH6 = m_allWork[sub][5];//通道3电压2
	m_sqlRes.m_NG = m_allWork[sub][6];//结果

	m_sqlRes.Update();
	return TRUE;
}

//想数据库添加统计结果数据
INT CControl::PriInsertResAll()
{
	CTime time = CTime::GetCurrentTime();//
	m_sqlResAll.AddNew();//添加新数据
	m_sqlResAll.m_TIME = time.GetTime();//时间
	m_sqlResAll.m_PI = m_pi; //批号
	m_sqlResAll.m_USER = m_userName;//用户名
	m_sqlResAll.m_ALL = m_motor.m_allNum;//总数
	m_sqlResAll.m_BAD = m_motor.m_allBad;//废品数

	m_sqlResAll.Update();
	return TRUE;
}

