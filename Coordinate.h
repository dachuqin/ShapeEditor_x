#if !defined(AFX_COORDINATE_H__FFA5301E_0750_49F7_BEB2_C724FFF148B6__INCLUDED_)
#define AFX_COORDINATE_H__FFA5301E_0750_49F7_BEB2_C724FFF148B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Coordinate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoordinate dialog

class CCoordinate : public CDialog
{
// Construction
public:
	CCoordinate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoordinate)
	enum { IDD = IDD_COORDINATE };
	double	m_X;
	double	m_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoordinate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoordinate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COORDINATE_H__FFA5301E_0750_49F7_BEB2_C724FFF148B6__INCLUDED_)
