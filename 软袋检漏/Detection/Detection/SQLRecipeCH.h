// SQLRecipeCH.h : CSQLRecipeCH ������

#pragma once

// ���������� 2016��11��17��, 15:13

class CSQLRecipeCH : public CRecordset
{
public:
	CSQLRecipeCH(INT GUID = 0, CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSQLRecipeCH)

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��
	enum
	{
		Max_Data_Num = 30
	};
	enum
	{
		U1 = 0,//��Դ��ѹ1
		U2 = 1,//��Դ��ѹ2
		Lou1 = 4,//��һƿй©��ѹ1
		Lou2 = 5,//��һƿй©��ѹ2
		U_SET1 = 6,//��ѹ�趨ֵ
		U_SET2 = 12,//��ѹ�趨ֵ
		UpLine1 = 7,//й©��ѹ����1
		UpLine2 = 13,//й©��ѹ����2
		DownLine1 = 9,//й©��ѹ����1
		DownLine2 = 15,//й©��ѹ����1
		LMD1 = 10,	//1#�Ŵ���
		LMD2 = 16,	//2#�Ŵ���
	};
	CStringW	m_NAME;
	INT m_data[Max_Data_Num];
	/*
	int	m_U_SET1;
	int	m_U_SET2;
	int	m_UPLINE1;
	int	m_UPLINE2;
	int	m_DOWNLINE1;
	int	m_DOWNLINE2;
	int	m_LMD1;
	int	m_LMD2;
	*/
	CString m_tableName;
// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��
	INT ComSetTableName(INT GUID);//������ ͨ����
// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


