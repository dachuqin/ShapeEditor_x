// FS_MergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shpeditor.h"
#include "FS_MergeDlg.h"
#include "MainFrm.h"
#include "ShpEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFS_MergeDlg dialog


CFS_MergeDlg::CFS_MergeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFS_MergeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFS_MergeDlg)
	//}}AFX_DATA_INIT
	m_OID=0;
}


void CFS_MergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFS_MergeDlg)
	DDX_Control(pDX, IDC_LIST, m_ctrList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFS_MergeDlg, CDialog)
	//{{AFX_MSG_MAP(CFS_MergeDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFS_MergeDlg message handlers

BOOL CFS_MergeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();
	IArrayPtr	pSeletedFeature;
	HRESULT	hr;
	hr=pView->GetSelectedFeatures(&pSeletedFeature);
	if(FAILED(hr)) return TRUE;
//	long nIndex;
//	nIndex=pView->GetLabelIndex();

	InitListBox(pSeletedFeature);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFS_MergeDlg::InitListBox(IArrayPtr	pSeletedFeature)
{	
	HRESULT	 hr;
	CMainFrame *pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CShpEditorView *pView=(CShpEditorView*)pMF->GetActiveView();

	m_ctrList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	IFeaturePtr	pFeature;
	
	hr=pSeletedFeature->get_Element(0,(IUnknown**)&pFeature);
	if(FAILED(hr)) return;	
	
	IFieldsPtr	pFields;
	pFeature->get_Fields(&pFields);
	
	long nFieldCount;
	pFields->get_FieldCount(&nFieldCount);

	
	int nIndex=0;
	for(long i=0;i<nFieldCount;i++)
	{

		IFieldPtr	pField;
		pFields->get_Field(i,&pField);

		VARIANT_BOOL	vtb;
		pField->get_Required(&vtb);
		if(vtb==VARIANT_TRUE)
			continue;

		BSTR	BFieldName;
		pField->get_Name(&BFieldName);

		CString strFieldName;
		strFieldName=(LPCWSTR)BFieldName;

		m_ctrList.InsertColumn(nIndex,strFieldName,LVCFMT_LEFT,70);		
	}
	
	
	long	nCount;
	hr=pSeletedFeature->get_Count(&nCount);

	for( i=0;i<nCount;i++)
	{
		IFeaturePtr	pFeature;
		hr=pSeletedFeature->get_Element(i,(IUnknown**)&pFeature);
		if(FAILED(hr)) return;

		
		IFieldsPtr	pFields;
		pFeature->get_Fields(&pFields);

		CString	strIndex;
		strIndex.Format("%ld",i+1);
		m_ctrList.InsertItem(i,strIndex);
		int nItemIndex=0;
		for(long l=0;l<nFieldCount;l++)
		{
			
			IFieldPtr	pField;
			pFields->get_Field(l,&pField);
			
			VARIANT_BOOL	vtb;
			pField->get_Required(&vtb);
			if(vtb==VARIANT_TRUE)
				continue;
	
			esriFieldType	FieldType;
			pField->get_Type(&FieldType);
			
			VARIANT	vtFieldValue;
			pFeature->get_Value(l,&vtFieldValue);
			
			CString strFieldValue;
			strFieldValue=pView->vtToCString(vtFieldValue,FieldType);
			
			m_ctrList.SetItemText(i,nItemIndex,(LPCTSTR)strFieldValue);
			nItemIndex++;
		}

		long OID;
		pFeature->get_OID(&OID);

		FS_SelectedInfo=new CFS_FeatureInfo;
		
		FS_SelectedInfo->OID=OID;
		FS_SelectedInfo->nItemIndex=i;
		m_SelectedInfoSet.Add(FS_SelectedInfo);
	}

	m_ctrList.SetItemState(1,1,LVIS_SELECTED);
}

void CFS_MergeDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	POSITION pos = m_ctrList.GetFirstSelectedItemPosition();

	int nItem = m_ctrList.GetNextSelectedItem(pos);

	int nCount;
	nCount=m_SelectedInfoSet.GetSize();

	CFS_FeatureInfo	*SelectedInfo;

	for(int i=0;i<nCount;i++)
	{
		
		SelectedInfo=m_SelectedInfoSet.GetAt(i);

		int nSelectedItem=0;
		nSelectedItem=SelectedInfo->nItemIndex;
		if(nItem==nSelectedItem)
			m_OID=SelectedInfo->OID;
	}
	CDialog::OnOK();
}

void CFS_MergeDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	int nCount;
	nCount=m_SelectedInfoSet.GetSize();
	
	for(int i=0;i<nCount;i++)
	{
		
		delete m_SelectedInfoSet.GetAt(i);
	}
	m_SelectedInfoSet.RemoveAll();
}
