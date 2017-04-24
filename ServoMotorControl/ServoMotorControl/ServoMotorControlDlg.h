#pragma once

#include "actutltype1.h"
#include "afxwin.h"
#include "PointMoveButton.h"
#include "KeyBoard.h"
#include "ClickEdit.h"
#include<map>
#include "afxext.h"

using namespace std;
class CServoMotorControlDlg : public CDialogEx
{
	static const UINT smore_button_id = 10000;
public:
	CServoMotorControlDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CServoMotorControlDlg();
	static DWORD WINAPI ThreadProc(LPVOID pParam);//���߳�
	static DWORD WINAPI turnOn_thread(LPVOID pParam); //�����߳�
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void add_Control(const UINT &id, LPCTSTR device, CDataExchange* pDX);
	void add_edit(const UINT &id, const LPCTSTR device);
// ʵ��
private:
	HICON m_hIcon;
	CActutltype1 m_motor;
	bool m_motorState ;
	HANDLE handle;
	HANDLE m_ONhandle;
	HANDLE m_mutex;
	POINT Old;
	map<UINT, PointMoveButton*> m_button;
	map<UINT, ClickEdit*>  m_edit;
	CBitmapButton m_m2044;
	KeyBoard m_board;

	void risingEdge(const CString str);
	void set_value(const CString str, const UINT data);
	void ReadAndShowD();
	void turn_on(); //����
	bool PositionOrigin(const CString str);
	// ���ɵ���Ϣӳ�亯��
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	enum { IDD = IDD_SERVOMOTORCONTROL_DIALOG };
	afx_msg void Start();
	afx_msg void Stop();
	afx_msg void M30();
	afx_msg void M31();
	afx_msg void M32();
	afx_msg void M33();
	afx_msg void M34();
	afx_msg void M35();
	afx_msg void M104();
	afx_msg void M105();
	afx_msg void M106();
	afx_msg void M107();
	afx_msg void M0();
	afx_msg void M180();
	afx_msg void M181();
	afx_msg void M182();
	afx_msg void M183();
	afx_msg void M184();
	afx_msg void M185();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void turnON();//������ť�¼�
	afx_msg void turnOFF();//�ػ���ť�¼�
	virtual void OnOK();
	virtual void OnCancel();
};


