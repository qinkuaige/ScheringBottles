// MotorLpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "MotorLpDlg.h"
#include "afxdialogex.h"
#include "DetectionDlg.h"

// CMotorLpDlg �Ի���

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


// CMotorLpDlg ��Ϣ�������
// CMotorLpDlg ��Ϣ�������
INT CMotorLpDlg::initDialog(CDetectionDlg* parentDlg)
{
	m_pDlg = parentDlg;
	if (Create(IDD, m_pDlg) == FALSE)
	{
		AfxMessageBox(_T("����ؽ��洴��ʧ�ܣ�"));
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
	//��ת
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


	//��ת
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


	//����
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

	//����ԭ��
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

	//����ֹͣ
	ON_EVENT(CMotorLpDlg, IDC_STOP, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_STOP, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//�ֶ�
	ON_EVENT(CMotorLpDlg, IDC_SHOU_DONG, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_SHOU_DONG, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)

	//��λ
	ON_EVENT(CMotorLpDlg, IDC_CLEAR_ERR, 1, CMotorLpDlg::LButtonDownUp1, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_CLEAR_ERR, 2, CMotorLpDlg::LButtonUpUp1, VTS_I4 VTS_BSTR VTS_I4)
	
	
	//�ٶȱ��
	ON_EVENT(CMotorLpDlg, IDC_CH_SPEED, DISPID_CLICK, CMotorLpDlg::ClickChSpeed, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_CLEAR, DISPID_CLICK, CMotorLpDlg::ClickClear, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_TIAO_SHI, DISPID_CLICK, CMotorLpDlg::ClickTiaoShi, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_TONG_BU, DISPID_CLICK, CMotorLpDlg::ClickTongBu, VTS_NONE)
	ON_EVENT(CMotorLpDlg, IDC_START, 1, CMotorLpDlg::LButtonDownStart, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_START, 2, CMotorLpDlg::LButtonUpStart, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_ZI_DONG, 1, CMotorLpDlg::LButtonDownZiDong, VTS_I4 VTS_BSTR VTS_I4)
	ON_EVENT(CMotorLpDlg, IDC_ZI_DONG, 2, CMotorLpDlg::LButtonUpZiDong, VTS_I4 VTS_BSTR VTS_I4)
END_EVENTSINK_MAP()

//�㶯 down
void CMotorLpDlg::LButtonDownUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, TRUE);
}

//�㶯 up
void CMotorLpDlg::LButtonUpUp1(long ID, LPCTSTR addr, long other)
{
	m_pMotor->ComSetValue(addr, FALSE);
}


//��������
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
//��������
void CMotorLpDlg::ClickStart()
{
	
}

//�Զ�
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

//�Զ�
void CMotorLpDlg::LButtonUpZiDong(long ID, LPCTSTR addr, long other)
{
	LONG value = FALSE;
	m_pMotor->ComGetValue(_T("M70"), &value);
	if (value != FALSE)
	{
		AfxMessageBox(_T("�Զ�����ʧ��:M70Ϊ��"));
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
		AfxMessageBox(_T("�Զ�����ʧ��:M70Ϊ��"));
		return;
	}
	m_pMotor->ComSetValue(_T("M56"), TRUE);
	Sleep(Sleep_Time);
	m_pMotor->ComSetValue(_T("M56"), FALSE);
}

//�ٶȱ��
void CMotorLpDlg::ClickChSpeed()
{
	ChSpeed(GetDlgItemInt(IDC_SPEED));
}

//ͳ������
void CMotorLpDlg::ClickClear()
{
	ClearData();
}

//�ŷ���ťȡ��
INT CMotorLpDlg::buttonChange(CDLF_Button& button, CString addr)
{
	static LONG value = -1;
	value = !value;
	m_pMotor->ComGetValue(addr, &value);
	m_pMotor->ComSetValue(addr, !value);
	showState(button, value);
	return TRUE;
}
//��ʾ��ť״̬
INT CMotorLpDlg::showState(CDLF_Button& button, INT value)
{
	BSTR bstrText;
	if (value == FALSE)
	{
		bstrText = ::SysAllocString(_T("ˮ��_��"));
		button.SetBackName(&bstrText);
	}
	else if (value == TRUE)
	{
		bstrText = ::SysAllocString(_T("ˮ��_��"));
		button.SetBackName(&bstrText);
	}
	return TRUE;
}

//��������ֹͣ
void CMotorLpDlg::ClickWangDai()
{
	
}

//����ģʽ
void CMotorLpDlg::ClickTiaoShi()
{
	
}

void CMotorLpDlg::ClickTongBu()
{
	buttonChange(m_tongBu, _T("M660"));
}

//�����ŷ���ȡ�����ݽ��
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

//ָʾ����ʾ
INT CMotorLpDlg::showDeng()
{
	LONG data[20] = { 0 };
	LONG value = 0;
	CString sTmp;
	enum
	{
		D_Zero = 4,//ԭ������
		D_Over = 5,//ԭ�����
		D_OFF = 6,//��OFF
		D_Point = 7,//�㶯
		D_Place = 8,//��λ
	};
	
	//����״̬
	//m_pMotor->ComGetValue(_T("M6"), &value);//��ȡ����
	//setDengValue(IDC_D_START, !value);
	//�Զ�״̬
	//m_pMotor->ComGetValue(_T("M4"), &value);//��ȡ����
	//setDengValue(IDC_D_SHOU, !value);
	return TRUE;
}

//�ı��ٶ�
INT CMotorLpDlg::ChSpeed(INT speed)
{
	CSetValueDlg m_setValue;

	ParamStruct data;
	data.m_name = _T("�� ��");
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

//�������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	m_pMotor->ComGetValue(_T("D510"), data, 10);//��ȡ����
	//�ٶ�
	SetDlgItemInt(IDC_SPEED1, getValue(&data[0]));
	SetDlgItemInt(IDC_SPEED2, getValue(&data[2]));
	SetDlgItemInt(IDC_SPEED3, getValue(&data[4]));
	SetDlgItemInt(IDC_SPEED4, getValue(&data[6]));
	
	//λ��
	m_pMotor->ComGetValue(_T("D500"), data, 10);//��ȡ����
	SetDlgItemInt(IDC_PLACE1, getValue(&data[0]));
	SetDlgItemInt(IDC_PLACE2, getValue(&data[2]));
	SetDlgItemInt(IDC_PLACE3, getValue(&data[4]));
	SetDlgItemInt(IDC_PLACE4, getValue(&data[6]));

	//�ٶ� λ��
	m_pMotor->ComGetValue(_T("D650"), data, 4);//��ȡ����
	SetDlgItemInt(IDC_SPEED5, getValue(&data[0]));
	SetDlgItemInt(IDC_PLACE5, getValue(&data[2]));

	//�����
	m_pMotor->ComGetValue(_T("D518"), data, 8);//��ȡ����
	SetDlgItemInt(IDC_Z_ERR1, data[0]);
	SetDlgItemInt(IDC_Z_ERR2, data[2]);
	SetDlgItemInt(IDC_Z_ERR3, data[4]);
	SetDlgItemInt(IDC_Z_ERR4, data[6]);

	//�ᱨ��
	m_pMotor->ComGetValue(_T("D526"), data, 8);//��ȡ����
	SetDlgItemInt(IDC_Z_BJ1, data[0]);
	SetDlgItemInt(IDC_Z_BJ2, data[2]);
	SetDlgItemInt(IDC_Z_BJ3, data[4]);
	SetDlgItemInt(IDC_Z_BJ4, data[6]);

	//�ŷ�ALM
	m_pMotor->ComGetValue(_T("D542"), data, 8);//��ȡ����
	SetDlgItemInt(IDC_ALM1, data[0]);
	SetDlgItemInt(IDC_ALM2, data[2]);
	SetDlgItemInt(IDC_ALM3, data[4]);
	SetDlgItemInt(IDC_ALM4, data[6]);

	//�����
	m_pMotor->ComGetValue(_T("D654"), data, 6);//��ȡ����
	SetDlgItemInt(IDC_Z_ERR5, data[0]);
	SetDlgItemInt(IDC_Z_BJ5, data[2]);
	SetDlgItemInt(IDC_ALM5, data[4]);
	
	//ָʾ��
	showDeng();

	//�ٶ�
	data[0] = 0;
	data[1] = 0;
	m_pMotor->ComGetValue(_T("D578"), data, 2);//��ȡ����
	SetDlgItemInt(IDC_SPEED, getValue(data));

	//�����ٶ�
	data[0] = 0;
	m_pMotor->ComGetValue(_T("D578"), data,1);//��ȡ����
	SetDlgItemInt(IDC_MESH_SPEED, getValue(data));
	/*
	//����
	//m_pMotor->ComGetValue(_T("D360"), data, 2);//��ȡ����
	//SetDlgItemInt(IDC_ALL_NUM, getValue(data));
	//��Ʒ
	//m_pMotor->ComGetValue(_T("D256"), data, 2);//��ȡ����
	//SetDlgItemInt(IDC_BAD_NUM, getValue(data));
	//����
	static LONG state[3] = {0};
	m_pMotor->ComGetValue(_T("D105"), data, 1);//��ȡ����
	if (state[0] != data[0])
	{
		state[0] = data[0];
		//showState(m_wangDai, !data[0]);
	}
	//����
	m_pMotor->ComGetValue(_T("M64"), data);//��ȡ����
	if (state[1] != data[0])
	{
		state[1] = data[0];
		//showState(m_tiaoShi, !data[0]);
	}
	//ͬ������
	m_pMotor->ComGetValue(_T("M851"), data);//��ȡ����
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
