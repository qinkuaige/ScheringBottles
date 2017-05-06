#pragma once

#include "Camera.h"

// CameraInterface �Ի���

class CameraInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CameraInterface)

public:
	CameraInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CameraInterface();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };
private:
	Camera* m_camera;
	POINT m_oldSize;
	HANDLE m_acquistionHandle; 
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

private:
	void collect();
public:
	static DWORD WINAPI imageAcquisitionThread(LPVOID pParam);
	afx_msg void StartCollecting();
	afx_msg void EndAcquisition();
	afx_msg void return_button();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
