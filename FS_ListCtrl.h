#if !defined(AFX_FS_LISTCTRL_H__6A9473DB_FB06_4D55_91C3_B9C0481D0CC5__INCLUDED_)
#define AFX_FS_LISTCTRL_H__6A9473DB_FB06_4D55_91C3_B9C0481D0CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_ListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFS_ListCtrl window

class CFS_ListCtrl : public CListCtrl
{
// Construction
public:
	CFS_ListCtrl();

// Attributes
public:
	CString m_strFieldName;
	CString m_strFieldType;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFS_ListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFS_ListCtrl();

	// Generated message map functions
protected:
	
	//{{AFX_MSG(CFS_ListCtrl)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_LISTCTRL_H__6A9473DB_FB06_4D55_91C3_B9C0481D0CC5__INCLUDED_)
