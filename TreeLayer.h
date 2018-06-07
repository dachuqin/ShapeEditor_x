#if !defined(AFX_TREELAYER_H__E9203DCF_3BE7_4E9B_BC3F_6BE84A34B70C__INCLUDED_)
#define AFX_TREELAYER_H__E9203DCF_3BE7_4E9B_BC3F_6BE84A34B70C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeLayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeLayer window
typedef struct  _TC_HTREEITEM{
	HTREEITEM	hti;
	BOOL		bIsVisible;
	CString		strRootName;
}TC_HTREEITEM;

class CTreeLayer : public CTreeCtrl
{
// Construction
public:
	CTreeLayer();

// Attributes
public:
	
	CImageList	m_TypeImgList;
	CImageList	m_StatusBmpList;

	TC_HTREEITEM	m_TCPreRefItem;
	TC_HTREEITEM	m_TCPreEditItem;
//	CBitmap		*AddBmp;
//	CBitmap		*DelBmp;
// Operations
public:
	void InitTreeCtrl();	
	void AddLayerItem(int nLayerType,BOOL IsVisible,CString LayerName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeLayer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeLayer();

	// Generated message map functions
protected:
	BOOL		m_bIsEditLayerLabelVisibel;
	BOOL		m_bIsRefLayerLabelVisibel;
protected:
	//{{AFX_MSG(CTreeLayer)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLayerDelete();
	afx_msg void OnAddLayer();
	afx_msg void OnAddRefLayer();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLayerSymbol();
	afx_msg void OnLayerShowLabel();
	afx_msg void OnUpdateLayerShowLabel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileDellayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLayerSymbol(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREELAYER_H__E9203DCF_3BE7_4E9B_BC3F_6BE84A34B70C__INCLUDED_)
