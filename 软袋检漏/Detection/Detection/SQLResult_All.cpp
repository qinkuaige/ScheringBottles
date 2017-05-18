// SQLResult_All.h : CSQLResultAll 类的实现



// CSQLResultAll 实现

// 代码生成在 2017年5月12日, 13:31

#include "stdafx.h"
#include "SQLResult_All.h"
IMPLEMENT_DYNAMIC(CSQLResultAll, CRecordset)

CSQLResultAll::CSQLResultAll(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_TIME = 0;
	m_PI = "";
	m_USER = "";
	m_ALL = 0;
	m_BAD = 0;
	m_OTHER = "";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}

// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSQLResultAll::GetDefaultConnect()
{
	return _T("DSN=RuanDai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZZ_PC;DATABASE=RuanDai");
}

CString CSQLResultAll::GetDefaultSQL()
{
	return _T("[dbo].[Result_All]");
}

void CSQLResultAll::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_BigInt(pFX, _T("[TIME]"), m_TIME);
	RFX_Text(pFX, _T("[PI]"), m_PI);
	RFX_Text(pFX, _T("[USER]"), m_USER);
	RFX_Long(pFX, _T("[ALL]"), m_ALL);
	RFX_Long(pFX, _T("[BAD]"), m_BAD);
	RFX_Text(pFX, _T("[OTHER]"), m_OTHER);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLResultAll 诊断

#ifdef _DEBUG
void CSQLResultAll::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLResultAll::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


