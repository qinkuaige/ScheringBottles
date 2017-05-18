#pragma once
#include "actutltype1.h"
#include <vector>
#include <map>
using namespace std;

enum{
	P_Speed = 0,//�ٶ�
	P_AllNum = 1,//����
	P_BadNum = 3,//��Ʒ��
	P_WDai = 5,//����״̬
	P_ZJi = 6,//��������״̬
	P_Grab = 7,//�ɼ��ź�
	P_BJin = 8,//����
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
		State_DisConnect = 0,//�豸�Ͽ�����״̬
		State_Connect,	//�豸����״̬
		State_Start,
		State_Stop,
		Dlg_ID = 4100,		//
		Plc_Data_Num = 5,//�����ɼ�plc���� ����
		Max_Motor_Speed = 120,//�ŷ���������ٶ�
	};
	
	enum
	{
		PLC_X = 0,
		PLC_M = 0,
		PLC_D = 0,
	};
public:
	virtual INT ComInit(CWnd* parentDlg, CControl* control, UINT GUID = FALSE, INT permission = FALSE);//��ʼ����
	//�ŷ�����
	virtual INT ComConnect(UINT Channel = TRUE);//�����豸
	virtual INT ComDisConnect();//�Ͽ�����
	virtual INT ComStart();//�豸����
	virtual INT ComStop();//�豸ֹͣ
	//virtual INT ComGetErr(vector<CString> err){ return FALSE; };//��ȡ������Ϣ
	virtual INT ComSetValue(CString addr, long value);//�����ŷ���ַ��ֵ
	virtual INT ComGetValue(CString addr, long* value);//��ȡ�ŷ���ַ��ֵ
	virtual INT ComGetValueX(CString addr, long* value, INT num = TRUE);//��ȡ�ŷ�X��ַ
	virtual INT ComGetValue(CString addr, long* value, INT num);//������ȡ�ŷ���ַ��ֵ
	virtual INT ComSetGrabFlag(INT GUID, INT* grabFlag);//����ȡͼ��ʶλ
	virtual INT ComGetSpeed();//��ȡ�豸�����ٶ�
	virtual INT ComSetSpeed(LONG value);//�����ٶ�
	virtual INT ComGetErr(vector<CString>& str);//��ȡ������Ϣ
	virtual INT ComResetErr();//����λ
	virtual INT ComClearData();//��������
private:
	INT PriCreateMotor(CWnd* parent);//��������
	static UINT PriCollectThread(LPVOID lparam);//�ɼ��߳�
	INT PriCollectFun();//�ɼ�����
	static UINT PriStartThread(LPVOID lParam);//�����߳�
	INT PriStartFun();//�豸�������̺���
	static UINT PriStopThread(LPVOID lParam);//ͣ���߳�
	INT PriStopFun();//�豸ֹͣ���̺���
	INT PriOpenThread();//�����߳�
	INT PriCloseThread();//�ر��߳�
	INT PriStopOneThread(INT* falg,CWinThread* pThread, INT waitTime);//�ر�һ���߳�
	INT PriGetValue(LONG* data);
	INT PriGetErr(CString addr, CString message, vector<CString>& str, INT sub = 0);//��ȡ����������Ϣ
	//��ȡ����������Ϣ
	inline INT PriGetErr(INT value ,CString message, vector<CString>& str, INT sub = 0)
	{
		if (value != m_errState[sub])//�ж��Ƿ����µı���
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
	CControl* m_pControl;//���߼���
public:
	INT m_GUID;//���
	INT m_state;//�����ŷ�״̬
	INT m_isRun;//�豸������״̬
	INT m_permission;//Ȩ��
	INT* m_pStartFlag;//
	INT m_speed;//���������ٶ�
	CWinThread* m_collectT;//�ɼ��߳�
	INT m_collectFlag;//�ɼ���־λ
	INT Motor_ID;//
	CRITICAL_SECTION m_cs;//�ٽ���
	LONG m_data[Plc_Data_Num];//����PLC����
	INT m_errState[255];//����״̬
	INT m_allNum;//PLCͳ������
	INT m_allBad;//PLCͳ���ܷ�Ʒ��
};

