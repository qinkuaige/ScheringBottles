#include "stdafx.h"
#include "MotorSL.h"
#include "Control.h"

CMotorSL::CMotorSL()
	:m_GUID(FALSE)//���
	, m_state(State_DisConnect)//�����ŷ�״̬
	, m_isRun(FALSE)//�豸������״̬
	, m_permission(FALSE)//Ȩ��
	, m_pStartFlag(NULL)//
	, m_speed(FALSE)//���������ٶ�
	, m_collectT(NULL)//�ɼ��߳�
	, m_collectFlag(FALSE)//�ɼ���־λ
	, m_pMotor(NULL)//�ŷ�����
	, m_allNum(FALSE)//PLCͳ������
	, m_allBad(FALSE)//PLCͳ���ܷ�Ʒ��
{
	InitializeCriticalSection(&m_cs);//��ʼ���ٽ���  
	for (INT i = 0; i < 255; ++i)
	{
		m_errState[i] = 0;
	}
}


CMotorSL::~CMotorSL()
{
	ComDisConnect();
}

//��ʼ����
INT CMotorSL::ComInit(CWnd* parentDlg, CControl* control, UINT GUID, INT permission)
{
	m_GUID = GUID;//�������
	m_permission = permission;//����Ȩ��
	m_pControl = control;
	PriCreateMotor(parentDlg);
	return TRUE;
}

//�����豸
INT CMotorSL::ComConnect(UINT Channel)
{
	CString	MsgStr;
	CString str;
	str.Format(_T("%d"), Channel);
	if (Channel > 1024)
	{
		AfxMessageBox(_T("�ŷ�����վ��ų���Χ(0-1024):") + Channel);
		return FALSE;
	}
	if (State_Connect == m_state)
	{
		AfxMessageBox(_T("�ŷ�����Ѿ�������"));
		return TRUE;
	}
	try{
		//����PLCվ��
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
			AfxMessageBox(_T("վ��:") + str + _T("�ŷ��������ʧ�ܣ�������:") + str1);
			return FALSE;
		}
	}
	catch (INT w){
		int x = w;
		AfxMessageBox(_T("վ��:") + str + _T("�ŷ��������ʧ�ܣ�"));
		return FALSE;
	}
	//��ȡ��ǰ�ٶ�
	LONG value1 = FALSE;
	LONG value2 = FALSE;
	ComGetValue(_T("D578"), &value1);
	ComGetValue(_T("D579"), &value2);
	m_speed = value1 + value2 * 65536;

	//����λ
	ComResetErr();

	//�����ɼ��߳�
	PriOpenThread();
	return TRUE;
}

//�Ͽ�����
INT CMotorSL::ComDisConnect()
{
	if (m_state == State_DisConnect)
	{
		return TRUE;
	}
	ComStop();
	PriCloseThread();
	m_pMotor->Close();//�Ͽ��ŷ�����
	m_state = State_DisConnect;
	return TRUE;
}

//�豸����
INT CMotorSL::ComStart()
{
	if (m_state == State_DisConnect)
	{
		AfxMessageBox(_T("�ŷ�δ����"));
		return FALSE;
	}
	//����λ
	ComResetErr();

	//��������
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

	//�����豸
	AfxBeginThread(PriStartThread, this);
	//�򿪲ɼ��߳�
	PriOpenThread();
	return TRUE;
}

//�豸ֹͣ
INT CMotorSL::ComStop()
{
	if (m_state == State_DisConnect)
	{
		AfxMessageBox(_T("�ŷ�δ����"));
		return FALSE;
	}

	//ֹͣ�豸
	PriStopFun();
	//�رղɼ��߳�
	PriCloseThread();
	m_isRun = FALSE;
	m_state = State_Stop;
	return TRUE;
}

//�����ŷ���ַ��ֵ
INT CMotorSL::ComSetValue(CString addr, long value)
{
	if (m_state == State_DisConnect)
	{
		return FALSE;
	}
	//EnterCriticalSection(&m_cs);//�����ٽ��� 
	m_pMotor->SetDevice(addr, value);
	//LeaveCriticalSection(&m_cs);//�뿪�ٽ��� 
	return TRUE;
}

//��ȡ�ŷ���ַ��ֵ
INT CMotorSL::ComGetValue(CString addr, long* value)
{
	if (m_state == State_DisConnect || value == NULL)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//�����ٽ��� 
	m_pMotor->GetDevice(addr, value);
	LeaveCriticalSection(&m_cs);//�뿪�ٽ��� 
	return TRUE;
}

//��ȡ�ŷ�X��ַ
INT CMotorSL::ComGetValueX(CString addr, long* value, INT num)
{
	if (m_state == State_DisConnect || value == NULL)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//�����ٽ��� 
	m_pMotor->ReadDeviceRandom(addr, num, value);
	LeaveCriticalSection(&m_cs);//�뿪�ٽ��� 
	return TRUE;
}

//������ȡ�ŷ���ַ��ֵ
INT CMotorSL::ComGetValue(CString addr, long* value, INT num)
{
	if (m_state == State_DisConnect || value == NULL || num <= 0)
	{
		return FALSE;
	}
	EnterCriticalSection(&m_cs);//�����ٽ��� 
	m_pMotor->ReadDeviceBlock(addr, num, value);
	LeaveCriticalSection(&m_cs);//�뿪�ٽ��� 
	return TRUE;
}

//����ȡͼ��ʶλ
INT CMotorSL::ComSetGrabFlag(INT GUID, INT* grabFlag)
{
	m_pStartFlag = grabFlag;
	return TRUE;
}

//��ȡ�豸�����ٶ�
INT CMotorSL::ComGetSpeed()
{
	return m_speed;
}

//�����ٶ�
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

//��ȡ������Ϣ
INT CMotorSL::ComGetErr(vector<CString>& str)
{
	LONG data[3] = { 0 };
	ComGetValue(_T("D0"), data, 3);

	
	str.clear();//
	INT sub = 0;//������
	PriGetErr((data[0] >> 0) & 1, _T("����ͣ����ť1���£�"), str, sub++);
	PriGetErr((data[0] >> 1) & 1, _T("����ͣ����ť2���£�"), str, sub++);
	PriGetErr((data[0] >> 2) & 1, _T("��Ƶ��������"), str, sub++);
	PriGetErr((data[0] >> 3) & 1, _T("Q2���ر�����"), str, sub++);
	PriGetErr((data[0] >> 4) & 1, _T("Q3���ر�����"), str, sub++);
	PriGetErr((data[0] >> 5) & 1, _T("�Ŵ򿪣�"), str, sub++);


	PriGetErr((data[1] >> 0) & 1, _T("1�ż����������"), str, sub++);
	PriGetErr((data[1] >> 1) & 1, _T("2�ż����������"), str, sub++);
	PriGetErr((data[1] >> 2) & 1, _T("3�ż����������"), str, sub++);
	PriGetErr((data[1] >> 3) & 1, _T("4�ż����������"), str, sub++);
	PriGetErr((data[1] >> 4) & 1, _T("5�ż����������"), str, sub++);
	PriGetErr((data[1] >> 5) & 1, _T("6�ż����������"), str, sub++);


	PriGetErr((data[2] >> 0) & 1, _T("1������⣡"), str, sub++);
	PriGetErr((data[2] >> 1) & 1, _T("2������⣡"), str, sub++);
	PriGetErr((data[2] >> 2) & 1, _T("3������⣡"), str, sub++);
	PriGetErr((data[2] >> 3) & 1, _T("4������⣡"), str, sub++);
	PriGetErr((data[2] >> 4) & 1, _T("5������⣡"), str, sub++);

	PriGetErr((data[2] >> 5) & 1, _T("1�ᱨ����⣡"), str, sub++);
	PriGetErr((data[2] >> 6) & 1, _T("2�ᱨ����⣡"), str, sub++);
	PriGetErr((data[2] >> 7) & 1, _T("3�ᱨ����⣡"), str, sub++);
	PriGetErr((data[2] >> 8) & 1, _T("4�ᱨ����⣡"), str, sub++);
	PriGetErr((data[2] >> 9) & 1, _T("5�ᱨ����⣡"), str, sub++);

	PriGetErr((data[2] >> 10) & 1, _T("1���ŷ�״̬������"), str, sub++);
	PriGetErr((data[2] >> 11) & 1, _T("2���ŷ�״̬������"), str, sub++);
	PriGetErr((data[2] >> 12) & 1, _T("3���ŷ�״̬������"), str, sub++);
	PriGetErr((data[2] >> 13) & 1, _T("4���ŷ�״̬������"), str, sub++);
	PriGetErr((data[2] >> 14) & 1, _T("5���ŷ�״̬������"), str, sub++);
	
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

//����λ
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
//��������
INT CMotorSL::ComClearData()
{
	ComSetValue(_T("M420"), TRUE);
	Sleep(300);
	ComSetValue(_T("M420"), FALSE);
	return TRUE;
}
//�����ŷ����
INT CMotorSL::PriCreateMotor(CWnd* parent)
{
	if (m_pMotor != NULL)
	{
		delete m_pMotor;
		m_pMotor = NULL;
	}
	//�õ��ŷ����ָ��
	m_pMotor = new CActutltype1;
	INT res = m_pMotor->Create(_T(""), _T(""), WS_CHILD, CRect(0, 0, 10, 10), parent, Dlg_ID);
	if (res == FALSE)
	{
		delete m_pMotor;
		m_pMotor = NULL;
		AfxMessageBox(_T("�ŷ��������ʧ�ܣ�"));
		return FALSE;
	}
	
	return TRUE;
}

//�ɼ��߳�
UINT CMotorSL::PriCollectThread(LPVOID lparam)
{
	CMotorSL* parent = (CMotorSL*)lparam;
	parent->PriCollectFun();
	return TRUE;
}

//�ɼ�����
INT CMotorSL::PriCollectFun()
{
	LONG start = -1;
	LONG upDown = -1;
	LONG value = 0;
	LONG data[20] = { 0 };
	LONG isErr = 0;
	enum
	{
		Speed = 0,//�ٶ�
		All_Num = 1,//����
		Bad_Num = 3,//��Ʒ��

	};
	m_collectFlag = TRUE;
	while (m_collectFlag)
	{
		//ʵ�»�ȡplc��������
		ComGetValue(_T("D3"), m_data, Plc_Data_Num);
		if ((m_data[0] >> 5) & 1)//�����ػ����½��ش�������
		{
			isErr = TRUE;
			vector<CString> errInfo;
			if (ComGetErr(errInfo))
			{
				m_pControl->ComInsertErr(errInfo);//������Ϣ���浽���ݿ�
			}
		}
		
		m_isRun = ((m_data[0] >> 4) & 1) && ((m_data[0] >> 0) & 1);//�����豸����״̬������״̬Ϊ1 ��ͬ��Ϊ1��ʱ����㿪����
		if (m_isRun != TRUE)//ͣ��״̬
		{
			Sleep(20);
			continue;
		}
		//��ȡPLC������
		m_allNum = m_data[1] + m_data[2] * 65536;
		m_allBad = m_data[3] + m_data[4] * 65536;

		value = (m_data[0] >> 1) & 1;//��λ�ź�
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
						str.Format(_T("��ѹ��%d���ݲɼ���ʱ"), i + 1);
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

//�����߳�
UINT CMotorSL::PriStartThread(LPVOID lParam)
{
	static INT isRun = FALSE;//�����̲߳��ظ�����
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

//�豸�������̺���
INT CMotorSL::PriStartFun()
{
	LONG value = FALSE;
	
	//ͬ��
	ComGetValue(_T("M660"), &value);
	if (value == FALSE)//�ж��Ƿ���ͬ��
	{
		//ԭ��ع�
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
			if (time > 0)//��ʱ
			{
				--time;
			}
			else
			{
				AfxMessageBox(_T("������ʱ��"));
				return FALSE;
			}
			Sleep(200);
		}
		//��ʼͬ��
		ComSetValue(_T("M660"), TRUE);
	}//�ж��Ƿ���ͬ��

	//�رջ�е����
	ComSetValue(_T("M631"), FALSE);
	//��������
	ComSetValue(_T("M670"), TRUE);
	Sleep(500);
	ComSetValue(_T("M670"), FALSE);

	//����״̬
	m_state = State_Start;
	return TRUE;
}

//ͣ���߳�
UINT CMotorSL::PriStopThread(LPVOID lParam)
{
	CMotorSL* parent = (CMotorSL*)lParam;
	parent->PriStopFun();
	return TRUE;
}

//�豸ֹͣ���̺���
INT CMotorSL::PriStopFun()
{
	//����ֹͣ
	ComSetValue(_T("M642"), TRUE);
	Sleep(500);
	ComSetValue(_T("M642"), FALSE);
	
	return TRUE;
}



//�򿪲ɼ��߳�
INT CMotorSL::PriOpenThread()
{
	if (m_collectFlag == TRUE)//����߳�û�б��ر���ֱ�ӷ���
	{
		return TRUE;
	}
	m_collectFlag = TRUE;
	//�����ɼ��߳�
	m_collectT = AfxBeginThread(PriCollectThread, this);
	return TRUE;
}

//�ر��߳�
INT CMotorSL::PriCloseThread()
{
	PriStopOneThread(&m_collectFlag,m_collectT, 200);
	return TRUE;
}

//�ر�һ���߳�
INT CMotorSL::PriStopOneThread(INT* falg,CWinThread* pThread, INT waitTime)
{
	if (*falg != TRUE)
	{
		return TRUE;
	}
	*falg = FALSE;

	HRESULT hResult = ERROR_SUCCESS;
	//�ȴ�ȡͼ�߳̽���
	if (pThread != NULL && WaitForSingleObject(pThread->m_hThread, waitTime) != WAIT_OBJECT_0)
	{
		INT res = TerminateThread(pThread->m_hThread, 0);//ǿ�ƹر��߳�
		if (!res)//��ȡΪʲôû�йر��̵߳�ԭ��
		{
			hResult = ::GetLastError();
		}
		//�ж��߳��Ƿ���Ч ��Ч������߳�
		if (hResult != ERROR_INVALID_HANDLE)
		{
			delete pThread;
		}
		pThread = NULL;
	}
	return TRUE;
}

//�����ŷ���ȡ�����ݽ��
INT CMotorSL::PriGetValue(LONG* data)
{
	data[0] = (USHORT)data[0];
	data[1] = (USHORT)data[1];
	return data[0] + (USHORT)data[1] * 65536;
}

//��ȡ����������Ϣ
INT CMotorSL::PriGetErr(CString addr, CString message, vector<CString>& str, INT sub)
{
	LONG value;
	ComGetValue(addr, &value);
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