#if !defined(AFX_DRAWARCDLG_H__0FE4D33B_E029_4224_90E8_30C54FC5AB5A__INCLUDED_)
#define AFX_DRAWARCDLG_H__0FE4D33B_E029_4224_90E8_30C54FC5AB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawArcDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawArcDlg dialog

class CDrawArcDlg : public CDialog
{
// Construction
public:
	CDrawArcDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawArcDlg)
	enum { IDD = IDD_DRAW_ARC };
	CButton	m_ctrArcType;
	CEdit	m_ctrFromY;
	CEdit	m_ctrFromX;
	CButton	m_ctrClockwise;
	double	m_StarX;
	double	m_Radius;
	double	m_StarY;
	double	m_EndX;
	double	m_EndY;
	//}}AFX_DATA
	int m_nClockwise;
	int m_nArcType;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawArcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDrawArcDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSmallArc();
	afx_msg void OnClockwise();
	afx_msg void OnClockwise2();
	afx_msg void OnBigArc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWARCDLG_H__0FE4D33B_E029_4224_90E8_30C54FC5AB5A__INCLUDED_)
