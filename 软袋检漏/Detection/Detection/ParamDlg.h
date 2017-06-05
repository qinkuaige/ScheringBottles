#pragma once
#include "Control.h"
#include "afxcmn.h"

// CParamDlg 对话框
class CDetectionDlg;
class CParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParamDlg)

public:
	CParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamDlg();

// 对话框数据
	enum { IDD = IDD_PARAM };
public:
	INT initDialog(CDetectionDlg* parentdlg);//创建窗口
	INT showDialog(UINT dialogID);//显示窗口
	INT updataList();
	INT changParam(CString name, INT sub, INT ParamID, const UINT coefficient = 100);//修改参数

private:
	CDetectionDlg* m_pDlg;
	CControl* m_pControl;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_rList;
	afx_msg void OnStnClickedPUs1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPUs2();
	afx_msg void OnStnClickedPUs3();
	afx_msg void OnStnClickedPUs4();
	afx_msg void OnStnClickedPLup1();
	afx_msg void OnStnClickedPLup2();
	afx_msg void OnStnClickedPLup3();
	afx_msg void OnStnClickedPLup4();
	afx_msg void OnStnClickedPLdown1();
	afx_msg void OnStnClickedPLdown2();
	afx_msg void OnStnClickedPLdown3();
	afx_msg void OnStnClickedPLdown4();
	afx_msg void OnStnClickedPLmd1();
	afx_msg void OnStnClickedPLmd2();
	afx_msg void OnStnClickedPLmd3();
	afx_msg void OnStnClickedPLmd4();
	afx_msg void OnBnClickedRecipeDlg();
	afx_msg void OnStnClickedPUs6();
	afx_msg void OnStnClickedPUs5();
	afx_msg void OnStnClickedPLup5();
	afx_msg void OnStnClickedPLup6();
	afx_msg void OnStnClickedPLdown5();
	afx_msg void OnStnClickedPLdown6();
	afx_msg void OnStnClickedPLmd5();
	afx_msg void OnStnClickedPLmd6();
};
