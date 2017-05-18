#include "stdafx.h"
#include "DataBaseAcc.h"


DataBaseAcc::DataBaseAcc()
{
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("��ʼ��comʧ�ܣ�"));
	}
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset.CreateInstance(__uuidof(Recordset));//ʹ��ADO�������ݿ��¼��
	m_pRecordsetR.CreateInstance(__uuidof(Recordset));//ʹ��ADO�������ݿ��¼��
}


DataBaseAcc::~DataBaseAcc()
{
	if (m_pRecordset != NULL && m_pRecordset->State)
	{
		//m_pRecordset->Close();
		//delete m_pRecordset;
		//m_pRecordset = NULL;
	}
	if (m_pRecordsetR != NULL && m_pRecordsetR->State)
	{
		//m_pRecordsetR->Close();
		//delete m_pRecordsetR;
		//m_pRecordsetR = NULL;
	}
	if (m_pConnection != NULL && m_pConnection->State)
	{
		//m_pConnection->Close();
		//m_pConnection = NULL;
	}
	
}

//��ʼ�����ݿ�
INT DataBaseAcc::ComInitAccess(CString path)
{
	//�������ݿ�
	ComLoadAccess(path);

	//�������
	CTime time = CTime::GetCurrentTime();
	CString ti;
	ti.Format(_T("%d��%02d��"), time.GetYear(), time.GetMonth());
	ComCreateTatble(ti);
	return TRUE;
}

//���ݿ�·��
INT DataBaseAcc::ComLoadAccess(CString path)
{
	CFileFind find;
	if (find.FindFile(path) == FALSE)
	{
		AfxMessageBox(_T("���ݿ�·������") + path);
		return FALSE;
	}
	m_path = path;
	try{
		CString str = _T("Provider = Microsoft.ACE.OLEDB.12.0;Data Source = ") + path +
			_T(";Mode = ReadWrite | Share Deny None; Persist Security Info = False");
		//�򿪱���Access��Demo.mdb 
		m_pConnection->ConnectionString = str.AllocSysString();
		//m_pConnection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;\
		//	Data Source = Data.accdb; \
		//	Mode = ReadWrite | Share Deny None; Persist Security Info = False";
		
		m_pConnection->Open("","","",adModeUnknown);//ע������ƴд���󣡣���
	}      
	catch(_com_error e)     
	{         
		CString str;
		PirGetErr(e);
		AfxMessageBox(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ�Demo.mdb�Ƿ��ڵ�ǰ·����!"));
		return FALSE; 
	} 
	//AfxMessageBox(_T("�򿪳ɹ�"));
	return TRUE;
}
//������
INT DataBaseAcc::ComCreateTatble()
{

	return TRUE;
}
//������
INT DataBaseAcc::ComCreateTatble(CString tableName)
{
	CString str = _T("CREATE TABLE ") + tableName
		+ _T("(TI INT,CH1 INT,CH2 INT, CH3 INT, CH4 INT, NG INT);");
	try{
		if (ComIsTable(tableName) == FALSE)
		{
			_variant_t RecordsAffected;
			m_pConnection->Execute(str.GetBuffer(0), 0, 0);
		}
		m_tableName = tableName;//����������
	}
	catch (_com_error e)
	{
		PirGetErr(e);
		return FALSE;
	}
	//AfxMessageBox(_T("�����ɹ�"));
	return TRUE;
}

//������Ϣ
INT DataBaseAcc::ComInsertData(INT ch1[])
{
	return ComInsertData(m_tableName, ch1);
}

//������Ϣ
INT DataBaseAcc::ComInsertData(CString& tableName, INT ch1[])
{
	static INT onceNum = 1;//ÿ1000�������ύһ��
	static INT once = onceNum;
	
	//CString sTime;
	/*
	//�Ƚ�������ȷ���Ƿ���Ҫ�����µı�
	static INT sMonth = -1;
	INT Month = time.GetMonth();
	if (sMonth == -1)
	{
		sMonth = Month;
	}
	if (sMonth != Month)
	{
		if (once < onceNum)
		{
			m_pRecordset->Update();
			m_pRecordset->Close();
			once = onceNum;
		}
		CString tableName;
		tableName.Format(_T("%02d��%02d��"), 
			time.GetYear(), time.GetMonth());
		ComCreateTatble(tableName);
	}
	*/
	//��������
	CString str;
	str = L"SELECT * FROM " + tableName + _T(";");
	try
	{
		if (once >= onceNum)
		{
			m_pRecordset->Open(str.GetBuffer(0), m_pConnection.GetInterfacePtr(),  // ��ȡ��ӿ��IDispatchָ��
				adOpenDynamic,
				adLockOptimistic,
				adCmdUnknown
				);
			once = FALSE;
		}
		++once;///////////////
		//for (INT i = 0; i < 1000; ++i)
		{
			//sTime.Format(_T("%02d%02d"), , );
			{
				CTime time = CTime::GetCurrentTime();//
				LONGLONG ti = time.GetTime();
				m_pRecordset->AddNew();
				m_pRecordset->PutCollect("TI", ti);
				INT i = 0;
				m_pRecordset->PutCollect("CH1", ch1[i]);
				++i;
				m_pRecordset->PutCollect("CH2", ch1[i]);
				++i;
				m_pRecordset->PutCollect("CH3", ch1[i]);
				++i;
				m_pRecordset->PutCollect("CH4", ch1[i]);
				//++i;
				//m_pRecordset->PutCollect("CH5", ch1[i]);
				++i;
				m_pRecordset->PutCollect("NG", ch1[i]);
				m_pRecordset->Update();
			}
		}
		
		if (once >= onceNum)
		{
			m_pRecordset->Close();
		}
	}
	catch (_com_error e)
	{
		PirGetErr(e);
	}
	return TRUE;
}

//����
INT DataBaseAcc::ComGetData(CTime& startT, CTime& endT, vector<LONGLONG>& data, INT num)
{
	CString str;
	CString time;
	LONGLONG start = startT.GetTime();
	LONGLONG end = endT.GetTime();
	INT res = TRUE;
	if (num <= 0 || num > 2000)
	{
		num = 2000;
	}
	try
	{
		str.Format(_T("SELECT top %d * FROM %s WHERE TI >= %I64d AND TI <= %I64d;"), 
			num, m_tableName, start, end);
		m_pRecordset->Open(
			str.GetBuffer(0),
			m_pConnection.GetInterfacePtr(),  // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdUnknown
			);
		//m_pRecordset->UpdateBatch(adAffectAll);
		if (!m_pRecordset->adoBOF)
		{
			m_pRecordset->MoveFirst();
			// ������и��ֶβ������б����  
			_variant_t var;
			while (!m_pRecordset->adoEOF)
			{
				//ʱ��
				var = m_pRecordset->GetCollect("TI");
				if (var.vt != VT_NULL)
					data.push_back(var.llVal);
				//��ѹ����
				CString name;
				for (INT i = 0; i < 4; ++i)
				{
					name.Format(_T("CH%d"), i + 1);
					var = m_pRecordset->GetCollect(name.GetBuffer(0));
					if (var.vt != VT_NULL)
						data.push_back(var.intVal);
				}
				//������
				var = m_pRecordset->GetCollect("NG");
				if (var.vt != VT_NULL)
					data.push_back(var.intVal);
				m_pRecordset->MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("��������Ϊ��"));
		 }
	}
	catch (_com_error e)
	{
		PirGetErr(e);
		res = FALSE;
	}
	if (m_pRecordset->State)
	{
		m_pRecordset->Close();
	}
	return res;
}

//�ύ����
INT DataBaseAcc::ComUpData()
{
	try
	{
		if (m_pRecordset->State)
		{
			m_pRecordset->Update();
			m_pRecordset->Close();
		}
	}
	catch (_com_error e)
	{
		PirGetErr(e);
	}
	if (m_pRecordset->State)
	{
		m_pRecordset->Close();
	}
	return TRUE;
}

//�жϱ��Ƿ����
INT DataBaseAcc::ComIsTable(CString& tableName)
{
	CString str;
	str = _T("SELECT * FROM ") + tableName + _T(";");
	try
	{
		m_pRecordset->Open(str.GetBuffer(0), m_pConnection.GetInterfacePtr(),  // ��ȡ��ӿ��IDispatchָ��
			adOpenStatic,
			adLockOptimistic,
			adCmdUnknown
			);
	}
	catch (_com_error e)
	{
		//PirGetErr(e);
		//m_pRecordset->Close();
		return FALSE;
	}
	m_pRecordset->Close();
	return TRUE;
}

//��ȡ������Ϣ
INT DataBaseAcc::ComGetErr(CString& err)
{

	return TRUE;
}

//��ȡ������Ϣ
INT DataBaseAcc::PirGetErr(_com_error& e)
{
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format(_T("������Ϣ:%s \n\n "),
		(LPCTSTR)bstrDescription);
	//�ڵ��Դ����д�ӡ������Ϣ,��Release���п���DBGView�鿴������Ϣ  
	OutputDebugString((LPCTSTR)ErrorStr);
#ifdef _DEBUG
	AfxMessageBox(ErrorStr, MB_OK | MB_ICONERROR);
#endif
	return TRUE;
}