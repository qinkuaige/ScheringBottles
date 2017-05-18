#pragma once
#include "DataBaseAcc.h"
#include "SQLResultRD.h"//��ʷ����
#include "SQLUser.h"//��¼��Ϣ
#include "SQLErr.h"//������Ϣ��¼
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
		ModBus_Num = 3,//ͨѶ����
		Send_Time = 20,//ÿ20ms����һ��
		//Insert_Num = 5,//Ҫ��������ݵĸ���
		Work_Max = 100,//���λ��
		CH_Num = 6,//���ͨ����
		Empty_Work = -100,//��λ
	};
public:
	INT ComInit(CDetectionDlg* parentDlg);//��ʼ��
	INT ComConnect();//�����豸
	INT ComDisConnect();//�Ͽ��豸����
	INT ComStart();//��ʼ���
	INT ComStop();//ֹͣ���
	INT ComClearData();//�������
	//INT ComGetResData(LONGLONG tiMax, LONGLONG timin, vector<vector<CString>>& str);//��ȡ��ʷ�������
	//INT ComGetResData(CString PH, vector<vector<CString>>& str);//��ȡ��ʷ�������
	INT ComInsertErr(vector<CString>& err);//��������Ϣ���뵽���ݿ���
	//INT ComIniRecipe(CString name = _T(""));//��ȡ�䷽
	INT ComExit();//�رճ���
private:
	static INT dataCallBack(UINT GUID, CByteArray& arry);//��ȡ���ݵĻص�����
	INT dataFun(UINT GUID, CByteArray& arry);//��ȡ���ݵĻص�����
	static UINT collectThread(LPVOID lParam);//�ɼ��߳�
	INT collectFun();//�ɼ�����
	static UINT PriSetRecipeThread(LPVOID lParam);//�����䷽�����߳�
	INT PriSetRecipeFun();//�����䷽���ĺ���

	INT PriReadIni();//��ȡ�����ļ�
	INT PriAddWork(UINT GUID);//��λ��һ
	INT PriStopOneThread(INT* falg, CWinThread* pThread, INT waitTime);//�ر�һ���߳�
	INT PriInsertRes(INT sub = 0);//�����ݿ���ӽ������
	INT PriInsertResAll();//�����ݿ����ͳ�ƽ������
public:
	INT PriSendData();//���ͱ���
public:
	//ModBusStruct m_modbus[ModBus_Num];
	CModBus m_modbus[ModBus_Num];//modBusͨѶ��
	CMotorSL m_motor;//�ŷ�����
	INT m_startFlag;//�ɼ���־λ
	CWinThread* m_collectT;//���������߳�
	INT		m_collectFlg;//�������ݱ�־λ
	INT m_isConnect;//��������״̬
	CString m_path;//���浱ǰ·��
	resultStruct m_resT;//ͳ�ƽ��
	INT		m_workSubT;//tͳ���ù�λ
	INT		m_isStart;//��ʼ����־λ
	INT     m_isSend;//���ͱ��ı�־λ
	CString m_userName;//����Ա����
	CString m_pi;
//��λ
public:
	INT m_allWork[Work_Max][CH_Num + 1];
public:
	DataBaseAcc m_access;//���ݴ洢��
	CSQLResultRD m_sqlRes;//�����
	CSQLResultAll m_sqlResAll;//����ͳ�ƽ��
	CDetectionDlg* m_parentDlg;//��������
};

