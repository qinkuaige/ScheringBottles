// SQLRecipeCH.h : CSQLRecipeCH ���ʵ��



// CSQLRecipeCH ʵ��

// ���������� 2016��11��17��, 15:13

#include "stdafx.h"
#include "SQLRecipeCH.h"
IMPLEMENT_DYNAMIC(CSQLRecipeCH, CRecordset)

CSQLRecipeCH::CSQLRecipeCH(INT GUID, CDatabase* pdb)
	: CRecordset(pdb)
	
{
	m_NAME = L"";
	/*
	m_U_SET1 = 0;
	m_U_SET2 = 0;
	m_UPLINE1 = 0;
	m_UPLINE2 = 0;
	m_DOWNLINE1 = 0;
	m_DOWNLINE2 = 0;
	m_LMD1 = 0;
	m_LMD2 = 0;
	*/
	m_nFields = 9;
	m_nDefaultType = dynaset;
	m_tableName.Format(_T("[LianPai].[dbo].[Recipe_H%d]"), GUID);
	for (INT i = 0; i < Max_Data_Num; ++i)
	{
		m_data[i] = 0;
	}
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSQLRecipeCH::GetDefaultConnect()
{
	return _T("DSN=LianPai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZZ-PC;DATABASE=LianPai");
}

CString CSQLRecipeCH::GetDefaultSQL()
{
	return m_tableName;
}

void CSQLRecipeCH::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Int(pFX, _T("[LMD2]"), m_data[LMD2]);//2#�Ŵ���
}
/////////////////////////////////////////////////////////////////////////////
// CSQLRecipeCH ���

#ifdef _DEBUG
void CSQLRecipeCH::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSQLRecipeCH::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//������ ͨ����
INT CSQLRecipeCH::ComSetTableName(INT GUID)
{
	m_tableName.Format(_T("[LianPai].[dbo].[Recipe_H%d]"), GUID);
	return TRUE;
}
