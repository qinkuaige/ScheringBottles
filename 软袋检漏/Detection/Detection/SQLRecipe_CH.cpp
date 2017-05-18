// SQLRecipe_CH.h : CSQLRecipe_CH ���ʵ��



// CSQLRecipe_CH ʵ��

// ���������� 2017��5��11��, 13:48

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
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Int(pFX, _T("[U_SET1]"), m_data[U_SET1]);//��ѹ�趨ֵ1
	RFX_Int(pFX, _T("[U_SET2]"), m_data[U_SET2]);//��ѹ�趨ֵ2
	RFX_Int(pFX, _T("[UPLINE1]"), m_data[UpLine1]);//й©��ѹ����1
	RFX_Int(pFX, _T("[UPLINE2]"), m_data[UpLine2]);//й©��ѹ����2
	RFX_Int(pFX, _T("[DOWNLINE1]"), m_data[DownLine1]);//й©��ѹ����1
	RFX_Int(pFX, _T("[DOWNLINE2]"), m_data[DownLine2]);//й©��ѹ����1
	RFX_Int(pFX, _T("[LMD1]"), m_data[LMD1]);//1#�Ŵ���
	RFX_Int(pFX, _T("[LMD2]"), m_data[LMD2]);//2#�Ŵ���;

}
/////////////////////////////////////////////////////////////////////////////
// CSQLRecipe_CH ���

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


//������ ͨ����
INT CSQLRecipe_CH::ComSetTableName(INT GUID)
{
	m_tableName.Format(_T("[RuanDai].[dbo].[Recipe_CH%d]"), GUID);
	return TRUE;
}

