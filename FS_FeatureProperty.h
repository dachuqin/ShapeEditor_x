#if !defined(AFX_FS_FEATUREPROPERTY_H__FB914917_7C79_4B26_877B_7AF32F952E7D__INCLUDED_)
#define AFX_FS_FEATUREPROPERTY_H__FB914917_7C79_4B26_877B_7AF32F952E7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_FeatureProperty.h : header file
//
#include "GridCtrl_src/GridCtrl.h"
#include "CellRange.h"

/////////////////////////////////////////////////////////////////////////////
// CFS_FeatureProperty dialog

class CFS_FeatureProperty : public CDialog
{
// Construction
public:
	CFS_FeatureProperty(CWnd* pParent = NULL);   // standard constructor
//	CFS_FeatureProperty(CWnd* pParent = NULL);   // standard constructor
	void	GetSelectedFeature();

// Dialog Data
	//{{AFX_DATA(CFS_FeatureProperty)
	enum { IDD = IDD_FEATURE_PROPERTY };
	CListCtrl	m_ctrList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFS_FeatureProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
protected:
	IFeaturePtr		m_pFeature;
	IEnumFeaturePtr m_pSelectedFeature;
//	IEnumFeaturePtr m_pBackupFeature;

	CEdit	*m_pEdit;
	CGridCtrl	m_Grid;
	BOOL		m_bIsRef;
	CCellID		m_EditCell;
// Implementation
protected:
	void	_GetCurrentDate(CString &strDate);
	
	BOOL	_IsDate(CString &str);
	BOOL	_IsFloat(CString& strText);
		
	BOOL	IsInteger(CString Integer);
	BOOL	IsLegal(CString &strFieldValue,CString strFieldType);

	void	GetDateFromStr(CString strTm, COleDateTime &tm);
	CString esriToCString(esriFieldType fieldtype);

	CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype);
	VARIANT ConvertType(CString strFieldValue,esriFieldType fieldtype);
	void	SaveModify();
	HRESULT GetIndexByName(CString strName,IFeature **pSelectedFeature);
//	long	GetIndexByName(CString strName);

	// Generated message map functions
	//{{AFX_MSG(CFS_FeatureProperty)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	afx_msg void OnExit();
	//}}AFX_MSG
	afx_msg void OnGridEndInPlaceEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_FEATUREPROPERTY_H__FB914917_7C79_4B26_877B_7AF32F952E7D__INCLUDED_)
