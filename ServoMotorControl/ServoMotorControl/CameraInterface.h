#pragma once


// CameraInterface �Ի���

class CameraInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CameraInterface)

public:
	CameraInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CameraInterface();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void StartCollecting();
	afx_msg void EndAcquisition();
};
