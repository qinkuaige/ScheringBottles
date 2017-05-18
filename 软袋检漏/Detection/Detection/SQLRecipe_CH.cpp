// SQLRecipe_CH.h : CSQLRecipe_CH 类的实现



// CSQLRecipe_CH 实现

// 代码生成在 2017年5月11日, 13:48

#include "stdafx.h"
#include "SQLRecipe_CH.h"
IMPLEMENT_DYNAMIC(CSQLRecipe_CH, CRecordset)

CSQLRecipe_CH::CSQLRecipe_CH(INT GUID, CDatabase* pdb)
	: CRecordset(pdb)
{

	m_NAME = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
	m_tableName.Format(_T("[RuanDai].[dbo].[Recipe_CH%d]"), GUID);
	for (INT i = 0; i < Max_Data_Num; ++i)
	{
		m_data[i] = 0;
	}
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSQLRecipe_CH::GetDefaultConnect()
{
	return _T("DSN=RuanDai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZZ_PC;DATABASE=RuanDai");
}

CString CSQLRecipe_CH::GetDefaultSQL()
{
	return _T("[dbo].[Recipe_CH0]");
}

void CSQLRecipe_CH::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Int(pFX, _T("[U_SET1]"), m_data[U_SET1]);//高压设定值1
	RFX_Int(pFX, _T("[U_SET2]"), m_data[U_SET2]);//高压设定值2
	RFX_Int(pFX, _T("[UPLINE1]"), m_data[UpLine1]);//泄漏电压上限1
	RFX_Int(pFX, _T("[UPLINE2]"), m_data[UpLine2]);//泄漏电压上限2
	RFX_Int(pFX, _T("[DOWNLINE1]"), m_data[DownLine1]);//泄漏电压下限1
	RFX_Int(pFX, _T("[DOWNLINE2]"), m_data[DownLine2]);//泄漏电压下限1
	RFX_Int(pFX, _T("[LMD1]"), m_data[LMD1]);//1#放大倍数
	RFX_Int(pFX, _T("[LMD2]"), m_data[LMD2]);//2#放大倍数;

}
/////////////////////////////////////////////////////////////////////////////
// CSQLRecipe_CH 诊断

#ifdef _DEBUG
void CSQLRecipe_CH::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLRecipe_CH::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


//表名称 通道号
INT CSQLRecipe_CH::ComSetTableName(INT GUID)
{
	m_tableName.Format(_T("[RuanDai].[dbo].[Recipe_CH%d]"), GUID);
	return TRUE;
}

