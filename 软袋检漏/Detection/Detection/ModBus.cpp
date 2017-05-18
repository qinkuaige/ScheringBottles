#include "stdafx.h"
#include "ModBus.h"
#include "Control.h"

UCHAR g_auchCRCHi[256] =
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
};

UCHAR g_auchCRCLo[256] =
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};

CModBus::CModBus()
	:m_dlg(NULL)
	, m_pCom(NULL)
	, m_dataFun(NULL)
	, m_GUID(FALSE)
	, m_upLine1(FALSE)//й©��ѹ����
	, m_downLine1(5)//й©��ѹ����
	, m_u1(FALSE)//��Դ��ѹ
	, m_upLine2(FALSE)//й©��ѹ����
	, m_downLine2(5)//й©��ѹ����
	, m_u2(FALSE)//��Դ��ѹ
	, m_isParam(FALSE)//�����Ƿ��ǲ�������
	, m_workSub1(FALSE)//��λ��1
	, m_workSub2(FALSE)//��λ��2
	, m_workAdd1(FALSE)//��λ����1
	, m_workAdd2(FALSE)//��λ����2
	, m_lou1(FALSE)//й©��ѹ1
	, m_lou2(FALSE)//й©��ѹ2
	, m_addr(_T("01"))//�豸��ַ
	, m_isSend(TRUE)//�ж�һ�������Ƿ�����ȫ
	, m_isConnect(FALSE)//��������״̬
	, m_rName(_T(""))//�����䷽����
	, m_collectF(FALSE)//�ɼ��̱߳�־λ
	, m_collectT(NULL)//�ɼ��߳�
	, m_startFlag(FALSE)
{
	CString sPath;
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos = sPath.ReverseFind('\\');
	m_path = sPath.Left(nPos);
	//
	InitializeCriticalSection(&m_cs);//��ʼ���ٽ���  
}


CModBus::~CModBus()
{
	ComDisConnect();
	if (m_dlg != NULL)
	{
		delete m_dlg;
		m_dlg = NULL;
	}
}

//��ʼ����
INT CModBus::ComInit(CDetectionDlg* parent, CControl* control, UINT GUID, CString addr)
{
	m_GUID = GUID;
	m_pDlg = parent;
	m_pControl = control;
	m_addr = addr;
	m_recipe.ComSetTableName(GUID);
	PriCreateDlg();
	return TRUE;
}

//��ʼ����
INT  CModBus::ComLoadParam(CString key)
{
	PriReadIni(key);//���ز���
	return TRUE;
}

//�򿪴���
INT CModBus::ComConnect()
{
	if (m_pCom == NULL)
	{
		return FALSE;
	}
	if (m_isConnect == TRUE)
	{
		AfxMessageBox(_T("��ѹ�������������ظ�����!"));
		return m_isConnect;
	}
	m_isConnect = TRUE;
	//PriReadIni();//���ز���
	m_pCom->put_CommPort(m_comParam.m_comID);//ѡ��com��
	m_pCom->put_InputMode(1);//���뷽ʽΪ�����Ʒ�ʽ
	m_pCom->put_InBufferSize(1024);//���뻺������СΪ1024byte
	m_pCom->put_OutBufferSize(512);//�����������СΪ512byte
	m_pCom->put_Settings(m_comParam.getSetting());//���ô��ڲ�����9600�����ʣ�����żУ�飬8������λ��1��ֹͣλ
	if (!m_pCom->get_PortOpen())
	{
		try
		{
			m_pCom->put_PortOpen(TRUE);//�򿪴���
		}
		catch (...)
		{
			m_isConnect = FALSE;
			CString str;
			str.Format(_T("COM%d ���ѱ�ʹ���޷���"), m_comParam.m_comID);
			AfxMessageBox(str);
			m_pControl->ComExit();
		}
	}
	m_pCom->put_RThreshold(1);//ÿ�����ڽ��ջ������ж�������1���ַ�ʱ������һ���������ݵ�oncomm�¼�
	m_pCom->put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0
	m_pCom->get_Input();//Ԥ������������ղ�������

	//�����ɼ��߳�
	m_collectT = AfxBeginThread(PriCollectThread, this);
	return TRUE;
}

//�رնϿ�����
INT CModBus::ComDisConnect()
{
	if (m_isConnect == TRUE)
	{
		try
		{
		    
		}
		catch (...)
		{

		}
		m_isConnect = FALSE;
	}
	return TRUE;
}
//�Ƿ���CRCУ��
INT CModBus::ComSendData(INT isCRC)
{
	ComSendData(m_addr + m_comParam.m_sendData, isCRC);
	return TRUE;
}

//�Ƿ���CRCУ��
INT CModBus::ComSendData(CString Data, INT isCRC)
{
	//�ȴ����Ľ�����ȫ��ŷ��ͱ���
	INT ti = 0;
	m_isSend = TRUE;
	//���ͱ���
	INT num = Data.GetLength();
	CByteArray arr;
	arr.RemoveAll();
	INT h = 0;
	INT l = 0;
	INT* p = &h;
	for (INT i = 0; i < num - 1;)
	{
		h = Data[i];
		l = Data[i + 1];
		p = &h;
		if (*p >= 'A' && *p <= 'F')
		{
			*p = (*p - 'A' + 10);
		}
		else if (*p >= '0' && *p <= '9')
		{
			*p = *p - '0';
		}
		else if (*p >= 'a' && *p <= 'f')
		{
			*p = (*p - 'a' + 10);
		}
		else//�����ַ�ֱ������
		{
			++i;
			continue;
		}
		p = &l;
		if (*p >= 'A' && *p <= 'F')
		{
			*p = (*p - 'A' + 10);
		}
		else if (*p >= '0' && *p <= '9')
		{
			*p = (*p - '0');
		}
		else if (*p >= 'a' && *p <= 'f')
		{
			*p = (*p - 'a' + 10);
		}
		else//�����ַ�ֱ������
		{
			++i;
			continue;
		}
		arr.Add(h * 16 + l);
		i += 2;
	}
	if (isCRC == TRUE)
	{
		PriCRC(arr);
	}
	EnterCriticalSection(&m_cs);//�����ٽ��� 
	m_pCom->put_Output(COleVariant(arr));
	PriGetData();
	LeaveCriticalSection(&m_cs);//�뿪�ٽ��� 
	return TRUE;
}

//���ûص�����
INT CModBus::ComSetCallBack(ComData fun)
{
	if (fun != NULL)
	{
		m_dataFun = fun;
	}
	return TRUE;
}

INT CModBus::PriCreateDlg()
{
	//new���ڴ���
	if (m_dlg != NULL)
	{
		delete m_dlg;
		m_dlg = NULL;
	}
	m_dlg = new CModBusDlg;
	//�������ڴ���
	if (m_dlg->Create(m_dlg->IDD, NULL) != TRUE)
	{
		AfxMessageBox(_T("����ͨѶ���ڴ���ʧ��!"));

		delete m_dlg;
		m_dlg = NULL;
		return FALSE;
	}
	//�õ����ڲ��ָ��
	m_pCom = &m_dlg->m_com;
	m_dlg->m_modBus = this;
	return TRUE;
}

//��ȡ�����ļ�
INT CModBus::PriReadIni(CString key)
{
	CString filePath = FILE_NAME;
	filePath = m_path + _T("\\ini\\") + filePath;
	//CString key = keyX;
	CFileFind find;
	if (find.FindFile(filePath) == FALSE)
	{
		AfxMessageBox(_T("�����ļ�������:") + filePath);
		return FALSE;
	}
	//���ں�
	m_comParam.m_comID = GetPrivateProfileInt(key, _T("���ں�"), 0, filePath);
	//������
	m_comParam.m_baud = GetPrivateProfileInt(key, _T("������"), 38400, filePath);
	//У��λ
	GetPrivateProfileString(key, _T("У��λ"), _T("n"), m_comParam.m_verify.GetBuffer(0),
		m_comParam.m_verify.GetLength(), filePath);
	//����λ
	m_comParam.m_startNum = GetPrivateProfileInt(key, _T("����λ"), 8, filePath);
	//ֹͣλ
	m_comParam.m_stopNum = GetPrivateProfileInt(key, _T("ֹͣλ"), 1, filePath);
	//�ɼ�����
	GetPrivateProfileString(key, _T("����"), _T(""),
		m_comParam.m_sendData.GetBuffer(0),0, filePath);

	//CH1
	m_workSub1 = GetPrivateProfileInt(key, _T("��λ��1"), 0, filePath);
	m_workAdd1 = GetPrivateProfileInt(key, _T("��λ����1"), 0, filePath);

	//CH2
	m_workSub2 = GetPrivateProfileInt(key, _T("��λ��2"), 0, filePath);
	m_workAdd2 = GetPrivateProfileInt(key, _T("��λ����2"), 0, filePath);

	return TRUE;
}

//CRCУ��
INT CModBus::PriCRC(CByteArray& arr, INT flag)
{
	INT len = arr.GetSize();
	INT res = TRUE;
	if (flag == CRC_Receive)
	{
		if (len < 2)
		{
			return FALSE;
		}
		len = len - 2;
	}
	UCHAR uchCRCHi = 0xff;
	UCHAR uchCRCLo = 0xff;
	UCHAR  uindex = 0;
	for (INT i = 0; i < len; ++i)
	{
		uindex = uchCRCHi^arr[i];
		uchCRCHi = uchCRCLo^g_auchCRCHi[uindex];
		uchCRCLo = g_auchCRCLo[uindex];
	}
	if (flag == CRC_Send)
	{
		arr.Add(uchCRCHi);
		arr.Add(uchCRCLo);
	}
	else if (flag == CRC_Receive)
	{
		if (uchCRCHi != arr[len] || uchCRCLo != arr[len + 1])
		{
			return FALSE;
		}
	}
	return res;
}



//��ȡ�豸����
INT CModBus::ComGetParam()
{
	m_isParam = TRUE;//��ȡ������ʶλ
	ComSendData(m_addr + Get_Param, TRUE);
	return TRUE;
}

//����ȡ�豸����
INT CModBus::ComSetParam(LONG addr, LONG value, INT isSQL)
{
	if (addr >= Max_Data_Num)//��ֹ���鳬��Χ
	{
		return FALSE;
	}
	CString str = m_addr + _T("0600");
	CString sTmp;
	sTmp.Format(_T("%02x%04x"), addr, value);
	str += sTmp;
	ComSendData(str, TRUE);
	m_data[addr] = value;
	if (isSQL == TRUE)
	{
		CSQLRecipe_CH recipe(m_GUID);
		try
		{
			if (recipe.Open())
			{
				recipe.Edit();
				recipe.m_data[addr] = value;
				recipe.Update();
				recipe.Move(0);
			}
		}
		catch (...)
		{
			return FALSE;
		}
	}
	return TRUE;
}

//ͳ����������
INT CModBus::ComClearData()
{
	m_res1.clear();
	m_res2.clear();
	return TRUE;
}

//�����䷽����
INT CModBus::ComSetRecipeT(CString name)
{
	m_rName = name;
	AfxBeginThread(PriSetRecipeThread, this);
	return TRUE;
}

//�����䷽�����߳�
INT CModBus::ComSetRecipe(CString name)
{
	//CSQLRecipeCH recipe(m_GUID);
	m_recipe;
	if (m_recipe.IsOpen())
	{
		m_recipe.Close();
	}
	CString str;
	//CString name = m_recipe;
	if (name != _T(""))
	{
		str = _T("SELECT * FROM ") + m_recipe.m_tableName +
			_T(" WHERE NAME = '") + name + _T("'");
	}
	else
	{
		str = _T("SELECT * FROM ") + m_recipe.m_tableName;
	}

	try{
		if (m_recipe.Open(NULL, str))
		{
			ComSetParam(U_SET1, m_recipe.m_data[U_SET1], FALSE);
			ComSetParam(U_SET2, m_recipe.m_data[U_SET2], FALSE);
			ComSetParam(UpLine1, m_recipe.m_data[UpLine1], FALSE);
			ComSetParam(UpLine2, m_recipe.m_data[UpLine2], FALSE);
			ComSetParam(DownLine1, m_recipe.m_data[DownLine1], FALSE);
			ComSetParam(DownLine2, m_recipe.m_data[DownLine2], FALSE);
			ComSetParam(LMD1, m_recipe.m_data[LMD1], FALSE);
			ComSetParam(LMD2, m_recipe.m_data[LMD2], FALSE);
		}
	}
	catch (...)
	{

	}
	ComGetParam();
	return TRUE;
}

//����䷽
INT CModBus::ComAddRecipe(CString name)
{
	CSQLRecipe_CH recipe(m_GUID);
	try
	{
		if (recipe.Open())
		{
			recipe.AddNew();
			recipe.m_NAME = name;
			for (INT i = 0; i < recipe.Max_Data_Num; ++i)
			{
				recipe.m_data[i] = 0;
			}
			recipe.Update();
			recipe.Close();
			return TRUE;
		}
	}
	catch(...)
	{

	}


	return FALSE;
}

//ɾ���䷽
INT CModBus::ComRemoveRecipe(CString name)
{
	CSQLRecipe_CH recip(m_GUID);
	try{
		CString sql = _T("SELECT * FROM ") + recip.m_tableName
			+ _T(" WHERE NAME = '") + name + _T("';");
		if (recip.Open(NULL, sql))
		{
			recip.MoveFirst();
			if (!recip.IsEOF())
			{
				recip.Delete();
				recip.Update();
				recip.Close();
				return TRUE;
			}
		}
	}
	catch (...)
	{

	}
	return FALSE;
}

//�ɼ������߳�
UINT CModBus::PriCollectThread(LPVOID lParam)
{
	CModBus* parent = (CModBus*)lParam;
	parent->PriCollectFun();
	return TRUE;
}

INT CModBus::PriCollectFun()//�ɼ�����
{
	m_collectF = TRUE;
	while (m_collectF)
	{
		if (m_startFlag  == TRUE) //&& m_pControl->m_motor.m_isRun == TRUE)
		{
			ComSendData(TRUE);
			m_startFlag = FALSE;
		}
		Sleep(5);
	}
	return TRUE;
}

//��ȡ����
INT CModBus::PriGetData()
{
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	CString m_strRXData;
	LONG time = 200;
	while(1)
	{
		//if(m_pCom->get_CommEvent() == 2)
		{
			////////��������Ը����Լ���ͨ��Э����봦�����  
			variant_inp = m_pCom->get_Input(); //��������  
			safearray_inp = variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���  
			CByteArray arr;//������յ�������
			arr.RemoveAll();
			safearray_inp.GetByteArray(arr);
			INT size = m_readArr.GetSize();
			m_readArr.InsertAt(size, &arr);
			//m_readArr ����Ϊ03���ǲ���
			if (PriCRC(m_readArr, CRC_Receive))//�ж�һ�������Ƿ������ȫ
			{
				m_isSend = FALSE;//������ȫ
				PriSaveGetData();
				m_readArr.RemoveAll();
				break;
			}
		}
		if (time > 0)
		{
			time--;
		}
		else
		{
			m_readArr.RemoveAll();
			OutputDebugString(_T("���Ľ��ܳ�ʱ��"));
			break;
		}
		Sleep(2);
	}
	
	return TRUE;
}


//�����ȡ��������
INT CModBus::PriSaveGetData()
{
	if (m_readArr[1] == 3)
	{
		INT size = m_readArr.GetSize();//��ȡ���ݰ���С
		for (INT i = 0; i < (size - 5)/ 2; ++i)//��������
		{
			m_data[i] = m_readArr[3 + i * 2] * 256 + m_readArr[3 + i * 2 + 1];
		}
		if (m_dataFun != NULL)
		{
			m_u1 = m_data[U1];
			m_u2 = m_data[U2];
			m_lou1 = m_data[Lou1];
			m_lou2 = m_data[Lou2];
			//1#
			if (m_lou1 < m_data[DownLine1])//��λ
			{
				m_res1.m_res = Res_Empty;
				++m_res1.m_allEmptyNum;
			}
			else if (m_lou1 >= m_data[UpLine1])//©Һ
			{
				m_res1.m_res = Res_NG;
				++m_res1.m_allNum;
				++m_res1.m_badNum;
			}
			else //��Ʒ
			{
				m_res1.m_res = Res_OK;
				++m_res1.m_allNum;
				++m_res1.m_goodNum;
			}

			//2#
			if (m_lou2 < m_data[DownLine2])//��λ
			{
				m_res2.m_res = Res_Empty;
				++m_res2.m_allEmptyNum;
			}
			else if (m_lou2 >= m_data[UpLine2])//©Һ
			{
				m_res2.m_res = Res_NG;
				++m_res2.m_allNum;
				++m_res2.m_badNum;
			}
			else                       //��Ʒ
			{
				m_res2.m_res = Res_OK;
				++m_res2.m_allNum;
				++m_res2.m_goodNum;
			}
			OutputDebugString(_T("111111111xxxxxxxxxxxxxxxxxxx"));
			m_dataFun(m_GUID, m_readArr);
		}//if CRC
	}
	return TRUE;
}

//�����䷽����
UINT CModBus::PriSetRecipeThread(LPVOID lParam)
{
	CModBus* parent = (CModBus*)lParam;
	parent->ComSetRecipe(parent->m_rName);
	
	return TRUE;
}
