// SQLResult_All.h : CSQLResultAll ���ʵ��



// CSQLResultAll ʵ��

// ���������� 2017��5��12��, 13:31

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

// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_BigInt(pFX, _T("[TIME]"), m_TIME);
	RFX_Text(pFX, _T("[PI]"), m_PI);
	RFX_Text(pFX, _T("[USER]"), m_USER);
	RFX_Long(pFX, _T("[ALL]"), m_ALL);
	RFX_Long(pFX, _T("[BAD]"), m_BAD);
	RFX_Text(pFX, _T("[OTHER]"), m_OTHER);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLResultAll ���

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


