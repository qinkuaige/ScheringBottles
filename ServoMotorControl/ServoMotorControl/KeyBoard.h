#pragma once

#include "ClickEdit.h"
#include "actutltype1.h"

class KeyBoard : public CDialogEx
{
	DECLARE_DYNAMIC(KeyBoard)

private:
	ClickEdit* m_edit;
	HANDLE *m_mutex;
	CActutltype1 *m_motor;
	UINT m_number;

public:
	KeyBoard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~KeyBoard();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	void input(const UINT number);

public:
	inline void set_edit(ClickEdit* edit){ m_edit = edit; }
	inline void set_mutex(HANDLE* mutex){ m_mutex = mutex; }
	inline  void set_motor(CActutltype1 *motor){ m_motor = motor;}
	afx_msg void one();
	afx_msg void two();
	afx_msg void three();
	afx_msg void four();
	afx_msg void five();
	afx_msg void six();
	afx_msg void seven();
	afx_msg void eight();
	afx_msg void nine();
	afx_msg void zero();
	afx_msg void remove();
	afx_msg void ok();
	virtual void OnOK();
};
