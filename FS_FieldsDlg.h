//{{AFX_INCLUDES()
#include "listview.h"
//}}AFX_INCLUDES
#if !defined(AFX_FS_FIELDSDLG_H__EE358B0A_74E1_42B3_A049_23D32C4881C5__INCLUDED_)
#define AFX_FS_FIELDSDLG_H__EE358B0A_74E1_42B3_A049_23D32C4881C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FS_FieldsDlg.h : header file
//
#include "FS_ListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFS_FieldsDlg dialog

class CFS_FieldsDlg : public CDialog
{
// Construction
public:
	CFS_FieldsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFS_FieldsDlg)
	enum { IDD = IDD_ADD_FIELDS };
	CListCtrl	m_ListCtrl;
	CButton	m_btModify;
	CButton	m_btDelete;
	CButton	m_btAdd;
	CComboBox	m_ctrFieldType;
	CString	m_strField;
	CString	m_strFieldType;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFS_FieldsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	int m_nIndex;
	IFeatureLayerPtr	m_pEditLayer;
	IWorkspaceEditPtr	m_pWorkspaceEdit;
	ICursorPtr			m_pCursor;

// Implementation
protected:
	void InitFieldValue(VARIANT &vtFieldValue,esriFieldType fieldtype);
	void InitNewField(BSTR BFieldName,esriFieldType fieldtype);
	BOOL CheckRepeat(CString strFieldName);
	void _GetCurrentDate(CString &strDate);
	BOOL IsHasExist(CString strFieldName);
	void AddFields();
	CString vtToCString(VARIANT vtFieldValue,esriFieldType fieldtype);
	CString esriToCString(esriFieldType fieldtype);
	void	ShowFields();
	void	AddFieldsToLayer();
	esriFieldType GetFieldType(CString	strFieldType);

	// Generated message map functions
	//{{AFX_MSG(CFS_FieldsDlg)
	afx_msg void OnButtonAdd();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDlete();
	afx_msg void OnModify();
	afx_msg void OnItemchangingListFields(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FS_FIELDSDLG_H__EE358B0A_74E1_42B3_A049_23D32C4881C5__INCLUDED_)
