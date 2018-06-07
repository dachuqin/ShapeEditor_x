// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A4807AE9_2EE6_422A_A4B5_2C65837BA5F0__INCLUDED_)
#define AFX_MAINFRM_H__A4807AE9_2EE6_422A_A4B5_2C65837BA5F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EditorToolBar.h"
#include "MapToolBar.h"
#include "LayerManage.h"
#include "TreeLayer.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
// Operations
public:
	CLayerManage	m_wndLayerManageBar;

	void ShowCoordinate(double X,double Y);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CReBarCtrl	m_wndReBar;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CEditorToolBar	m_wndEditorToolBar;
	CMapToolBar		m_wndMapToolBar;


// Generated message map functions
protected:
	BOOL	CreateToolbar();
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditorVisible();
	afx_msg void OnUpdateEditorVisible(CCmdUI* pCmdUI);
	afx_msg void OnToolsVisible();
	afx_msg void OnUpdateToolsVisible(CCmdUI* pCmdUI);
	afx_msg void OnLayerManage();
	afx_msg void OnUpdateLayerManage(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnChangeFeature(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A4807AE9_2EE6_422A_A4B5_2C65837BA5F0__INCLUDED_)
