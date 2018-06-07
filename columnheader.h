#if !defined(AFX_COLUMNHEADER_H__74F11736_C707_4D9D_B0D0_429C3AD7D70A__INCLUDED_)
#define AFX_COLUMNHEADER_H__74F11736_C707_4D9D_B0D0_429C3AD7D70A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CColumnHeader wrapper class

class CColumnHeader : public COleDispatchDriver
{
public:
	CColumnHeader() {}		// Calls COleDispatchDriver default constructor
	CColumnHeader(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CColumnHeader(const CColumnHeader& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetIndex();
	void SetIndex(long nNewValue);
	CString GetKey();
	void SetKey(LPCTSTR lpszNewValue);
	float GetLeft();
	void SetLeft(float newValue);
	short GetSubItemIndex();
	void SetSubItemIndex(short nNewValue);
	VARIANT GetTag();
	void SetTag(const VARIANT& newValue);
	float GetWidth();
	void SetWidth(float newValue);
	void SetRefTag(const VARIANT& newValue);
	VARIANT GetIcon();
	void SetIcon(const VARIANT& newValue);
	short GetPosition();
	void SetPosition(short nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLUMNHEADER_H__74F11736_C707_4D9D_B0D0_429C3AD7D70A__INCLUDED_)