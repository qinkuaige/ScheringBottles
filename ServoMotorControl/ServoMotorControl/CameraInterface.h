#pragma once

#include "Camera.h"

// CameraInterface 对话框

class CameraInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CameraInterface)

public:
	CameraInterface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CameraInterface();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };
private:
	Camera* m_camera;
	HANDLE m_acquistionHandle; 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

private:
	void collect();
public:
	static DWORD WINAPI imageAcquisitionThread(LPVOID pParam);
	afx_msg void StartCollecting();
	afx_msg void EndAcquisition();
};
