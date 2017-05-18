// MotorRDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Detection.h"
#include "MotorRDDlg.h"
#include "afxdialogex.h"


// CMotorRDDlg 对话框

IMPLEMENT_DYNAMIC(CMotorRDDlg, CDialogEx)

CMotorRDDlg::CMotorRDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorRDDlg::IDD, pParent)
{

}

CMotorRDDlg::~CMotorRDDlg()
{
}

void CMotorRDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TONG_BU, m_tongBuBT);
	DDX_Control(pDX, IDC_TEST_MOTOR, m_testMotorBT);
	DDX_Control(pDX, IDC_DI_YA, m_diYa);
}


BEGIN_MESSAGE_MAP(CMotorRDDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CH_SPEED, &CMotorRDDlg::OnBnClickedChSpeed)
END_MESSAGE_MAP()


// CMotorRDDlg 消息处理程序
INT CMotorRDDlg::initDialog(CDetectionDlg* parentDlg)
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

INT CMotorRDDlg::showDialog(INT dlgID)
{
	if (dlgID == IDD)
	{
		SetTimer(2000, 1000, NULL);
		SetTimer(3000, 1000, NULL);
		SetTimer(4000, 1000, NULL);
		SetTimer(5000, 1000, NULL);
		ShowWindow(SW_SHOW);
	}
	else
	{
		KillTimer(2000);
		KillTimer(3000);
		KillTimer(4000);
		KillTimer(5000);
		ShowWindow(SW_HIDE);
	}
	return TRUE;
}

//改变速度
INT CMotorRDDlg::ChSpeed(INT speed)
{
	m_pMotor->ComSetSpeed(speed);
	return TRUE;
}

//清空数据
INT CMotorRDDlg::ClearData()
{
	m_pMotor->ComClearData();
	return TRUE;
} 



//计算伺服获取的数据结果
INT CMotorRDDlg::getValue(LONG* data)
{
	data[0] = (USHORT)data[0];
	data[1] = (USHORT)data[1];
	return data[0] + (USHORT)data[1] * 65536;
}

BEGIN_EVENTSINK_MAP(CMotorRDDlg, CDialogEx)
	//正转
	ON_EVENT(CMotorRDDlg, IDC_UP1, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP1, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP2, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP2, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP3, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP3, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP4, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP4, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP5, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_UP5, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)


	//反转
	ON_EVENT(CMotorRDDlg, IDC_DOWN1, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN1, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN2, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN2, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN3, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN3, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN4, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN4, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN5, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_DOWN5, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)


	//回零
	ON_EVENT(CMotorRDDlg, IDC_BACK1, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK1, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK2, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK2, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK3, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK3, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK4, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK4, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK5, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK5, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//设置原点
	ON_EVENT(CMotorRDDlg, IDC_SET1, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET1, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET2, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET2, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET3, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET3, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET4, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET4, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET5, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_SET5, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	//主控制
	//开机做的单独函数
	//ON_EVENT(CMotorRDDlg, IDC_START, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	//ON_EVENT(CMotorRDDlg, IDC_START, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//停止
	ON_EVENT(CMotorRDDlg, IDC_STOP, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_STOP, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	//错误复位
	ON_EVENT(CMotorRDDlg, IDC_RESE_ERR, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_RESE_ERR, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//错误复位2
	ON_EVENT(CMotorRDDlg, IDC_RESE_ERR2, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_RESE_ERR2, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	//原点回归
	ON_EVENT(CMotorRDDlg, IDC_BACK_ZERO, 1, CMotorRDDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorRDDlg, IDC_BACK_ZERO, 2, CMotorRDDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	ON_EVENT(CMotorRDDlg, IDC_TONG_BU, DISPID_CLICK, CMotorRDDlg::ClickTongBu, VTS_NONE) //同步
	ON_EVENT(CMotorRDDlg, IDC_START, DISPID_CLICK, CMotorRDDlg::ClickStart, VTS_NONE) //开机
	
	ON_EVENT(CMotorRDDlg, IDC_TEST_MOTOR, DISPID_CLICK, CMotorRDDlg::ClickTestMotor, VTS_NONE)  //机械调试
	ON_EVENT(CMotorRDDlg, IDC_DI_YA, DISPID_CLICK, CMotorRDDlg::ClickDiYa, VTS_NONE)  //低压有效
END_EVENTSINK_MAP()


//按钮按下，给相应的地址置1
void CMotorRDDlg::LButtonDownUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, TRUE);
}

//按键抬起，给相应的地址置0
void CMotorRDDlg::LButtonUpUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, FALSE);
}


void CMotorRDDlg::OnTimer(UINT_PTR nIDEvent)
{
	static INT state[10] = { 0 };

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
	if (nIDEvent == 2000)
	{
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
	}
	else if (nIDEvent == 3000)
	{
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

	}
	else if (nIDEvent == 4000)
	{
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
	}
	else if (nIDEvent == 5000)
	{
		//轴错误
		m_pMotor->ComGetValue(_T("D654"), data, 6);//获取数据
		SetDlgItemInt(IDC_Z_ERR5, data[0]);
		SetDlgItemInt(IDC_Z_BJ5, data[2]);
		SetDlgItemInt(IDC_ALM5, data[6]);

		//速度
		data[0] = 0;
		data[1] = 0;
		m_pMotor->ComGetValue(_T("D578"), data, 2);//获取数据
		SetDlgItemInt(IDC_SPEED, getValue(data));
		{
			//获取同步状态
			LONG value = FALSE;
			BSTR bstrText;
			m_pMotor->ComGetValue(_T("M660"), &value);
			if (value == TRUE)
			{
				bstrText = ::SysAllocString(_T("水晶_红"));
				m_tongBuBT.SetBackName(&bstrText);
			}
			else if (value == FALSE)
			{
				bstrText = ::SysAllocString(_T("水晶_绿"));
				m_tongBuBT.SetBackName(&bstrText);
			}
		}
		{
			//获取同步状态
			LONG value = FALSE;
			BSTR bstrText;
			m_pMotor->ComGetValue(_T("M631"), &value);
			if (value == TRUE)
			{
				bstrText = ::SysAllocString(_T("水晶_红"));
				m_testMotorBT.SetBackName(&bstrText);
			}
			else if (value == FALSE)
			{
				bstrText = ::SysAllocString(_T("水晶_绿"));
				m_testMotorBT.SetBackName(&bstrText);
			}
		}
		{
			//获取同步状态
			LONG value = FALSE;
			BSTR bstrText;
			m_pMotor->ComGetValue(_T("M79"), &value);
			if (value == TRUE)
			{
				bstrText = ::SysAllocString(_T("水晶_红"));
				m_diYa.SetBackName(&bstrText);
			}
			else if (value == FALSE)
			{
				bstrText = ::SysAllocString(_T("水晶_绿"));
				m_diYa.SetBackName(&bstrText);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

//速度变更
void CMotorRDDlg::OnBnClickedChSpeed()
{
	ParamStruct data;
	data.m_max = 120;
	CSetValueDlg setDlg;
	if (setDlg.showDlg(data) == IDYES)
	{
		LONG speed = data;
		ChSpeed(speed);
	}
}

//同步
void CMotorRDDlg::ClickTongBu()
{
	
	LONG data = FALSE;
	m_pMotor->ComGetValue(_T("M660"), &data);
	data = !data;
	m_pMotor->ComSetValue(_T("M660"), data);
	BSTR bstrText;
	if (data == TRUE)
	{
		bstrText = ::SysAllocString(_T("水晶_红"));
		m_tongBuBT.SetBackName(&bstrText);
	}
	else if (data == FALSE)
	{
		bstrText = ::SysAllocString(_T("水晶_绿"));
		m_tongBuBT.SetBackName(&bstrText);
	}
	
}

//开机
void CMotorRDDlg::ClickStart()
{
	LONG data = FALSE;
	m_pMotor->ComGetValue(_T("D3"), &data);

	INT isRun = (data >> 4) & 1;
	if (isRun == FALSE)
	{
		//错误复位
		m_pMotor->ComSetValue(_T("M480"), TRUE);
		Sleep(500);
		m_pMotor->ComSetValue(_T("M480"), FALSE);

		//开机
		m_pMotor->ComSetValue(_T("M670"), TRUE);
		Sleep(500);
		m_pMotor->ComSetValue(_T("M670"), FALSE);
	}
	
}

//机械测试
void CMotorRDDlg::ClickTestMotor()
{
	LONG data = FALSE;
	m_pMotor->ComGetValue(_T("M631"), &data);
	data = !data;
	m_pMotor->ComSetValue(_T("M631"), data);
	BSTR bstrText;
	if (data == TRUE)
	{
		bstrText = ::SysAllocString(_T("水晶_红"));
		m_testMotorBT.SetBackName(&bstrText);
	}
	else if (data == FALSE)
	{
		bstrText = ::SysAllocString(_T("水晶_绿"));
		m_testMotorBT.SetBackName(&bstrText);
	}
}

//低压有效
void CMotorRDDlg::ClickDiYa()
{
	LONG value = FALSE;
	m_pMotor->ComGetValue(_T("M79"), &value);
	value = !value;
	m_pMotor->ComSetValue(_T("M79"), value);
	BSTR bstrText;
	if (value == TRUE)
	{
		bstrText = ::SysAllocString(_T("水晶_红"));
		m_diYa.SetBackName(&bstrText);
	}
	else if (value == FALSE)
	{
		bstrText = ::SysAllocString(_T("水晶_绿"));
		m_diYa.SetBackName(&bstrText);
	}
}
