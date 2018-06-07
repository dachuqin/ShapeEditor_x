#if !defined(AFX_STARDLG_H__D72D43CF_BAB9_4761_98C9_1ECC11BA2CDF__INCLUDED_)
#define AFX_STARDLG_H__D72D43CF_BAB9_4761_98C9_1ECC11BA2CDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStarDlg dialog

class CStarDlg : public CDialog
{
// Construction
public:
	CStarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStarDlg)
	enum { IDD = IDD_WELLCOM_DLG };
	int		m_nState;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStarDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARDLG_H__D72D43CF_BAB9_4761_98C9_1ECC11BA2CDF__INCLUDED_)
