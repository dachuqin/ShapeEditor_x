#if !defined(AFX_LAYERMANAGE_H__B9639669_7123_44FD_AEC2_B851DA333A61__INCLUDED_)
#define AFX_LAYERMANAGE_H__B9639669_7123_44FD_AEC2_B851DA333A61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerManage.h : header file
//

#ifndef baseCMyBar
#define baseCMyBar CSizingControlBarG
#endif
#include "TreeLayer.h"
/////////////////////////////////////////////////////////////////////////////
// CLayerManage window
#define ID_TREECTRL	2001

class CLayerManage : public baseCMyBar
{
// Construction
public:
	CLayerManage();

// Attributes
public:
	CTreeLayer	m_wndTree;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerManage)
	//}}AFX_VIRTUAL
protected:	
	CFont	m_font;
	// Implementation
public:
	virtual ~CLayerManage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLayerManage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERMANAGE_H__B9639669_7123_44FD_AEC2_B851DA333A61__INCLUDED_)
