#include "stdafx.h"
#include "Control.h"
#include "DetectionDlg.h"
CControl* m_this = NULL;
CControl::CControl()
	:m_isConnect(FALSE)//��������״̬
	, m_collectT(NULL)//���������߳�
	, m_collectFlg(FALSE)//�������ݱ�־λ
	, m_startFlag(FALSE)//�ɼ���־λ
	, m_workSubT(FALSE)//ͳ���ù�λ
	, m_isStart(FALSE)//��ʼ����־λ
	, m_isSend(FALSE)//���ͱ��ı�־
{
	m_this = this;
	//��λ
	for (INT i = 0; i < Work_Max; ++i)
	{
		for (INT j = 0; j < CH_Num + 1; ++j)
		{
			m_allWork[i][j] = Empty_Work;
		}
	}
	//��ȡ����·��
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

//��ʼ��
INT CControl::ComInit(CDetectionDlg* parentDlg)
{
	m_parentDlg = parentDlg;
	//���ز���
	PriReadIni();
	//��ʼ��ͨѶ
	CString key;
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		key.Format(_T("ͨ��%d"),i + 1);
		CString addr;
		addr.Format(_T("%02d"), i + 1);
		m_modbus[i].ComInit(parentDlg, this, i, addr);//��ʼ��ͨѶ��
		m_modbus[i].ComLoadParam(key);//����ͨѶ����
		m_modbus[i].ComSetCallBack(dataCallBack);//����ͨѶ�ûص�����
	}
	
	//��ʼ���ŷ�
	m_motor.ComInit(parentDlg,this);

	return TRUE;
}

//�����豸
INT CControl::ComConnect()
{
	if (m_isConnect == TRUE)
	{
		AfxMessageBox(_T("�豸������,�����ظ�����"));
		return FALSE;
	}
	m_isConnect = TRUE;//�豸���ӱ�־λ

	
	//�������ݿ�
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
	
	//����ͨѶ
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComConnect();//����com��
		//��ȡ�䷽
		m_modbus[i].ComSetRecipeT(_T("ͨ��"));
	}
	
	//�����ŷ�
	m_motor.ComConnect();
	return TRUE;
}

//�Ͽ��豸����
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

//��ʼ���
INT CControl::ComStart()
{
	m_isStart = TRUE;
#ifdef TEST
	//m_startFlag = TRUE;
	//���Ա�������
	
#endif
	return m_motor.ComStart();//�ŷ�����;
}

//ֹͣ���
INT CControl::ComStop()
{
	m_isStart = FALSE;
	//m_access.ComUpData();
	PriInsertRes(0);
	PriInsertResAll();
	return m_motor.ComStop();//�ŷ�ֹͣ
}

//�������
INT CControl::ComClearData()
{
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComClearData();
	}
	return TRUE;
}

//��������Ϣ���뵽���ݿ���
INT CControl::ComInsertErr(vector<CString>& err)
{
	CSQLErr sqlErr;
	if (sqlErr.Open())
	{
		INT size = err.size();
		for (INT i = 0; i < size; ++i)
		{
			sqlErr.AddNew();
			CTime time = ::CTime::GetCurrentTime();//����ʱ��
			sqlErr.m_TI = time.GetTime();
			sqlErr.m_NAME = m_userName;//����ʱ����Ա
			sqlErr.m_INFO = err[i];//������Ϣ
			sqlErr.Update();
		}
	}
	else
	{
		AfxMessageBox(_T("������Ϣ���ݿ��ʧ�ܣ�"));
	}
	return TRUE;
}

//�رճ���
INT CControl::ComExit()
{
	exit(0);
	return TRUE;
}

//��ȡ���ݵĻص�����
INT CControl::dataCallBack(UINT GUID, CByteArray& arry)
{
	m_this->dataFun(GUID, arry);
	return TRUE;
}

//��ȡ���ݵĻص�����
INT CControl::dataFun(UINT GUID, CByteArray& arry)
{
	//1#
	INT sub = m_modbus[GUID].m_workSub1;
	INT res = m_modbus[GUID].m_res1.m_res;
	if (res > m_allWork[sub][CH_Num])//�洢���� ��Ʒ > ��Ʒ > ��λ
	{
		m_allWork[sub][CH_Num] = res;
	}
	//����©���ѹ
	m_allWork[sub][GUID * 2] = m_modbus[GUID].m_lou1;

	//2#
	sub = m_modbus[GUID].m_workSub2;
	res = m_modbus[GUID].m_res2.m_res;
	if (res > m_allWork[sub][CH_Num])//�洢���� ��Ʒ > ��Ʒ > ��λ
	{
		m_allWork[sub][CH_Num] = res;
	}

	//����©���ѹ
	m_allWork[sub][GUID * 2 + 1] = m_modbus[GUID].m_lou2;
	
	if (GUID + 1 == ModBus_Num && m_allWork[sub][0] != Res_Empty)//��������
	{
		//��������
		PriInsertRes(sub);
		//ͳ������
		++m_resT.m_allNum;//������һ
		res = m_allWork[sub][CH_Num];
		m_allWork[sub][CH_Num] = Res_Empty;//��������
		if (res == Res_OK)//��Ʒ
		{
			++m_resT.m_goodNum;
		}
		else if (res == Res_NG)//��Ʒ
		{
			++m_resT.m_badNum;
		}

	}
	//�ؼ�����ʾ���
	//m_parentDlg->m_mainDlg.updataList(m_allWork[sub]);
	//��λ��һ
	PriAddWork(GUID);
	
	return TRUE;
}

//�ɼ��߳�
UINT CControl::collectThread(LPVOID lParam)
{
	m_this->collectFun();
	return TRUE;
}

//�ɼ�����
INT CControl::collectFun()
{
	m_collectT = NULL;
	return TRUE;
}

//���ͱ���
INT CControl::PriSendData()
{
#ifdef TEST
	//OutputDebugString(_T("��ʼ��������"));
#endif
	for (INT i = 0; i < ModBus_Num; ++i)
	{
		m_modbus[i].ComSendData();//���ͱ���
	}
	return TRUE;
}
//��ȡ�����ļ�
INT CControl::PriReadIni()
{
	return TRUE;
}
//��λ��һ
INT CControl::PriAddWork(UINT GUID)
{
	//��λ��һ
	m_modbus[GUID].m_workSub1 = (m_modbus[GUID].m_workSub1 + m_modbus[GUID].m_workAdd1) % Work_Max;
	m_modbus[GUID].m_workSub2 = (m_modbus[GUID].m_workSub2 + m_modbus[GUID].m_workAdd2) % Work_Max;
	return TRUE;
}

//�ر�һ���߳�
INT CControl::PriStopOneThread(INT* falg, CWinThread* pThread, INT waitTime)
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

//�����ݿ���ӽ������
INT CControl::PriInsertRes(INT sub)
{
	CTime time = CTime::GetCurrentTime();//
	m_sqlRes.AddNew();//���������
	m_sqlRes.m_TI = time.GetTime();//ʱ��
	m_sqlRes.m_PH = _T("1");//����
	m_sqlRes.m_CH1 = m_allWork[sub][0];//ͨ��1��ѹ1
	m_sqlRes.m_CH2 = m_allWork[sub][1];//ͨ��1��ѹ2
	m_sqlRes.m_CH3 = m_allWork[sub][2];//ͨ��2��ѹ1
	m_sqlRes.m_CH4 = m_allWork[sub][3];//ͨ��2��ѹ2
	m_sqlRes.m_CH5 = m_allWork[sub][4];//ͨ��3��ѹ1
	m_sqlRes.m_CH6 = m_allWork[sub][5];//ͨ��3��ѹ2
	m_sqlRes.m_NG = m_allWork[sub][6];//���

	m_sqlRes.Update();
	return TRUE;
}

//�����ݿ����ͳ�ƽ������
INT CControl::PriInsertResAll()
{
	CTime time = CTime::GetCurrentTime();//
	m_sqlResAll.AddNew();//���������
	m_sqlResAll.m_TIME = time.GetTime();//ʱ��
	m_sqlResAll.m_PI = m_pi; //����
	m_sqlResAll.m_USER = m_userName;//�û���
	m_sqlResAll.m_ALL = m_motor.m_allNum;//����
	m_sqlResAll.m_BAD = m_motor.m_allBad;//��Ʒ��

	m_sqlResAll.Update();
	return TRUE;
}

