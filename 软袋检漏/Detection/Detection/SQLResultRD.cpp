// SQLResultRD.h : CSQLResultRD ���ʵ��



// CSQLResultRD ʵ��

// ���������� 2017��4��11��, 16:54

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

// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// CSQLResultRD ���

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


