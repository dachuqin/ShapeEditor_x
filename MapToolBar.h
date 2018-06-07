#if !defined(AFX_MAPTOOLBAR_H__6A08D18C_663B_4AB3_AB39_9C78A6A1FA14__INCLUDED_)
#define AFX_MAPTOOLBAR_H__6A08D18C_663B_4AB3_AB39_9C78A6A1FA14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapToolBar window

class CMapToolBar : public CToolBar
{
// Construction
public:
	CMapToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPTOOLBAR_H__6A08D18C_663B_4AB3_AB39_9C78A6A1FA14__INCLUDED_)
