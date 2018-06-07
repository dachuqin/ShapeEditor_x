#if !defined(AFX_CLIPDLG_H__2053BB3D_92B9_4902_8487_493505863CED__INCLUDED_)
#define AFX_CLIPDLG_H__2053BB3D_92B9_4902_8487_493505863CED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClipDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClipDlg dialog

class CClipDlg : public CDialog
{
// Construction
public:
	CClipDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClipDlg)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_Radio;
	int		m_method;
	double	m_Distance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClipDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPDLG_H__2053BB3D_92B9_4902_8487_493505863CED__INCLUDED_)
