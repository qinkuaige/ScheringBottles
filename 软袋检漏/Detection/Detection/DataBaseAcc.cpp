#include "stdafx.h"
#include "DataBaseAcc.h"


DataBaseAcc::DataBaseAcc()
{
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("初始化com失败！"));
	}
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset.CreateInstance(__uuidof(Recordset));//使用ADO创建数据库记录集
	m_pRecordsetR.CreateInstance(__uuidof(Recordset));//使用ADO创建数据库记录集
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

//初始化数据库
INT DataBaseAcc::ComInitAccess(CString path)
{
	//加载数据库
	ComLoadAccess(path);

	//创建表格
	CTime time = CTime::GetCurrentTime();
	CString ti;
	ti.Format(_T("%d年%02d月"), time.GetYear(), time.GetMonth());
	ComCreateTatble(ti);
	return TRUE;
}

//数据库路径
INT DataBaseAcc::ComLoadAccess(CString path)
{
	CFileFind find;
	if (find.FindFile(path) == FALSE)
	{
		AfxMessageBox(_T("数据库路径有误：") + path);
		return FALSE;
	}
	m_path = path;
	try{
		CString str = _T("Provider = Microsoft.ACE.OLEDB.12.0;Data Source = ") + path +
			_T(";Mode = ReadWrite | Share Deny None; Persist Security Info = False");
		//打开本地Access库Demo.mdb 
		m_pConnection->ConnectionString = str.AllocSysString();
		//m_pConnection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;\
		//	Data Source = Data.accdb; \
		//	Mode = ReadWrite | Share Deny None; Persist Security Info = False";
		
		m_pConnection->Open("","","",adModeUnknown);//注意代码的拼写错误！！！
	}      
	catch(_com_error e)     
	{         
		CString str;
		PirGetErr(e);
		AfxMessageBox(_T("数据库连接失败，确认数据库Demo.mdb是否在当前路径下!"));
		return FALSE; 
	} 
	//AfxMessageBox(_T("打开成功"));
	return TRUE;
}
//创建表
INT DataBaseAcc::ComCreateTatble()
{

	return TRUE;
}
//创建表
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
		m_tableName = tableName;//保存表的名称
	}
	catch (_com_error e)
	{
		PirGetErr(e);
		return FALSE;
	}
	//AfxMessageBox(_T("创建成功"));
	return TRUE;
}

//插入信息
INT DataBaseAcc::ComInsertData(INT ch1[])
{
	return ComInsertData(m_tableName, ch1);
}

//插入信息
INT DataBaseAcc::ComInsertData(CString& tableName, INT ch1[])
{
	static INT onceNum = 1;//每1000条数据提交一次
	static INT once = onceNum;
	
	//CString sTime;
	/*
	//比较日期来确定是否需要创建新的表
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
		tableName.Format(_T("%02d年%02d月"), 
			time.GetYear(), time.GetMonth());
		ComCreateTatble(tableName);
	}
	*/
	//插入数据
	CString str;
	str = L"SELECT * FROM " + tableName + _T(";");
	try
	{
		if (once >= onceNum)
		{
			m_pRecordset->Open(str.GetBuffer(0), m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
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

//数据
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
			m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdUnknown
			);
		//m_pRecordset->UpdateBatch(adAffectAll);
		if (!m_pRecordset->adoBOF)
		{
			m_pRecordset->MoveFirst();
			// 读入库中各字段并加入列表框中  
			_variant_t var;
			while (!m_pRecordset->adoEOF)
			{
				//时间
				var = m_pRecordset->GetCollect("TI");
				if (var.vt != VT_NULL)
					data.push_back(var.llVal);
				//电压数据
				CString name;
				for (INT i = 0; i < 4; ++i)
				{
					name.Format(_T("CH%d"), i + 1);
					var = m_pRecordset->GetCollect(name.GetBuffer(0));
					if (var.vt != VT_NULL)
						data.push_back(var.intVal);
				}
				//处理结果
				var = m_pRecordset->GetCollect("NG");
				if (var.vt != VT_NULL)
					data.push_back(var.intVal);
				m_pRecordset->MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("表内数据为空"));
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

//提交数据
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

//判断表是否存在
INT DataBaseAcc::ComIsTable(CString& tableName)
{
	CString str;
	str = _T("SELECT * FROM ") + tableName + _T(";");
	try
	{
		m_pRecordset->Open(str.GetBuffer(0), m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
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

//获取错误信息
INT DataBaseAcc::ComGetErr(CString& err)
{

	return TRUE;
}

//获取错误信息
INT DataBaseAcc::PirGetErr(_com_error& e)
{
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format(_T("错误信息:%s \n\n "),
		(LPCTSTR)bstrDescription);
	//在调试窗口中打印错误信息,在Release版中可用DBGView查看错误信息  
	OutputDebugString((LPCTSTR)ErrorStr);
#ifdef _DEBUG
	AfxMessageBox(ErrorStr, MB_OK | MB_ICONERROR);
#endif
	return TRUE;
}