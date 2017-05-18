#pragma once
#import "c:\program files\common files\system\ado\msado15.dll"\
 no_namespace rename("EOF", "adoEOF")rename("BOF","adoBOF")
#include <vector>
using namespace std;
class DataBaseAcc
{
public:
	DataBaseAcc();
	virtual ~DataBaseAcc();
public:
	virtual INT ComInitAccess(CString path);//��ʼ�����ݿ�
	virtual INT ComLoadAccess(CString path);//���ݿ�·��
	virtual INT ComGetErr(CString& err);//��ȡ������Ϣ
	virtual INT ComCreateTatble();//������
	virtual INT ComCreateTatble(CString tableName);//������
	virtual INT ComInsertData(INT ch1[]);//������Ϣ
	virtual INT ComInsertData(CString& tableName,INT ch1[]);//������Ϣ
	virtual INT ComGetData(CTime& startT, CTime& endT, vector<LONGLONG>& data, INT num = FALSE);//��ȡ����
	virtual INT ComUpData();//�ύ����
	virtual INT ComIsTable(CString& tableName);//�жϱ��Ƿ����
private:
	virtual INT PirGetErr(_com_error& e);//��ȡ������Ϣ
private:
	_ConnectionPtr  m_pConnection; // ����ADO���ӱ���ָ��
	_RecordsetPtr    m_pRecordset;// �����¼������ָ��
	_RecordsetPtr    m_pRecordsetR;// �����¼������ָ��
	CString m_tableName;//���������
	CString m_path;//���浱ǰ����·��
};

