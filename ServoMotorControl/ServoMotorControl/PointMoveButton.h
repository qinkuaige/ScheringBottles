#pragma once
#include "afxwin.h"
#include "actutltype1.h"

class PointMoveButton :
	public CButton
{
public:
	PointMoveButton(UINT id, LPCTSTR m_device);
	~PointMoveButton();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void  set_run(CActutltype1 &motor);
	void  set_stop(CActutltype1 &motor);
	inline const  INT get_id(){ return m_id; }
private:
	UINT m_id;
	LPCTSTR m_device;

};

