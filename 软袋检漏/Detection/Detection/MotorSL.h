#pragma once
#include "actutltype1.h"
#include <vector>
#include <map>
using namespace std;

enum{
	P_Speed = 0,//速度
	P_AllNum = 1,//总数
	P_BadNum = 3,//废品数
	P_WDai = 5,//网带状态
	P_ZJi = 6,//主机运行状态
	P_Grab = 7,//采集信号
	P_BJin = 8,//报警
};

//class CMotorDlg;
class CActutltype1;
class CControl;
class CMotorSL
{
public:
	CMotorSL();
	virtual ~CMotorSL();
public:
	enum
	{
		State_DisConnect = 0,//设备断开连接状态
		State_Connect,	//设备连接状态
		State_Start,
		State_Stop,
		Dlg_ID = 4100,		//
		Plc_Data_Num = 5,//连续采集plc数据 个数
		Max_Motor_Speed = 120,//伺服运行最大速度
	};
	
	enum
	{
		PLC_X = 0,
		PLC_M = 0,
		PLC_D = 0,
	};
public:
	virtual INT ComInit(CWnd* parentDlg, CControl* control, UINT GUID = FALSE, INT permission = FALSE);//初始化类
	//伺服操作
	virtual INT ComConnect(UINT Channel = TRUE);//连接设备
	virtual INT ComDisConnect();//断开连接
	virtual INT ComStart();//设备启动
	virtual INT ComStop();//设备停止
	//virtual INT ComGetErr(vector<CString> err){ return FALSE; };//获取报警信息
	virtual INT ComSetValue(CString addr, long value);//设置伺服地址的值
	virtual INT ComGetValue(CString addr, long* value);//获取伺服地址的值
	virtual INT ComGetValueX(CString addr, long* value, INT num = TRUE);//获取伺服X地址
	virtual INT ComGetValue(CString addr, long* value, INT num);//批量获取伺服地址的值
	virtual INT ComSetGrabFlag(INT GUID, INT* grabFlag);//设置取图标识位
	virtual INT ComGetSpeed();//获取设备运行速度
	virtual INT ComSetSpeed(LONG value);//设置速度
	virtual INT ComGetErr(vector<CString>& str);//获取错误信息
	virtual INT ComResetErr();//错误复位
	virtual INT ComClearData();//数据清零
private:
	INT PriCreateMotor(CWnd* parent);//创建窗口
	static UINT PriCollectThread(LPVOID lparam);//采集线程
	INT PriCollectFun();//采集函数
	static UINT PriStartThread(LPVOID lParam);//开机线程
	INT PriStartFun();//设备启动流程函数
	static UINT PriStopThread(LPVOID lParam);//停机线程
	INT PriStopFun();//设备停止流程函数
	INT PriOpenThread();//开启线程
	INT PriCloseThread();//关闭线程
	INT PriStopOneThread(INT* falg,CWinThread* pThread, INT waitTime);//关闭一个线程
	INT PriGetValue(LONG* data);
	INT PriGetErr(CString addr, CString message, vector<CString>& str, INT sub = 0);//获取单个报警信息
	//获取单个报警信息
	inline INT PriGetErr(INT value ,CString message, vector<CString>& str, INT sub = 0)
	{
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
public:
	CActutltype1* m_pMotor;
	CControl* m_pControl;//主逻辑类
public:
	INT m_GUID;//序号
	INT m_state;//保存伺服状态
	INT m_isRun;//设备在运行状态
	INT m_permission;//权限
	INT* m_pStartFlag;//
	INT m_speed;//保存运行速度
	CWinThread* m_collectT;//采集线程
	INT m_collectFlag;//采集标志位
	INT Motor_ID;//
	CRITICAL_SECTION m_cs;//临界区
	LONG m_data[Plc_Data_Num];//保存PLC数据
	INT m_errState[255];//报警状态
	INT m_allNum;//PLC统计总数
	INT m_allBad;//PLC统计总废品数
};

