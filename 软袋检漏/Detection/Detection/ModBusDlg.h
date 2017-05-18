#pragma once
#include "mscomm1.h"
#include "resource.h"

// CModBusDlg 对话框
class CModBus;
class CModBusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModBusDlg)

public:
	CModBusDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModBusDlg();

// 对话框数据
	enum { IDD = IDD_MODBUS };
public:
	CModBus* m_modBus;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_com;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
};
