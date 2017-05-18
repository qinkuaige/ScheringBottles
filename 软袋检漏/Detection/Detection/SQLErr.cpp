// SQLErr.h : CSQLErr 类的实现



// CSQLErr 实现

// 代码生成在 2016年11月16日, 16:58

#include "stdafx.h"
#include "SQLErr.h"
IMPLEMENT_DYNAMIC(CSQLErr, CRecordset)

CSQLErr::CSQLErr(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_TI = 0;
	m_LE = 0;
	m_INFO = L"";
	m_NAME = L"";
	m_nFields = 4;
	m_nDefaultType = dynaset;
	m_tableName = _T("[RuanDai].[dbo].[ERR]");
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSQLErr::GetDefaultConnect()
{
	return _T("DSN=RuanDai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=WINDOWS-TJ72C68;DATABASE=RuanDai");
}

CString CSQLErr::GetDefaultSQL()
{
	return m_tableName;
}

void CSQLErr::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_BigInt(pFX, _T("[TI]"), m_TI);
	RFX_Int(pFX, _T("[LE]"), m_LE);
	RFX_Text(pFX, _T("[INFO]"), m_INFO);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLErr 诊断

#ifdef _DEBUG
void CSQLErr::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLErr::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


