#pragma once
#include "DataBaseAcc.h"
#include "SQLResultRD.h"//历史数据
#include "SQLUser.h"//登录信息
#include "SQLErr.h"//错误信息记录
#include "SQLRecipe_CH.h"
#include "ModBus.h"
#include "MotorSL.h"
#include "SQLResult_All.h"

#define Data_Base_Path _T("\\data\\Data.accdb")
#define Main_Path _T("\\ini\\main")

class CDetectionDlg;
class CControl
{
public:
	CControl();
	virtual ~CControl();
	enum{
		ModBus_Num = 3,//通讯数量
		Send_Time = 20,//每20ms发送一次
		//Insert_Num = 5,//要插入的数据的个数
		Work_Max = 100,//最大工位数
		CH_Num = 6,//检测通道数
		Empty_Work = -100,//空位
	};
public:
	INT ComInit(CDetectionDlg* parentDlg);//初始化
	INT ComConnect();//连接设备
	INT ComDisConnect();//断开设备连接
	INT ComStart();//开始检测
	INT ComStop();//停止检测
	INT ComClearData();//清除数据
	//INT ComGetResData(LONGLONG tiMax, LONGLONG timin, vector<vector<CString>>& str);//获取历史结果数据
	//INT ComGetResData(CString PH, vector<vector<CString>>& str);//获取历史结果数据
	INT ComInsertErr(vector<CString>& err);//将错误信息输入到数据库中
	//INT ComIniRecipe(CString name = _T(""));//读取配方
	INT ComExit();//关闭程序
private:
	static INT dataCallBack(UINT GUID, CByteArray& arry);//获取数据的回调函数
	INT dataFun(UINT GUID, CByteArray& arry);//获取数据的回调函数
	static UINT collectThread(LPVOID lParam);//采集线程
	INT collectFun();//采集函数
	static UINT PriSetRecipeThread(LPVOID lParam);//设置配方报文线程
	INT PriSetRecipeFun();//设置配方报文函数

	INT PriReadIni();//读取参数文件
	INT PriAddWork(UINT GUID);//工位加一
	INT PriStopOneThread(INT* falg, CWinThread* pThread, INT waitTime);//关闭一个线程
	INT PriInsertRes(INT sub = 0);//想数据库添加结果数据
	INT PriInsertResAll();//想数据库添加统计结果数据
public:
	INT PriSendData();//发送报文
public:
	//ModBusStruct m_modbus[ModBus_Num];
	CModBus m_modbus[ModBus_Num];//modBus通讯类
	CMotorSL m_motor;//伺服控制
	INT m_startFlag;//采集标志位
	CWinThread* m_collectT;//发送数据线程
	INT		m_collectFlg;//发送数据标志位
	INT m_isConnect;//保存连接状态
	CString m_path;//保存当前路径
	resultStruct m_resT;//统计结果
	INT		m_workSubT;//t统计用工位
	INT		m_isStart;//开始检测标志位
	INT     m_isSend;//发送报文标志位
	CString m_userName;//操作员名称
	CString m_pi;
//工位
public:
	INT m_allWork[Work_Max][CH_Num + 1];
public:
	DataBaseAcc m_access;//数据存储类
	CSQLResultRD m_sqlRes;//结果表
	CSQLResultAll m_sqlResAll;//保存统计结果
	CDetectionDlg* m_parentDlg;//主窗口类
};

