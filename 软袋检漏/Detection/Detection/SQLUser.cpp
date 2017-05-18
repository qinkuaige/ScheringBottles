// SQLUser.h : CSQLUser ���ʵ��



// CSQLUser ʵ��

// ���������� 2016��11��15��, 16:35

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
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSQLUser::GetDefaultConnect()
{

	return _T("DSN=LianPai;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZZ-PC;DATABASE=LianPai");
}

CString CSQLUser::GetDefaultSQL()
{
	CString str;
	//�����񲻴������Զ��������
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[PW]"), m_PW);
	RFX_Int(pFX, _T("[ROOT]"), m_ROOT);
	RFX_Int(pFX, _T("[OTHRE]"), m_OTHRE);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLUser ���

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


