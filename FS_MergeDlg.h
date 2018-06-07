#if !defined(AFX_FS_MERGEDLG_H__31932D6C_570A_4748_9698_B4016975CE55__INCLUDED_)
#define AFX_FS_MERGEDLG_H__31932D6C_570A_4748_9698_B4016975CE55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_MergeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFS_MergeDlg dialog
class CFS_FeatureInfo :public CObject
{
public:
	CFS_FeatureInfo(){};

	long OID;
	int  nItemIndex;
};



typedef CTypedPtrArray<CObArray, CFS_FeatureInfo*> CFS_FeatureInfoARRAY;

class CFS_MergeDlg : public CDialog
{
// Construction
public:
	CFS_MergeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFS_MergeDlg)
	enum { IDD = IDD_MERGE_DLG };
	CListCtrl	m_ctrList;
	//}}AFX_DATA
	int m_OID;
	CFS_FeatureInfoARRAY	m_SelectedInfoSet;
	CFS_FeatureInfo	*FS_SelectedInfo;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFS_MergeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	void InitListBox(IArrayPtr	pSeletedFeature);
		
	// Generated message map functions
	//{{AFX_MSG(CFS_MergeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_MERGEDLG_H__31932D6C_570A_4748_9698_B4016975CE55__INCLUDED_)
