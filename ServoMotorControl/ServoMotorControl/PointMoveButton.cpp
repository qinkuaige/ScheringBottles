#include "stdafx.h"
#include "PointMoveButton.h"


PointMoveButton::PointMoveButton(UINT id, LPCTSTR device)
:m_id(id), m_device(device)
{
}


PointMoveButton::~PointMoveButton()
{
}


BOOL PointMoveButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// 捕获鼠标左键按下和松开状态，上报父窗口  
	switch (message)
	{
	case WM_LBUTTONDOWN:
		::SendMessage(this->GetParent()->m_hWnd, m_id, 1, 0);
		break;
	case WM_LBUTTONUP:
		::SendMessage(this->GetParent()->m_hWnd, m_id, 0, 0);
		break;
	default:
		break;
	}
	return CButton::OnWndMsg(message, wParam, lParam, pResult);
}


void  PointMoveButton::set_run(CActutltype1 &motor)
{
	motor.SetDevice(m_device, 1);
}

void  PointMoveButton::set_stop(CActutltype1 &motor)
{
	motor.SetDevice(m_device, 0);
}

