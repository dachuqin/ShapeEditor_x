#if !defined(AFX_DISTANCEDLG_H__5EB4C03C_16C8_43B8_8F24_091BBE6C57D8__INCLUDED_)
#define AFX_DISTANCEDLG_H__5EB4C03C_16C8_43B8_8F24_091BBE6C57D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DistanceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg dialog

class CDistanceDlg : public CDialog
{
// Construction
public:
	CDistanceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDistanceDlg)
	enum { IDD = IDD_DISTANCE };
	double	m_dDistance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDistanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDistanceDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISTANCEDLG_H__5EB4C03C_16C8_43B8_8F24_091BBE6C57D8__INCLUDED_)
