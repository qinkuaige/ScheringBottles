// SQLErr.h : CSQLErr ���ʵ��



// CSQLErr ʵ��

// ���������� 2016��11��16��, 16:58

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_BigInt(pFX, _T("[TI]"), m_TI);
	RFX_Int(pFX, _T("[LE]"), m_LE);
	RFX_Text(pFX, _T("[INFO]"), m_INFO);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);

}
/////////////////////////////////////////////////////////////////////////////
// CSQLErr ���

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


