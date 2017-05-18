// SQLRecipeCH.h : CSQLRecipeCH 的声明

#pragma once

// 代码生成在 2016年11月17日, 15:13

class CSQLRecipeCH : public CRecordset
{
public:
	CSQLRecipeCH(INT GUID = 0, CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSQLRecipeCH)

	// 字段/参数数据

	// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
	// 数据类型的 CStringW)的实际数据类型。
	//  这是为防止 ODBC 驱动程序执行可能
	// 不必要的转换。如果希望，可以将这些成员更改为
	// CString 类型，ODBC 驱动程序将执行所有必要的转换。
	// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
	// 以同时支持 Unicode 和这些转换)。
	enum
	{
		Max_Data_Num = 30
	};
	enum
	{
		U1 = 0,//电源电压1
		U2 = 1,//电源电压2
		Lou1 = 4,//上一瓶泄漏电压1
		Lou2 = 5,//上一瓶泄漏电压2
		U_SET1 = 6,//高压设定值
		U_SET2 = 12,//高压设定值
		UpLine1 = 7,//泄漏电压上限1
		UpLine2 = 13,//泄漏电压上限2
		DownLine1 = 9,//泄漏电压下限1
		DownLine2 = 15,//泄漏电压下限1
		LMD1 = 10,	//1#放大倍数
		LMD2 = 16,	//2#放大倍数
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
// 重写
	// 向导生成的虚函数重写
	public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持
	INT ComSetTableName(INT GUID);//表名称 通道号
// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


