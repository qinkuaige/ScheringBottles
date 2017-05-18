// SQLUser.h : CSQLUser 类的实现



// CSQLUser 实现

// 代码生成在 2016年11月15日, 16:35

#include "stdafx.h"
#include "SQLUser.h"
IMPLEMENT_DYNAMIC(CSQLUser, CRecordset)

CSQLUser::CSQLUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_NAME = L"";
	m_PW = L"";
	m_ROOT = 0;
	m_OTHRE = 0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
	m_tableName = _T("[LianPai].[dbo].[User]");
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSQLUser::GetDefaultConnect()
{

	return _T("DSN=LianPai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZZ-PC;DATABASE=LianPai");
}

CString CSQLUser::GetDefaultSQL()
{
	CString str;
	//如果表格不存在则自动创建表格
	str = _T("if object_id('") + m_tableName +
		_T("','U') is null CREATE TABLE ") +
		m_tableName +
		_T("(NAME[nchar](10),PW[nchar](10),ROOT[smallint],OTHRE[smallint]);");
	m_pDatabase->ExecuteSQL(str);
	return m_tableName;
}

void CSQLUser::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[PW]"), m_PW);
	RFX_Int(pFX, _T("[ROOT]"), m_ROOT);
	RFX_Int(pFX, _T("[OTHRE]"), m_OTHRE);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLUser 诊断

#ifdef _DEBUG
void CSQLUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


