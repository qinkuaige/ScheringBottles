#pragma once
#include "ModBusDlg.h"
#include <queue>
using namespace std;
#define FILE_NAME _T("com.ini")
#define Get_Param _T("0300000011")
enum
{
	Param_Num = 17,//参数个数
	Data_Num = 6,//正常读取数据的个数
};

struct ComStruct
{
	INT m_comID;
	INT m_baud;//波特率
	CString m_verify;//校验位
	INT m_startNum;//数据位
	INT m_stopNum;//停止位
	CString m_sendData;//默认报文
	//获取设置字符串
	CString getSetting()
	{
		CString str;
		str.Format(_T("%d,%s,%d,%d"), m_baud, m_verify, m_startNum, m_stopNum);
		return str;
	}
	ComStruct()
	{
		m_comID = 1;
		m_baud = 38400;//波特率
		m_verify = _T("n");//校验位
		m_startNum = 8;//数据位
		m_stopNum = 1;//停止位
		m_sendData = _T("0300000006C5C8");//默认报文
	}
};

struct resultStruct
{
	INT m_res;//当前结果
	INT m_allNum;//总数
	INT m_goodNum;//好品数
	INT m_badNum;//坏品总数
	INT m_allEmptyNum;//空品总数
	resultStruct()
	{
		m_res = FALSE;//当前结果
		m_allNum = FALSE;//总数
		m_goodNum = FALSE;//好品数
		m_badNum = FALSE;//坏品总数
		m_allEmptyNum = FALSE;//空品总数
	}
	resultStruct& operator=(const resultStruct& other)
	{
		m_res = other.m_res;//当前结果
		m_allNum = other.m_allNum;//总数
		m_goodNum = other.m_goodNum;//好品数
		m_badNum = other.m_badNum;//坏品总数
		m_allEmptyNum = other.m_allEmptyNum;//空品总数
		return *this;
	}
	INT clear()//数据清零
	{
		m_res = FALSE;//当前结果
		m_allNum = FALSE;//总数
		m_goodNum = FALSE;//好品数
		m_badNum = FALSE;//坏品总数
		m_allEmptyNum = FALSE;//空品总数
		return TRUE;
	}
};
struct CHStruct
{

};
typedef INT(*ComData)(UINT GUID, CByteArray& arry);

enum
{
	Res_Empty = -100,
	Res_OK = FALSE,
	Res_NG = TRUE,
};
enum
{
	Max_Data_Num = 30,//最大参数个数
	U1 = 0,//电源电压1
	U2 = 1,//电源电压2
	Lou1 = 4,//上一瓶泄漏电压1
	Lou2 = 5,//上一瓶泄漏电压2
	U_SET1 = 6,//高压设定值
	U_SET2 = 12,//高压设定值
	UpLine1 = 7,//泄漏电压上限1
	UpLine2 = 13,//泄漏电压上限2
	DownLine1 = 9,//泄漏电压下限1
	DownLine2 = 15,//泄漏电压下限1
	LMD1 = 10,	//1#放大倍数
	LMD2 = 16,	//2#放大倍数
};

class CDetectionDlg;
class CControl;
class CModBus
{
public:
	CModBus();
	virtual ~CModBus();
	enum{
		CRC_Send = 0,
		CRC_Receive,
	};
public:
	virtual INT ComInit(CDetectionDlg* parent, CControl* control ,
		UINT GUID = FALSE, CString addr = _T("00"));//初始化类
	virtual INT ComLoadParam(CString key);//初始化类
	virtual INT ComConnect();//打开串口
	INT ComDisConnect();//关闭断开连接
	virtual INT ComSendData(INT isCRC = FALSE);//是否做CRC校验
	virtual INT ComSendData(CString Data, INT isCRC = FALSE);//是否做CRC校验
	virtual INT ComSetCallBack(ComData fun);//设置回调函数
	virtual INT ComGetParam();//获取设备参数
	INT ComSetParam(LONG addr, LONG value, INT isSQL = TRUE);//设置取设备参数
	INT ComClearData();//统计数据清零
	INT ComSetRecipeT(CString name);//设置配方数据线程
	INT ComSetRecipe(CString name);//设置配方数据
	INT ComAddRecipe(CString name);//添加配方
	INT ComRemoveRecipe(CString name);//删除配方
private:
	INT PriCreateDlg();
	INT PriReadIni(CString key);//读取配置文件
	INT PriCRC(CByteArray& arr, INT flag = CRC_Send);//CRC校验
	static UINT PriSetRecipeThread(LPVOID lParam);//设置配方数据
	
public:
	static UINT PriCollectThread(LPVOID lParam);//采集数据线程
	INT PriCollectFun();//采集函数
	INT PriGetData();//获取数据
	INT PriSaveGetData();//保存获取到的数据
private:
	UINT m_GUID;//序号
	CDetectionDlg* m_pDlg;
	CControl* m_pControl;
	CMscomm1* m_pCom;//串口插件地址
	CWnd* m_parentDlg;//保存父类窗口指针
	CModBusDlg* m_dlg;//串口插件所在的窗口指针
	ComStruct m_comParam;//串口参数结构体
	CString m_path;//保存当前程序路径
	CByteArray m_readArr;//保存接收到的数据
	INT m_isParam;//保存是否是参数报文
	CString m_addr;//设备地址
	INT m_isSend;//判断一条报文是否发送完全
	CString m_rName;//配方名称
	INT m_isConnect;//保存连接状态
	INT m_collectF;//采集线程标志位
	CWinThread* m_collectT;//采集线程
public:
	INT m_startFlag;//开始采集

//高压箱参数
public:
	INT m_data[Max_Data_Num];//获取到的参数值
	INT m_upLine1;//泄漏电压上限
	INT m_downLine1;//泄漏电压下限
	INT m_u1;//电源电压
	INT m_upLine2;//泄漏电压上限
	INT m_downLine2;//泄漏电压下限
	INT m_u2;//电源电压
	INT m_workSub1;//工位号1
	INT m_workSub2;//工位号2
	INT m_workSub3;//工位号2
	INT m_workAdd1;//工位增量1
	INT m_workAdd2;//工位增量2
	INT m_workAdd3;//工位增量2
	INT m_lou1;//泄漏电压1
	INT m_lou2;//泄漏电压2
	resultStruct m_res1;//结果1
	resultStruct m_res2;//结果2
	CSQLRecipe_CH m_recipe;//参数
public:
	ComData m_dataFun;
	CRITICAL_SECTION m_cs;//临界区
};

