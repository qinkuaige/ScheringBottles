#pragma once
#include "ModBusDlg.h"
#include <queue>
using namespace std;
#define FILE_NAME _T("com.ini")
#define Get_Param _T("0300000011")
enum
{
	Param_Num = 17,//��������
	Data_Num = 6,//������ȡ���ݵĸ���
};

struct ComStruct
{
	INT m_comID;
	INT m_baud;//������
	CString m_verify;//У��λ
	INT m_startNum;//����λ
	INT m_stopNum;//ֹͣλ
	CString m_sendData;//Ĭ�ϱ���
	//��ȡ�����ַ���
	CString getSetting()
	{
		CString str;
		str.Format(_T("%d,%s,%d,%d"), m_baud, m_verify, m_startNum, m_stopNum);
		return str;
	}
	ComStruct()
	{
		m_comID = 1;
		m_baud = 38400;//������
		m_verify = _T("n");//У��λ
		m_startNum = 8;//����λ
		m_stopNum = 1;//ֹͣλ
		m_sendData = _T("0300000006C5C8");//Ĭ�ϱ���
	}
};

struct resultStruct
{
	INT m_res;//��ǰ���
	INT m_allNum;//����
	INT m_goodNum;//��Ʒ��
	INT m_badNum;//��Ʒ����
	INT m_allEmptyNum;//��Ʒ����
	resultStruct()
	{
		m_res = FALSE;//��ǰ���
		m_allNum = FALSE;//����
		m_goodNum = FALSE;//��Ʒ��
		m_badNum = FALSE;//��Ʒ����
		m_allEmptyNum = FALSE;//��Ʒ����
	}
	resultStruct& operator=(const resultStruct& other)
	{
		m_res = other.m_res;//��ǰ���
		m_allNum = other.m_allNum;//����
		m_goodNum = other.m_goodNum;//��Ʒ��
		m_badNum = other.m_badNum;//��Ʒ����
		m_allEmptyNum = other.m_allEmptyNum;//��Ʒ����
		return *this;
	}
	INT clear()//��������
	{
		m_res = FALSE;//��ǰ���
		m_allNum = FALSE;//����
		m_goodNum = FALSE;//��Ʒ��
		m_badNum = FALSE;//��Ʒ����
		m_allEmptyNum = FALSE;//��Ʒ����
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
	Max_Data_Num = 30,//����������
	U1 = 0,//��Դ��ѹ1
	U2 = 1,//��Դ��ѹ2
	Lou1 = 4,//��һƿй©��ѹ1
	Lou2 = 5,//��һƿй©��ѹ2
	U_SET1 = 6,//��ѹ�趨ֵ
	U_SET2 = 12,//��ѹ�趨ֵ
	UpLine1 = 7,//й©��ѹ����1
	UpLine2 = 13,//й©��ѹ����2
	DownLine1 = 9,//й©��ѹ����1
	DownLine2 = 15,//й©��ѹ����1
	LMD1 = 10,	//1#�Ŵ���
	LMD2 = 16,	//2#�Ŵ���
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
		UINT GUID = FALSE, CString addr = _T("00"));//��ʼ����
	virtual INT ComLoadParam(CString key);//��ʼ����
	virtual INT ComConnect();//�򿪴���
	INT ComDisConnect();//�رնϿ�����
	virtual INT ComSendData(INT isCRC = FALSE);//�Ƿ���CRCУ��
	virtual INT ComSendData(CString Data, INT isCRC = FALSE);//�Ƿ���CRCУ��
	virtual INT ComSetCallBack(ComData fun);//���ûص�����
	virtual INT ComGetParam();//��ȡ�豸����
	INT ComSetParam(LONG addr, LONG value, INT isSQL = TRUE);//����ȡ�豸����
	INT ComClearData();//ͳ����������
	INT ComSetRecipeT(CString name);//�����䷽�����߳�
	INT ComSetRecipe(CString name);//�����䷽����
	INT ComAddRecipe(CString name);//����䷽
	INT ComRemoveRecipe(CString name);//ɾ���䷽
private:
	INT PriCreateDlg();
	INT PriReadIni(CString key);//��ȡ�����ļ�
	INT PriCRC(CByteArray& arr, INT flag = CRC_Send);//CRCУ��
	static UINT PriSetRecipeThread(LPVOID lParam);//�����䷽����
	
public:
	static UINT PriCollectThread(LPVOID lParam);//�ɼ������߳�
	INT PriCollectFun();//�ɼ�����
	INT PriGetData();//��ȡ����
	INT PriSaveGetData();//�����ȡ��������
private:
	UINT m_GUID;//���
	CDetectionDlg* m_pDlg;
	CControl* m_pControl;
	CMscomm1* m_pCom;//���ڲ����ַ
	CWnd* m_parentDlg;//���游�ര��ָ��
	CModBusDlg* m_dlg;//���ڲ�����ڵĴ���ָ��
	ComStruct m_comParam;//���ڲ����ṹ��
	CString m_path;//���浱ǰ����·��
	CByteArray m_readArr;//������յ�������
	INT m_isParam;//�����Ƿ��ǲ�������
	CString m_addr;//�豸��ַ
	INT m_isSend;//�ж�һ�������Ƿ�����ȫ
	CString m_rName;//�䷽����
	INT m_isConnect;//��������״̬
	INT m_collectF;//�ɼ��̱߳�־λ
	CWinThread* m_collectT;//�ɼ��߳�
public:
	INT m_startFlag;//��ʼ�ɼ�

//��ѹ�����
public:
	INT m_data[Max_Data_Num];//��ȡ���Ĳ���ֵ
	INT m_upLine1;//й©��ѹ����
	INT m_downLine1;//й©��ѹ����
	INT m_u1;//��Դ��ѹ
	INT m_upLine2;//й©��ѹ����
	INT m_downLine2;//й©��ѹ����
	INT m_u2;//��Դ��ѹ
	INT m_workSub1;//��λ��1
	INT m_workSub2;//��λ��2
	INT m_workSub3;//��λ��2
	INT m_workAdd1;//��λ����1
	INT m_workAdd2;//��λ����2
	INT m_workAdd3;//��λ����2
	INT m_lou1;//й©��ѹ1
	INT m_lou2;//й©��ѹ2
	resultStruct m_res1;//���1
	resultStruct m_res2;//���2
	CSQLRecipe_CH m_recipe;//����
public:
	ComData m_dataFun;
	CRITICAL_SECTION m_cs;//�ٽ���
};

