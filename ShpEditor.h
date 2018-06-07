// ShpEditor.h : main header file for the SHPEDITOR application
//

#if !defined(AFX_SHPEDITOR_H__04E6F4CC_6BF8_4248_B1BF_ACF2425FBAD4__INCLUDED_)
#define AFX_SHPEDITOR_H__04E6F4CC_6BF8_4248_B1BF_ACF2425FBAD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CShpEditorApp:
// See ShpEditor.cpp for the implementation of this class
//

class CShpEditorApp : public CWinApp
{
public:
	CShpEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShpEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CShpEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHPEDITOR_H__04E6F4CC_6BF8_4248_B1BF_ACF2425FBAD4__INCLUDED_)
