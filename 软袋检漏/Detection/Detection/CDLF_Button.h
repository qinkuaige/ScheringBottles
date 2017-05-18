// CDLF_Button.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDLF_Button

class CDLF_Button : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDLF_Button)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x26151E11, 0xE742, 0x4EBF, { 0xAD, 0xBE, 0x5C, 0x12, 0x53, 0xD5, 0x70, 0x92 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:

// 操作
public:

	long setCallBack(signed char * callBackDown, signed char * callBackUp, long other)
	{
		long result;
		static BYTE parms[] = VTS_PI1 VTS_PI1 VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, callBackDown, callBackUp, other);
		return result;
	}
	short SetBackPath(BSTR * path)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I2, (void*)&result, parms, path);
		return result;
	}
	short SetIconPath(BSTR * path)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I2, (void*)&result, parms, path);
		return result;
	}
	short SetIconName(BSTR * fileName)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, fileName);
		return result;
	}
	short SetState(unsigned short state)
	{
		short result;
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I2, (void*)&result, parms, state);
		return result;
	}
	short GetState()
	{
		short result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short SetBackName(BSTR * fileName)
	{
		short result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I2, (void*)&result, parms, fileName);
		return result;
	}


};
