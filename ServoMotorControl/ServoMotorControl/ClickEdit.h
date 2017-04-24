#pragma once
#include "afxwin.h"
class ClickEdit :public CEdit
{
private:
	UINT m_msgID;
	LPCTSTR m_device;
public:
	ClickEdit(UINT, LPCTSTR);
	virtual ~ClickEdit();

	inline LPCTSTR get_device(){ return m_device; }
	inline UINT get_msgID(){ return m_msgID; }
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

