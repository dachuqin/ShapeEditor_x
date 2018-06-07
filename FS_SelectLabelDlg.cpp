// FS_SelectLabelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shpeditor.h"
#include "FS_SelectLabelDlg.h"

#include "MainFrm.h"
#include "ShpEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_SelectLabelDlg dialog


CFS_SelectLabelDlg::CFS_SelectLabelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFS_SelectLabelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFS_SelectLabelDlg)
	m_strSelectedField = _T("");
	//}}AFX_DATA_INIT
}


void CFS_SelectLabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFS_SelectLabelDlg)
	DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
	DDX_LBString(pDX, IDC_LISTBOX, m_strSelectedField);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFS_SelectLabelDlg, CDialog)
	//{{AFX_MSG_MAP(CFS_SelectLabelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_SelectLabelDlg message handlers

BOOL CFS_SelectLabelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	
	IFeatureLayerPtr	pFeatureLayer;
	
	pView->GetCurrentLayer(&pFeatureLayer);
	InitListBox(pFeatureLayer);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFS_SelectLabelDlg::InitListBox(IFeatureLayerPtr	pLayer)
{
	
	ITablePtr	pTable;
	IGeoFeatureLayerPtr	pGeoLayer;
	pGeoLayer=pLayer;
	pTable	=pGeoLayer;
	
	IFieldsPtr	pFields;
	pTable->get_Fields(&pFields);
	
	long nCount;
	pFields->get_FieldCount(&nCount);
	if(nCount<1) return ;
	
	for(long i=0;i<nCount;i++)
	{
		IFieldPtr	pField;
		BSTR		BName;
		
		pFields->get_Field(i,&pField);
		
		VARIANT_BOOL	vtb;
		pField->get_Required(&vtb);
		
		if(vtb==VARIANT_TRUE)
			continue;

		pField->get_Name(&BName);
		
		CString	strName;
		strName=(LPCWSTR)BName;
		
		m_ListBox.AddString(strName);
	}	
}