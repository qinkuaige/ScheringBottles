#pragma once
#include "mscomm1.h"
#include "resource.h"

// CModBusDlg �Ի���
class CModBus;
class CModBusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModBusDlg)

public:
	CModBusDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModBusDlg();

// �Ի�������
	enum { IDD = IDD_MODBUS };
public:
	CModBus* m_modBus;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMscomm1 m_com;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
};
