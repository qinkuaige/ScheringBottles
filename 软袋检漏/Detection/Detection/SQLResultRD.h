// SQLResultRD.h : CSQLResultRD ������

#pragma once

// ���������� 2017��4��11��, 16:54
#include <vector>
using namespace std;
class CSQLResultRD : public CRecordset
{
public:
	CSQLResultRD(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSQLResultRD)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	LONGLONG	m_TI;
	CStringW	m_PH;
	long	m_CH1;
	long	m_CH2;
	long	m_CH3;
	long	m_CH4;
	long	m_CH5;
	long	m_CH6;
	long	m_NG;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��
public:
	CString m_tableName;//������
// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


