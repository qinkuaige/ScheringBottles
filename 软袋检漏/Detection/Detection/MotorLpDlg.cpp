// MotorLpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "MotorLpDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CMotorLpDlg 对话框

IMPLEMENT_DYNAMIC(CMotorLpDlg, CDialogEx)

CMotorLpDlg::CMotorLpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorLpDlg::IDD, pParent)
{

}

CMotorLpDlg::~CMotorLpDlg()
{
}

void CMotorLpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIAO_SHI, m_tiaoShi);
	DDX_Control(pDX, IDC_TONG_BU, m_tongBu);
}


BEGIN_MESSAGE_MAP(CMotorLpDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CH_SPEED, &CMotorLpDlg::OnBnClickedChSpeed)
END_MESSAGE_MAP()


// CMotorLpDlg 消息处理程序
// CMotorLpDlg 消息处理程序
INT CMotorLpDlg::initDialog(CDetectionDlg* parentDlg)
{
	m_pDlg = parentDlg;
	if (Create(IDD, m_pDlg) == FALSE)
	{
		AfxMessageBox(_T("主监控界面创建失败！"));
		return FALSE;
	}
	m_pMotor = &m_pDlg->m_control.m_motor;
	return TRUE;
}

INT CMotorLpDlg::showDialog(INT dlgID)
{
	if (dlgID == IDD)
	{
		SetTimer(2000, 500, NULL);
		ShowWindow(SW_SHOW);
	}
	else
	{
		KillTimer(2000);
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}
BEGIN_EVENTSINK_MAP(CMotorLpDlg, CDialogEx)
	//正转
	ON_EVENT(CMotorLpDlg, IDC_UP1, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP1, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP2, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP2, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP3, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP3, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP4, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP4, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP5, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_UP5, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)


	//反转
	ON_EVENT(CMotorLpDlg, IDC_DOWN1, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN1, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN2, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN2, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN3, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN3, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN4, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN4, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN5, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_DOWN5, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)


	//回零
	ON_EVENT(CMotorLpDlg, IDC_BACK1, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK1, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK2, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK2, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK3, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK3, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK4, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK4, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK5, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_BACK5, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//设置原点
	ON_EVENT(CMotorLpDlg, IDC_SET1, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET1, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET2, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET2, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET3, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET3, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET4, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET4, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET5, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SET5, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//主机停止
	ON_EVENT(CMotorLpDlg, IDC_STOP, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_STOP, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//手动
	ON_EVENT(CMotorLpDlg, IDC_SHOU_DONG, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SHOU_DONG, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//复位
	ON_EVENT(CMotorLpDlg, IDC_CLEAR_ERR, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_CLEAR_ERR, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	
	
	//速度变更
	ON_EVENT(CMotorLpDlg, IDC_CH_SPEED, DISPID_CLICK, CMotorLpDlg::ClickChSpeed, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_CLEAR, DISPID_CLICK, CMotorLpDlg::ClickClear, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_TIAO_SHI, DISPID_CLICK, CMotorLpDlg::ClickTiaoShi, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_TONG_BU, DISPID_CLICK, CMotorLpDlg::ClickTongBu, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_START, 1, CMotorLpDlg::LButtonDownStart, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_START, 2, CMotorLpDlg::LButtonUpStart, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_ZI_DONG, 1, CMotorLpDlg::LButtonDownZiDong, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_ZI_DONG, 2, CMotorLpDlg::LButtonUpZiDong, VTS_I4 VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

//点动 down
void CMotorLpDlg::LButtonDownUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, TRUE);
}

//点动 up
void CMotorLpDlg::LButtonUpUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, FALSE);
}


//主机启动
void CMotorLpDlg::LButtonDownStart(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(_T("M50"), TRUE);
	m_pMotor->ComSetValue(_T("M870"), TRUE);
	
}

void CMotorLpDlg::LButtonUpStart(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(_T("M50"), FALSE);
	m_pMotor->ComSetValue(_T("M870"), FALSE);
}
//主机启动
void CMotorLpDlg::ClickStart()
{
	
}

//自动
void CMotorLpDlg::LButtonDownZiDong(long ID, LPCTSTR addr, long other)
{
	LONG value = FALSE;
	m_pMotor->ComGetValue(_T("M70"), &value);
	if (value != FALSE)
	{
		
		return;
	}
	m_pMotor->ComSetValue(_T("M56"), TRUE);
}

//自动
void CMotorLpDlg::LButtonUpZiDong(long ID, LPCTSTR addr, long other)
{
	LONG value = FALSE;
	m_pMotor->ComGetValue(_T("M70"), &value);
	if (value != FALSE)
	{
		AfxMessageBox(_T("自动开启失败:M70为真"));
		return;
	}
	m_pMotor->ComSetValue(_T("M56"), FALSE);
}

void CMotorLpDlg::ClickZiDong()
{
	LONG value = FALSE;
	m_pMotor->ComGetValue(_T("M70"), &value);
	if (value != FALSE)
	{
		AfxMessageBox(_T("自动开启失败:M70为真"));
		return;
	}
	m_pMotor->ComSetValue(_T("M56"), TRUE);
	Sleep(Sleep_Time);
	m_pMotor->ComSetValue(_T("M56"), FALSE);
}

//速度变更
void CMotorLpDlg::ClickChSpeed()
{
	ChSpeed(GetDlgItemInt(IDC_SPEED));
}

//统计清理
void CMotorLpDlg::ClickClear()
{
	ClearData();
}

//伺服按钮取反
INT CMotorLpDlg::buttonChange(CDLF_Button& button, CString addr)
{
	static LONG value = -1;
	value = !value;
	m_pMotor->ComGetValue(addr, &value);
	m_pMotor->ComSetValue(addr, !value);
	showState(button, value);
	return TRUE;
}
//显示按钮状态
INT CMotorLpDlg::showState(CDLF_Button& button, INT value)
{
	BSTR bstrText;
	if (value == FALSE)
	{
		bstrText = ::SysAllocString(_T("水晶_红"));
		button.SetBackName(&bstrText);
	}
	else if (value == TRUE)
	{
		bstrText = ::SysAllocString(_T("水晶_绿"));
		button.SetBackName(&bstrText);
	}
	return TRUE;
}

//网带运行停止
void CMotorLpDlg::ClickWangDai()
{
	
}

//调试模式
void CMotorLpDlg::ClickTiaoShi()
{
	
}

void CMotorLpDlg::ClickTongBu()
{
	buttonChange(m_tongBu, _T("M660"));
}

//计算伺服获取的数据结果
INT CMotorLpDlg::getValue(LONG* data)
{
	data[0] = (USHORT)data[0];
	data[1] = (USHORT)data[1];
	return data[0] + (USHORT)data[1] * 65536;
}

//
INT CMotorLpDlg::setDengValue(INT ID, LONG value)
{
	CDLF_Button* pButton = NULL;
	pButton = (CDLF_Button*)GetDlgItem(ID);
	if (pButton->GetState() != value)
	{
		pButton->SetState((USHORT)value);
	}
	
	return TRUE;
}

//指示灯显示
INT CMotorLpDlg::showDeng()
{
	LONG data[20] = { 0 };
	LONG value = 0;
	CString sTmp;
	enum
	{
		D_Zero = 4,//原点请求
		D_Over = 5,//原点完成
		D_OFF = 6,//轴OFF
		D_Point = 7,//点动
		D_Place = 8,//定位
	};
	
	//运行状态
	//m_pMotor->ComGetValue(_T("M6"), &value);//获取数据
	//setDengValue(IDC_D_START, !value);
	//自动状态
	//m_pMotor->ComGetValue(_T("M4"), &value);//获取数据
	//setDengValue(IDC_D_SHOU, !value);
	return TRUE;
}

//改变速度
INT CMotorLpDlg::ChSpeed(INT speed)
{
	CSetValueDlg m_setValue;

	ParamStruct data;
	data.m_name = _T("速 度");
	data.m_max = 60;
	data.m_min = 0;

	if (m_pDlg->m_setValueDlg.showDlg(data) == TRUE)
	{
		m_pMotor->ComSetValue(_T("D204"), data);
		Sleep(Sleep_Time);
		m_pMotor->ComSetValue(_T("M870"), TRUE);
		Sleep(Sleep_Time);
		m_pMotor->ComSetValue(_T("M870"), FALSE);
	}
	return TRUE;
}

//清空数据
INT CMotorLpDlg::ClearData()
{
	m_pMotor->ComSetValue(_T("D256"), FALSE);
	m_pMotor->ComSetValue(_T("D257"), FALSE);

	m_pMotor->ComSetValue(_T("D360"), FALSE);
	m_pMotor->ComSetValue(_T("D361"), FALSE);

	m_pMotor->ComSetValue(_T("D356"), FALSE);
	m_pMotor->ComSetValue(_T("D357"), FALSE);
	return TRUE;
}

void CMotorLpDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LONG data[20] = { 0 };
	enum{
		Place = 0,
		Speed = 2,
		Z_Err = 4,
		Z_BJ = 5,
		ALM = 6
	};
	LONG value = 0;
	CString sTmp;
	m_pMotor->ComGetValue(_T("D510"), data, 10);//获取数据
	//速度
	SetDlgItemInt(IDC_SPEED1, getValue(&data[0]));
	SetDlgItemInt(IDC_SPEED2, getValue(&data[2]));
	SetDlgItemInt(IDC_SPEED3, getValue(&data[4]));
	SetDlgItemInt(IDC_SPEED4, getValue(&data[6]));
	
	//位置
	m_pMotor->ComGetValue(_T("D500"), data, 10);//获取数据
	SetDlgItemInt(IDC_PLACE1, getValue(&data[0]));
	SetDlgItemInt(IDC_PLACE2, getValue(&data[2]));
	SetDlgItemInt(IDC_PLACE3, getValue(&data[4]));
	SetDlgItemInt(IDC_PLACE4, getValue(&data[6]));

	//速度 位置
	m_pMotor->ComGetValue(_T("D650"), data, 4);//获取数据
	SetDlgItemInt(IDC_SPEED5, getValue(&data[0]));
	SetDlgItemInt(IDC_PLACE5, getValue(&data[2]));

	//轴错误
	m_pMotor->ComGetValue(_T("D518"), data, 8);//获取数据
	SetDlgItemInt(IDC_Z_ERR1, data[0]);
	SetDlgItemInt(IDC_Z_ERR2, data[2]);
	SetDlgItemInt(IDC_Z_ERR3, data[4]);
	SetDlgItemInt(IDC_Z_ERR4, data[6]);

	//轴报警
	m_pMotor->ComGetValue(_T("D526"), data, 8);//获取数据
	SetDlgItemInt(IDC_Z_BJ1, data[0]);
	SetDlgItemInt(IDC_Z_BJ2, data[2]);
	SetDlgItemInt(IDC_Z_BJ3, data[4]);
	SetDlgItemInt(IDC_Z_BJ4, data[6]);

	//伺服ALM
	m_pMotor->ComGetValue(_T("D542"), data, 8);//获取数据
	SetDlgItemInt(IDC_ALM1, data[0]);
	SetDlgItemInt(IDC_ALM2, data[2]);
	SetDlgItemInt(IDC_ALM3, data[4]);
	SetDlgItemInt(IDC_ALM4, data[6]);

	//轴错误
	m_pMotor->ComGetValue(_T("D654"), data, 6);//获取数据
	SetDlgItemInt(IDC_Z_ERR5, data[0]);
	SetDlgItemInt(IDC_Z_BJ5, data[2]);
	SetDlgItemInt(IDC_ALM5, data[4]);
	
	//指示灯
	showDeng();

	//速度
	data[0] = 0;
	data[1] = 0;
	m_pMotor->ComGetValue(_T("D578"), data, 2);//获取数据
	SetDlgItemInt(IDC_SPEED, getValue(data));

	//网带速度
	data[0] = 0;
	m_pMotor->ComGetValue(_T("D578"), data,1);//获取数据
	SetDlgItemInt(IDC_MESH_SPEED, getValue(data));
	/*
	//总数
	//m_pMotor->ComGetValue(_T("D360"), data, 2);//获取数据
	//SetDlgItemInt(IDC_ALL_NUM, getValue(data));
	//废品
	//m_pMotor->ComGetValue(_T("D256"), data, 2);//获取数据
	//SetDlgItemInt(IDC_BAD_NUM, getValue(data));
	//网袋
	static LONG state[3] = {0};
	m_pMotor->ComGetValue(_T("D105"), data, 1);//获取数据
	if (state[0] != data[0])
	{
		state[0] = data[0];
		//showState(m_wangDai, !data[0]);
	}
	//调试
	m_pMotor->ComGetValue(_T("M64"), data);//获取数据
	if (state[1] != data[0])
	{
		state[1] = data[0];
		//showState(m_tiaoShi, !data[0]);
	}
	//同步控制
	m_pMotor->ComGetValue(_T("M851"), data);//获取数据
	if (state[2] != data[0])
	{
		state[2] = data[0];
		//showState(m_tongBu, !data[0]);
	}
	*/
}


void CMotorLpDlg::OnBnClickedChSpeed()
{
	
}
