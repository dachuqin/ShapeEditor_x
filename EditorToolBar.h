#if !defined(AFX_EDITORTOOLBAR_H__8F35C80F_9EDB_41E0_A195_C091CCF91B6B__INCLUDED_)
#define AFX_EDITORTOOLBAR_H__8F35C80F_9EDB_41E0_A195_C091CCF91B6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorToolBar.h : header file
//
#include "MenuButton.h"
#include "FS_MenuButton.h"

/////////////////////////////////////////////////////////////////////////////
// CEditorToolBar window

class CEditorToolBar : public CToolBar
{
// Construction
public:
	CEditorToolBar();

// Attributes
public:

// Operations
public:
	CMenuButton		m_MenuButton;
	CFS_MenuButton  m_FS_MenuButton;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditorToolBar();

	// Generated message map functions
protected:
	BOOL CreateSketchButton();
	CFont	m_font;
	//{{AFX_MSG(CEditorToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditorMenu();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORTOOLBAR_H__8F35C80F_9EDB_41E0_A195_C091CCF91B6B__INCLUDED_)
