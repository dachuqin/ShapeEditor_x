#if !defined(AFX_FS_SELECTLABELDLG_H__6B7718EC_0A7D_4AFD_8FFA_5737C1AFCCA4__INCLUDED_)
#define AFX_FS_SELECTLABELDLG_H__6B7718EC_0A7D_4AFD_8FFA_5737C1AFCCA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_SelectLabelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFS_SelectLabelDlg dialog

class CFS_SelectLabelDlg : public CDialog
{
// Construction
public:
	CFS_SelectLabelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFS_SelectLabelDlg)
	enum { IDD = IDD_SELECT_LABEL };
	CListBox	m_ListBox;
	CString	m_strSelectedField;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFS_SelectLabelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitListBox(IFeatureLayerPtr	pLayer);

	// Generated message map functions
	//{{AFX_MSG(CFS_SelectLabelDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_SELECTLABELDLG_H__6B7718EC_0A7D_4AFD_8FFA_5737C1AFCCA4__INCLUDED_)
