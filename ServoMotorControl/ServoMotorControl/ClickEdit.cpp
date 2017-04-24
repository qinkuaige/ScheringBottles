#include "stdafx.h"
#include "ClickEdit.h"


ClickEdit::ClickEdit(UINT msgID, LPCTSTR device) :m_msgID(msgID), m_device(device)
{
}


ClickEdit::~ClickEdit()
{
}
BEGIN_MESSAGE_MAP(ClickEdit, CEdit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void ClickEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	::SendMessage(this->GetParent()->m_hWnd, m_msgID, 1, 0);
	CEdit::OnLButtonDown(nFlags, point);
}
