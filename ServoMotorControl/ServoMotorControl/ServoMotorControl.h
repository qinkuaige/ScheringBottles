
// ServoMotorControl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CServoMotorControlApp: 
// �йش����ʵ�֣������ ServoMotorControl.cpp
//

class CServoMotorControlApp : public CWinApp
{
public:
	CServoMotorControlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServoMotorControlApp theApp;