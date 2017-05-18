#pragma once

// CSetValueDlg 对话框
struct ParamStruct
{
	CString m_name;//参数名称
	INT		m_max;//参数最大值
	INT		m_min;//参数最小值
	INT     m_root;//权限
	CString m_value;//参数值
	ParamStruct()
		: m_name(_T(""))
		, m_max(FALSE)
		, m_min(FALSE)
		, m_root(FALSE)
		, m_value(_T(""))
	{
	}
	operator INT()
	{
		return _ttoi(m_value);
	}
	operator LONG()
	{
		return _ttoi(m_value);
	}
	operator DWORD()
	{
		return _ttoi(m_value);
	}
	operator DOUBLE()
	{
		return _ttof(m_value);
	}
	operator CString()
	{
		return m_value;
	}
	inline INT operator=(INT value)
	{
		m_value.Format(_T("%d"), value);
		return value;
	}
	inline LONG operator=(LONG value)
	{
		m_value.Format(_T("%d"), value);
		return value;
	}
	inline DOUBLE operator=(DOUBLE value)
	{
		m_value.Format(_T("%f"), value);
		return value;
	}
	inline CString operator=(CString value)
	{
		m_value = value;
		return value;
	}
	inline ParamStruct operator*(INT value)
	{
		(*this) = _ttof(m_value) * value;
		return (*this);
	}
	inline ParamStruct operator*(DOUBLE value)
	{
		(*this) = _ttof(m_value) * value;
		return (*this);
	}
};
class CDetectionDlg;
class CSetValueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetValueDlg)

public:
	CSetValueDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetValueDlg();

// 对话框数据
	enum { IDD = IDD_SET_VALUE_DLG };
public:
	INT initDlg(CDetectionDlg* pDlg, CRect& rect = CRect(0, 0, 0, 0));//初始化窗口
	INT showDlg(ParamStruct& value);//显示窗口
	ParamStruct GetValue();//返回设置的值
private:
	INT PriSetValue(CString value);//设置当前数据
public:
	CDetectionDlg* m_pDlg;//保存主窗口指针
	ParamStruct* m_value;//保存当前输入值
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSvPoint();
	afx_msg void OnBnClickedSv0();
	afx_msg void OnBnClickedSv1();
	afx_msg void OnBnClickedSv2();
	afx_msg void OnBnClickedSv3();
	afx_msg void OnBnClickedSv4();
	afx_msg void OnBnClickedSv5();
	afx_msg void OnBnClickedSv6();
	afx_msg void OnBnClickedSv7();
	afx_msg void OnBnClickedSv8();
	afx_msg void OnBnClickedSv9();
	afx_msg void OnBnClickedSvB();
	afx_msg void OnBnClickedSvC();
	afx_msg void OnBnClickedSvYes();
	afx_msg void OnBnClickedSvNo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedSvSub();
};
