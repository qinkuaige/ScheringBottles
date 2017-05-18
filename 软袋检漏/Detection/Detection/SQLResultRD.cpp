// SQLResultRD.h : CSQLResultRD 类的实现



// CSQLResultRD 实现

// 代码生成在 2017年4月11日, 16:54

#include "stdafx.h"
#include "SQLResultRD.h"
IMPLEMENT_DYNAMIC(CSQLResultRD, CRecordset)

CSQLResultRD::CSQLResultRD(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_TI = 0;
	m_PH = L"";
	m_CH1 = 0;
	m_CH2 = 0;
	m_CH3 = 0;
	m_CH4 = 0;
	m_CH5 = 0;
	m_CH6 = 0;
	m_NG = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;

	m_tableName = _T("[RuanDai].[dbo].[Result_Data]");
}

// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSQLResultRD::GetDefaultConnect()
{
	return _T("DSN=RuanDai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=WINDOWS-TJ72C68;DATABASE=RuanDai");
}

CString CSQLResultRD::GetDefaultSQL()
{
	return _T("[dbo].[Result_Data]");
}

void CSQLResultRD::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_BigInt(pFX, _T("[TI]"), m_TI);
	RFX_Text(pFX, _T("[PH]"), m_PH);
	RFX_Long(pFX, _T("[CH1]"), m_CH1);
	RFX_Long(pFX, _T("[CH2]"), m_CH2);
	RFX_Long(pFX, _T("[CH3]"), m_CH3);
	RFX_Long(pFX, _T("[CH4]"), m_CH4);
	RFX_Long(pFX, _T("[CH5]"), m_CH5);
	RFX_Long(pFX, _T("[CH6]"), m_CH6);
	RFX_Long(pFX, _T("[NG]"), m_NG);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLResultRD 诊断

#ifdef _DEBUG
void CSQLResultRD::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLResultRD::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


