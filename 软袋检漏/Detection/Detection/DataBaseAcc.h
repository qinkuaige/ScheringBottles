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
	virtual INT ComInitAccess(CString path);//初始化数据库
	virtual INT ComLoadAccess(CString path);//数据库路径
	virtual INT ComGetErr(CString& err);//获取错误信息
	virtual INT ComCreateTatble();//创建表
	virtual INT ComCreateTatble(CString tableName);//创建表
	virtual INT ComInsertData(INT ch1[]);//插入信息
	virtual INT ComInsertData(CString& tableName,INT ch1[]);//插入信息
	virtual INT ComGetData(CTime& startT, CTime& endT, vector<LONGLONG>& data, INT num = FALSE);//获取数据
	virtual INT ComUpData();//提交数据
	virtual INT ComIsTable(CString& tableName);//判断表是否存在
private:
	virtual INT PirGetErr(_com_error& e);//获取错误信息
private:
	_ConnectionPtr  m_pConnection; // 定义ADO连接变量指针
	_RecordsetPtr    m_pRecordset;// 定义记录集变量指针
	_RecordsetPtr    m_pRecordsetR;// 定义记录集变量指针
	CString m_tableName;//保存表名称
	CString m_path;//保存当前数据路径
};

